#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>

#include <png.h>

#include "snprintf/mysnprintf.h"
#include "thingtype.h"

#define OPTPARSE_IMPLEMENTATION 1
#include "optparse.h"

#include <vld.h>

static pixel_t *
pixel_at(bitmap_t *bitmap, int x, int y)
{
	return bitmap->pixels + bitmap->width * x + y;
}

static thingtypelist_t *
load_dat(const char *f, int *maxCount)
{
	uint16 thingTypes[ThingLastCategory];

	FILE *fp;
	thingtype_t *n;
	thingtypelist_t *list, *listTail;
	uint16 id;
	int category;

	uint32 datSignature;
	uint16 contentRevision;

	uint16 itemsCount, creaturesCount, effectsCount, missilesCount;
	uint16 total;

	fp = fopen(f, "rb");
	if (!fp)
		return NULL;

	if (!(list = thingtypelist_init()))
	{
		fclose(fp);
		return NULL;
	}
	listTail = list;

	fread(&datSignature, 4, 1, fp);         /* dat signature */
	contentRevision = (uint16)(datSignature);

	total = 0;
	for (category = 0; category < ThingLastCategory; ++category)
	{
		uint16 count;
		fread(&count, 2, 1, fp);
		thingTypes[category] = count;
		total += count;

		if (category == ThingCategoryItem)
			total = total - 100 + 1;
	}

	itemsCount = thingTypes[ThingCategoryItem];     /* item count */
	creaturesCount = thingTypes[ThingCategoryCreature]; /* outfit count */
	effectsCount = thingTypes[ThingCategoryEffect];   /* effects count */
	missilesCount = thingTypes[ThingCategoryMissile];   /* missiles count(distance) */

	fprintf(stderr, "DatVer:%d Items: %d Creatures: %d Effects: %d Missiles: %d --  Total: %d\n",
		    contentRevision, itemsCount, creaturesCount, effectsCount, missilesCount, total);

	/* the first item(ID = 100) */
	for (category = 0; category < ThingLastCategory; ++category) {
		uint16 firstId = 1;
		if (category == ThingCategoryItem)
			firstId = 100;

		for (id = firstId; id <= thingTypes[category]; ++id) {
			n = thingtype_unserialize(fp, id, category);
			if (!n) {
				fprintf(stderr, "Failed to unserialize dat item %hd.\n", id);
				goto out;
			}

			thingtypelist_append(listTail, n);
			listTail = &(*listTail)->next;
			++(*maxCount);
		}
	}

out:
	fclose(fp);
	return list;
}

static buffer_t *
load_spr(const char *f, int *off, int *total)
{
	buffer_t *bp;
	uint32 signature;
	int spritesCount;
	int spritesOffset;

	bool bGameSpritesU32;

	bGameSpritesU32 = false;

	bp = balloc(f);
	if (!bp)
		return NULL;

	signature = bget32(bp);

	if (g_game_feature_bGameSpritesU32) {
		spritesCount = bget32(bp);
	}
	else {
		spritesCount = bget16(bp);
	}

	spritesOffset = btell(bp);

	*off = spritesOffset;
	*total = spritesCount;
	return bp;
}

