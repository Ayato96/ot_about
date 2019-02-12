#include "thingtype.h"

#include <stdlib.h>
#include "itemtype.h"

#define CLIENT_VERSION 1098

#define _MAX(a,b) (((a) > (b)) ? (a) : (b))
#define _MIN(a,b) (((a) < (b)) ? (a) : (b))

static pixel_t *
pixel_at(bitmap_t *bitmap, int x, int y)
{
	return bitmap->pixels + bitmap->width * x + y;
}

static
#ifdef __GNUC__
	__attribute__((__noreturn__, __format__(__printf__, 1, 2)))
#endif
void 
critical(const char *errmsg, ...)
{
	va_list va;
	int len;
	char outmsg[4096];

	va_start(va, errmsg);
	len = o_vsnprintf(outmsg, 4096, errmsg, va);
	va_end(va);

	if (len < 0)
		abort ();

	puts(outmsg);
	puts("Error is not recoverable, aborting now...");
	exit(EXIT_FAILURE);
}

static thingtype_t *
thingtype_new(uint16 id, enum ThingCategory category)
{
	thingtype_t *n;
	if (!(n = malloc(sizeof(*n))))
		return NULL;

	memset(n, 0, sizeof(*n));

	n->id = id;
	n->category = category;
	return n;
}

static __inline void 
thingtype_destroy(thingtype_t *i)
{
	free(i->spriteIds);
	free(i);
}

static thingtypelist_t *
thingtype_init(void)
{
	thingtype_t *ret;

	ret = calloc(1, sizeof(*ret));
	if (!ret)
		return NULL;

	return ret;
}

static void 
thingtypelist_destroy(thingtypelist_t *list)
{
	thingtype_t *tmp, *p;

	tmp = *list;
	while (tmp) {
		p = tmp->next;
		item_destroy(tmp);
		tmp = p;
	}

	free(list);
}

static void 
thingtypelist_append(thingtypelist_t *list, thingtype_t *newItem)
{
	newItem->next = *list;
	*list = newItem;
}

static int
read_string(FILE *fp, char *buffer, size_t buffer_size)
{
	uint16 len;

	fread(&len, 2, 1, fp);
	if (len > 0 && len < buffer_size) {
		return fread(buffer, len, 1, fp);
	}
	return -1;
}

