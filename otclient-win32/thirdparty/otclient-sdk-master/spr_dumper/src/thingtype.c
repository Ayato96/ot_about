#include "thingtype.h"

#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "snprintf/mysnprintf.h"
#include "itemtype.h"

#define _MAX(a,b) (((a) > (b)) ? (a) : (b))
#define _MIN(a,b) (((a) < (b)) ? (a) : (b))

int g_client_version;
bool g_game_feature_bGameIdleAnimations;
bool g_game_feature_bGameEnhancedAnimations;
bool g_game_feature_bGameSpritesU32;

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

void 
set_client_version(int version)
{
	g_client_version = version;
	g_game_feature_bGameIdleAnimations = false;
	g_game_feature_bGameEnhancedAnimations = false;
	g_game_feature_bGameSpritesU32 = false;

	if (g_client_version >= 1057) {
		g_game_feature_bGameIdleAnimations = true;
	}

	if (g_client_version >= 1050) {
		g_game_feature_bGameEnhancedAnimations = true;
	}

	if (g_client_version >= 960) {
		g_game_feature_bGameSpritesU32 = true;
	}
}

thingtype_t *
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

void 
thingtype_destroy(thingtype_t *i)
{
	free(i->spriteIds);
	free(i);
}

thingtypelist_t *
thingtypelist_init(void)
{
	thingtypelist_t *ret;

	ret = calloc(1, sizeof(*ret));
	if (!ret)
		return NULL;

	*ret = NULL;
	return ret;
}

void 
thingtypelist_destroy(thingtypelist_t *list)
{
	thingtype_t *tmp, *p;

	tmp = *list;
	while (tmp) {
		p = tmp->next;
		thingtype_destroy(tmp);
		tmp = p;
	}

	free(list);
}

void
thingtypelist_append(thingtypelist_t *listTail, thingtype_t *newItem)
{
	if (*listTail == NULL) {
		*listTail = newItem;
	}
	else {
		(*listTail)->next = newItem;
	}
}

static int
read_string(FILE *fp, char *buffer, size_t bufferSize)
{
	uint16 len;

	fread(&len, 2, 1, fp);
	if (len > 0 && len < bufferSize) {
		return fread(buffer, len, 1, fp);
	}
	return -1;
}

thingtype_t *
thingtype_unserialize(FILE *fp, uint16 clientId, enum ThingCategory category)
{
	thingtype_t *ret;
	int attr, count, i, j;
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

		if (g_client_version >= 1000) {
			/* In 10.10+ all attributes from 16 and up were
			* incremented by 1 to make space for 16 as
			* "No Movement Animation" flag.
			*/
			if (attr == 16)
				attr = ThingAttrNoMoveAnimation;
			else if (attr > 16)
				attr -= 1;
		}
		else if (g_client_version >= 860) {
			/* Default attribute values follow
			* the format of 8.6-9.86.
			* Therefore no changes here.
			*/
		}
		else if (g_client_version >= 780) {
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
		else if (g_client_version >= 755) {
			/* In 7.55-7.72 attributes 23 is "Floor Change". */
			if (attr == 23)
				attr = ThingAttrFloorChange;
		}
		else if (g_client_version >= 740) {
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
			if (g_client_version >= 755) {
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
			ret->attribs[attr].bMarketDataPtr = true;
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
		case ThingAttrLensHelp: {
			uint16 a;
			fread(&a, 2, 1, fp);
			ret->attribs[attr].a = a;
			break;
		}
		default:
			ret->attribs[attr].b = true;
			break;
		};
	}

	if (!done)
		critical("corrupt data (id: %d, category: %d, count: %d, lastAttr: %d)",
			     clientId, category, count, attr);

	bool hasFrameGroups = (category == ThingCategoryCreature && g_game_feature_bGameIdleAnimations);
	uint8 groupCount = hasFrameGroups ? fgetc(fp) : 1;

	ret->animationPhases = 0;
	int totalSpritesCount = 0;

	for (i = 0; i < groupCount; ++i) {
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
		if (g_client_version >= 755)
			ret->numPatternZ = fgetc(fp);
		else
			ret->numPatternZ = 1;

		int groupAnimationsPhases = fgetc(fp);
		ret->animationPhases += groupAnimationsPhases;

		if (groupAnimationsPhases > 1 && g_game_feature_bGameEnhancedAnimations) {
			ret->animator = animator_unserialize(fp, groupAnimationsPhases);
		}

		int totalSprites = ret->width * ret->height * ret->layers * ret->numPatternX * ret->numPatternY * ret->numPatternZ * groupAnimationsPhases;
		if ((ret->spriteCount + totalSprites) > 4096)
			critical("A thing type has more than 4096 sprites");

		int oldSpriteCount = ret->spriteCount;
		uint32 *oldSpriteIds = ret->spriteIds;

		ret->spriteCount += totalSprites;
		if (!(ret->spriteIds = calloc(ret->spriteCount, sizeof(uint32))))
			critical("Cannot allocate sprite ids of count %d (item id %d)",
				ret->spriteCount, ret->id);

		for (j = 0; j < oldSpriteCount; ++j)
			ret->spriteIds[j] = oldSpriteIds[j];
		free(oldSpriteIds);
		
		for (j = oldSpriteCount; j < ret->spriteCount; ++j) {
			if (g_game_feature_bGameSpritesU32) {
				uint32 spriteId;
				fread(&spriteId, 4, 1, fp);
				ret->spriteIds[j] = spriteId;
			}
			else {
				uint16 spriteId;
				fread(&spriteId, 2, 1, fp);
				ret->spriteIds[j] = spriteId;
			}
		}
	}

	return ret;
}