/** Based on OTClient's sprite loading.  Writes pixel into @bitmap  */
#define SPRITE_DATA_SIZE 32 * 32 * 4
static bool 
spr_write_pixels(uint16 spriteId, buffer_t *sp, int offset, int total, bitmap_t *bitmap)
{
	if (spriteId == 0)
		return false;

	bseek(sp, ((spriteId - 1) * 4) + offset);
	uint32 address  = bget32(sp);
	if (address == 0)
		return false;
	bseek(sp, address + 3);

	uint16 pixelSize = bget16(sp);
	uint16 x = 0, y = 0;
	int read = 0, writePos = 0, i;
	pixel_t *pixel;

	while (read < pixelSize && writePos < SPRITE_DATA_SIZE) {
		uint16 transparentPixels = bget16(sp);
		uint16 colorizedPixels   = bget16(sp);

		for (i = 0; i < transparentPixels && writePos < SPRITE_DATA_SIZE; ++i) {
			pixel = pixel_at(bitmap, x, y);
			pixel->red = pixel->green = pixel->blue = pixel->alpha = 0x00;

			if (x < 31)
				++x;
			else {
				x = 0;
				++y;
			}

			writePos += 4;
		}

		for (i = 0; i < colorizedPixels && writePos < SPRITE_DATA_SIZE; ++i) {
			pixel = pixel_at(bitmap, x, y);
			pixel->red   = bgetc(sp);
			pixel->green = bgetc(sp);
			pixel->blue  = bgetc(sp);
			pixel->alpha = 0xFF;

			if (x < 31)
				++x;
			else {
				x = 0;
				++y;
			}

			writePos += 4;
		}

		read += 4 + (3 * colorizedPixels);
	}

	while (writePos < SPRITE_DATA_SIZE) {
		pixel = pixel_at(bitmap, x, y);
		pixel->red = pixel->green = pixel->blue = pixel->alpha = 0x00;

		if (x < 31)
			++x;
		else {
			x = 0;
			++y;
		}

		writePos += 4;
	}

	return true;
}

static bool 
save_png(bitmap_t *bitmap, const char *path)
{
	FILE *fp;
	png_structp png = NULL;
	png_infop info = NULL;
	size_t x, y;
	png_byte **rows = NULL;

	int pixelSize = 4;	/* rgba  */
	int depth = 8;

	fp = fopen(path, "wb");
	if (!fp)
		return false;

	png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png)
		return false;

	info = png_create_info_struct(png);
	if (!info) {
		png_destroy_write_struct(&png, &info);
		return false;
	}

	if (setjmp(png_jmpbuf(png))) {
		png_destroy_write_struct(&png, &info);
		return false;
	}

	png_set_IHDR(png,
		     info,
		     bitmap->width,
		     bitmap->height,
		     depth,
		     PNG_COLOR_TYPE_RGBA,
		     PNG_INTERLACE_NONE,
		     PNG_COMPRESSION_TYPE_DEFAULT,
		     PNG_FILTER_TYPE_DEFAULT
		    );

	rows = png_malloc(png, bitmap->height * sizeof(png_byte *));
	for (y = 0; y < bitmap->height; ++y) {
		png_byte *row =
			png_malloc(png, sizeof(uint8) * bitmap->width * pixelSize);
		rows[y] = row;
		for (x = 0; x < bitmap->width; ++x) {
			pixel_t *pixel = pixel_at(bitmap, x, y);
			*row++ = pixel->red;
			*row++ = pixel->green;
			*row++ = pixel->blue;
			*row++ = pixel->alpha;
		}
	}

	png_init_io(png, fp);
	png_set_rows(png, info, rows);
	png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);

	for (y = 0; y < bitmap->height; ++y)
		png_free(png, rows[y]);
	png_free(png, rows);

	png_destroy_write_struct(&png, &info);
	fclose(fp);
	return true;
}

static void 
makedir(const char *__name)
{
	/* Check if the directory already exists.  */
	struct stat st;
	if (stat(__name, &st) == 0)
		return;

		printf("Creating directory %s... ", __name);
#ifdef _WIN32
	if (_mkdir(__name) != 0)
#else
	if (mkdir(__name, 0777) != 0)
#endif
		critical("Failed!");
		printf("Success\n");
}