thingtype_t *
thingtype_unserialize(FILE *fp, uint16 clientId, enum ThingCategory category)
{
	thingtype_t *ret;
	enum ItemCategory iCategory;
	uint32 flags;
	int attr, count, i;
	bool done;

	if (!(ret = thingtype_new(clientId, category))) {
		fclose(fp);
		critical("Can't allocate new item of size %d (id %d)(category %d)", 
			     sizeof(*ret), clientId, category);
	}

	count = 0;
	attr = -1,
	done = false;

	for (i = 0; i < ThingLastAttr; ++i) {
		++count;

		/* The end of the flag values are indicated by a 0xFF byte */
		attr = fgetc(fp);
		if (attr == ThingLastAttr) {
			done = true;
			break;
		}

		if (CLIENT_VERSION >= 1000) {
			/* In 10.10+ all attributes from 16 and up were
			* incremented by 1 to make space for 16 as
			* "No Movement Animation" flag.
			*/
			if (attr == 16)
				attr = ThingAttrNoMoveAnimation;
			else if (attr > 16)
				attr -= 1;
		}
		else if (CLIENT_VERSION >= 860) {
			/* Default attribute values follow
			* the format of 8.6-9.86.
			* Therefore no changes here.
			*/
		}
		else if (CLIENT_VERSION >= 780) {
			/* In 7.80-8.54 all attributes from 8 and higher were
			* incremented by 1 to make space for 8 as
			* "Item Charges" flag.
			*/
			if (attr == 8) {
				ret->attribs[ThingAttrChargeable].a = true;
				continue;
			}
			else if (attr > 8)
				attr -= 1;
		}
		else if (CLIENT_VERSION >= 755) {
			/* In 7.55-7.72 attributes 23 is "Floor Change". */
			if (attr == 23)
				attr = ThingAttrFloorChange;
		}
		else if (CLIENT_VERSION >= 740) {
			/* In 7.4-7.5 attribute "Ground Border" did not exist
			* attributes 1-15 have to be adjusted.
			* Several other changes in the format.
			*/
			if (attr > 0 && attr <= 15)
				attr += 1;
			else if (attr == 16)
				attr = ThingAttrLight;
			else if (attr == 17)
				attr = ThingAttrFloorChange;
			else if (attr == 18)
				attr = ThingAttrFullGround;
			else if (attr == 19)
				attr = ThingAttrElevation;
			else if (attr == 20)
				attr = ThingAttrDisplacement;
			else if (attr == 22)
				attr = ThingAttrMinimapColor;
			else if (attr == 23)
				attr = ThingAttrRotateable;
			else if (attr == 24)
				attr = ThingAttrLyingCorpse;
			else if (attr == 25)
				attr = ThingAttrHangable;
			else if (attr == 26)
				attr = ThingAttrHookSouth;
			else if (attr == 27)
				attr = ThingAttrHookEast;
			else if (attr == 28)
				attr = ThingAttrAnimateAlways;

			/* "Multi Use" and "Force Use" are swapped */
			if (attr == ThingAttrMultiUse)
				attr = ThingAttrForceUse;
			else if (attr == ThingAttrForceUse)
				attr = ThingAttrMultiUse;
		}

		switch (attr) {
		case ThingAttrDisplacement: {
			if (CLIENT_VERSION >= 755) {
				fread(&ret->displacement.x, 2, 1, fp);
				fread(&ret->displacement.y, 2, 1, fp);
			}
			else {
				ret->displacement.x = 8;
				ret->displacement.y = 8;
			}
			ret->attribs[attr].b = true;
			break;
		}
		case ThingAttrLight: {
			struct Light light;
			fread(&light.intensity, 2, 1, fp);
			fread(&light.color, 2, 1, fp);
			ret->attribs[attr].l = light;
			break;
		}
		case ThingAttrMarket: {
			struct MarketData *market;
			market = malloc(sizeof(*market));
			fread(&market->category, 2, 1, fp);
			fread(&market->tradeAs, 2, 1, fp);
			fread(&market->showAs, 2, 1, fp);
			read_string(fp, market->name, sizeof(market->name));
			fread(&market->restrictVocation, 2, 1, fp);
			fread(&market->requiredLevel, 2, 1, fp);
			ret->attribs[attr].market = market;
			break;
		}
		case ThingAttrElevation: {
			uint16 elevation;
			fread(&elevation, 2, 1, fp);
			ret->attribs[attr].elevation = elevation;
			break;
		}
		case ThingAttrUsable:
		case ThingAttrGround:
		case ThingAttrWritable:
		case ThingAttrWritableOnce:
		case ThingAttrMinimapColor:
		case ThingAttrCloth:
		case ThingAttrLensHelp:
			fread(&attr, 2, 1, fp);
			ret->attribs[attr].a = attr;
			break;
		default:
			ret->attribs[attr].b = true;
			break;
		};
	}

	if (!done)
		critical("corrupt data (id: %d, category: %d, count: %d, lastAttr: %d)",
			     clientId, category, count, attr);

	bool bGameIdleAnimations, bGameEnhancedAnimations, bGameSpritesU32;
	bGameIdleAnimations = false;
	bGameEnhancedAnimations = false;
	bGameSpritesU32 = false;

	if (CLIENT_VERSION >= 1057) {
		bGameIdleAnimations = true;
	}

	if (CLIENT_VERSION >= 1050) {
		bGameEnhancedAnimations = true;
	}

	if (CLIENT_VERSION >= 960) {
		bGameSpritesU32 = true;
	}

	bool hasFrameGroups = (category == ThingCategoryCreature && bGameIdleAnimations);
	uint8 groupCount = hasFrameGroups ? fgetc(fp) : 1;

	ret->animationPhases = 0;
	int totalSpritesCount = 0;

	for (int i = 0; i < groupCount; ++i) {
		uint8 frameGroupType = FrameGroupDefault;
		if (hasFrameGroups)
			frameGroupType = fgetc(fp);

		ret->width = fgetc(fp);
		ret->height = fgetc(fp);
		if (ret->width > 1 || ret->height > 1) {
			ret->realSize = fgetc(fp);
			ret->exactSize = _MIN(ret->realSize, _MAX(ret->width * 32, ret->height * 32));
		}
		else
			ret->exactSize = 32;

		ret->layers = fgetc(fp);
		ret->numPatternX = fgetc(fp);
		ret->numPatternY = fgetc(fp);
		if (CLIENT_VERSION >= 755)
			ret->numPatternZ = fgetc(fp);
		else
			ret->numPatternZ = 1;

		int groupAnimationsPhases = fgetc(fp);
		ret->animationPhases += groupAnimationsPhases;

		if (groupAnimationsPhases > 1 && bGameEnhancedAnimations) {
			ret->animator = animator_unserialize(fp, groupAnimationsPhases);
		}

		int totalSprites = ret->width * ret->height * ret->layers * ret->numPatternX * ret->numPatternY * ret->numPatternZ * groupAnimationsPhases;
		if (!(ret->spriteIds = calloc(ret->spriteCount, sizeof(uint16))))
			critical("Cannot allocate sprite ids of count %d (item id %d)",
				     ret->spriteCount, ret->id);

		if ((ret->spriteCount + totalSprites) > 4096)
			critical("A thing type has more than 4096 sprites");

		m_spritesIndex.resize((totalSpritesCount + totalSprites));
		for (int i = totalSpritesCount; i < (totalSpritesCount + totalSprites); i++)
			m_spritesIndex[i] = bGameSpritesU32 ? fin->getU32() : fin->getU16();

		ret->spriteCount += totalSprites;
	}


	category = (ItemCategory)fgetc(fp);

	fread(&flags, 4, 1, fp); /* flags */




		switch (attr) {
		case 0x00: /* ground tile is followed by a 2 byte value indicating the speed */
		case 0x09: /* writeable is followed by a 2 byte value indicating the max text length */
		case 0x0A: /* readable is followed by a 2 byte value indicating the max text length */
		case 0x1A: /* height is followed by a 2 byte value indicating the draw height(? ) */
		case 0x1D: /* minimap color is followed by a 2 byte value indicating the minimap color */
		case 0x1E: /* floor change? is followed by a 1 byte value indicating one of these values  (86 - openable holes, 
				   77 - can be used to go down, 76 - can be used to go up, 82 - stairs up, 79 - switch) then another 1 
				   byte value that always returns 4*/
			fseek(fp, 2, SEEK_CUR);
			break;

		case 0x16: /* light info is followed by a 2 byte value indicating the light level then another 2 byte value indicating the light color */
		case 0x19: /* draw offset is followed bye a 2 byte value indicating the x offset then another 2 byte value indicating the y offset */
			fseek(fp, 4, SEEK_CUR);


	ret->width  = fgetc(fp);
	ret->height = fgetc(fp);

	/* if the width or height is greater than 1 you have to skip the next byte then the byte after it is blend frames */
	if (ret->width > 1 || ret->height > 1)
		fgetc(fp);

	/* number of sprites (width * height * blend frames * divx * divy * divz * animation length) */
	uint8 blend_frames, divx, divy, divz, animation_length;
	blend_frames = fgetc(fp);
	divx = fgetc(fp);
	divy = fgetc(fp);
	divz = fgetc(fp);
	animation_length = fgetc(fp);

	ret->spriteCount = ret->width * ret->height * (int)blend_frames * (int)divx * (int)divy * (int)divz * (int)animation_length;
	if (!(ret->spriteIds = calloc(ret->spriteCount, sizeof(uint16))))
		critical("Cannot allocate sprite ids of count %d (item id %d)", ret->spriteCount, ret->id);

	int i;
	uint16 spriteId;
	size_t n;
	for (i = 0; i < (int)ret->spriteCount; ++i) {
		n = fread(&spriteId, 2, 1, fp);
		if (n != 1)
			continue;

		ret->spriteIds[i] = spriteId;
	}

	return ret;
}