int 
main(int argc, char *argv[])
{
	char *dumpFolder = NULL;

	/*int option;*/
	struct optparse options;
	
	optparse_init(&options, argv);
	/*
	while ((option = optparse(&options, ":")) != -1) {
		switch (option) {
		case 'f':
			dumpFolder = options.optarg;
			break;

		case '?':
			fprintf(stderr, "%s: %s\n", argv[0], options.errmsg);
			exit(EXIT_FAILURE);
		}
	}*/

	char *arg;
	while ((arg = optparse_arg(&options))) {
		dumpFolder = arg;
		break;
	}

	if (NULL == dumpFolder)
		critical("Usage: %s <folder to dump into>", argv[0]);

	set_client_version(1098);

	thingtypelist_t *list;
	thingtype_t *it;
	int maxCount = 0;

	if (!(list = load_dat("./Tibia.dat", &maxCount)))
		critical("Failed to load Tibia.dat!");

	int sp_off;
	int sp_total;
	buffer_t *sp_buffer = load_spr("./Tibia.spr", &sp_off, &sp_total);
	if (!sp_buffer)
		critical("Failed to load Tibia.spr!");

	printf("Total sprites found in Tibia.spr: %hd\n", sp_total);
	{
		/* Make the directories:
		 * - dumpFolder
		 * - dumpFolder/Items
		 * - dumpFolder/Creatures  */
		makedir(dumpFolder);

		char tmpf[512];

		snprintf(tmpf, sizeof(tmpf), "%s\\Items", dumpFolder);
		makedir(tmpf);

		snprintf(tmpf, sizeof(tmpf), "%s\\Creatures", dumpFolder);
		makedir(tmpf);

		snprintf(tmpf, sizeof(tmpf), "%s\\Effects", dumpFolder);
		makedir(tmpf);

		snprintf(tmpf, sizeof(tmpf), "%s\\Missiles", dumpFolder);
		makedir(tmpf);
	}

#define MAX_FAILED_SIZE (1<<13)
	int count = 0, countFailed = 0, i, num;
	uint32 failedIds[MAX_FAILED_SIZE];
	char *type;

	printf("Now dumping sprites into %s (This may take some time)...\n", dumpFolder);
	fflush(stdout);

	foreach_thingtype(list, it) {
		/* Loop each sprite in this item, an item can have several
		 * sprites, for example if it's a creature it will have all
		 * of the possible creature directions. For an item
		 * it perhaps can contain the other parts if it's large (citation needed).  */
		switch (it->category) {
		case ThingCategoryItem:
			type = "Items";
			break;
		case ThingCategoryCreature:
			type = "Creatures";
			break;
		case ThingCategoryEffect:
			type = "Effects";
			break;
		case ThingCategoryMissile:
			type = "Missiles";
			break;
		default:
			type = "Unknown";
			break;
		}

		for (num = 0, i = 0; i < (int)it->spriteCount; ++i) {
			bitmap_t bmp;

			bmp.width = bmp.height = 32;
			bmp.pixels = calloc(sizeof(pixel_t), 32 * 32);
			if (!spr_write_pixels(it->spriteIds[i], sp_buffer, sp_off, sp_total, &bmp)) {
				/* FIXME: Usually when the spr_write_pixels returns false, all of the
				 * item sprites are corrupt, which is extremely odd.
				 * This happens when loading Tibia files of 8.6, haven't tested
				 * with any other Tibia version.  */
				assert(countFailed < MAX_FAILED_SIZE);
				failedIds[countFailed++] = it->id;
				free(bmp.pixels);
				break;
			}

			char filename[512];
			/* ./dumpFolder/ItemType/ItemId_sNumSprite/  */
			if (!o_snprintf(filename, 512, "%s/%s/%d_s%3d.png", dumpFolder, type, it->id, num++))
				abort();
				if (!save_png(&bmp, filename))
				abort();

			free(bmp.pixels);
		}

		++count;
		if (!(count % 2))
			printf("\r[%3d%%]", 100 * count / maxCount);
		fflush(stdout);
	}

	printf("\n%d sprites were saved", count);
	if (countFailed) {
		FILE *out;
		printf(" and %d were corrupt", countFailed);

		out = fopen("corrupt_ids.txt", "w+");
		if (out) {
			fprintf(out, "Corrupt item ids:\n");
			fprintf(out, "A\tB\tC\tD\tE\n");
			for (i = 0, num = 0; i < countFailed; ++i) {
				fprintf(out, "%d\t", failedIds[i]);
				if (++num == 5) {
					fprintf(out, "\n");
					num = 0;
				}
			}

			fclose(out);
			printf(", successfully saved corrupt ids to corrupt_ids.txt");
		} else
			printf(", failed to save corrupt ids to corrupt_ids.txt");
	}
	putchar('\n');

	thingtypelist_destroy(list);
	bfree(sp_buffer);
	return 0;
}