
#ifndef THINGTYPE_H
#define THINGTYPE_H

#include <stdio.h>
#include <stdbool.h>

#include "types.h"
#include "animator.h"

enum FrameGroupType {
    FrameGroupDefault = 0,
    FrameGroupIdle = FrameGroupDefault,
    FrameGroupMoving
};

enum ThingCategory {
    ThingCategoryItem = 0,
    ThingCategoryCreature,
    ThingCategoryEffect,
    ThingCategoryMissile,
    ThingInvalidCategory,
    ThingLastCategory = ThingInvalidCategory
};

enum ThingAttr {
    ThingAttrGround           = 0, /* ground tile is followed by a 2 byte value indicating the speed */
    ThingAttrGroundBorder     = 1,
    ThingAttrOnBottom         = 2,
    ThingAttrOnTop            = 3,
    ThingAttrContainer        = 4,
    ThingAttrStackable        = 5,
    ThingAttrForceUse         = 6,
    ThingAttrMultiUse         = 7,
    ThingAttrWritable         = 8,
    ThingAttrWritableOnce     = 9, /* writeable is followed by a 2 byte value indicating the max text length */
    ThingAttrFluidContainer   = 10,
    ThingAttrSplash           = 11,
    ThingAttrNotWalkable      = 12,
    ThingAttrNotMoveable      = 13,
    ThingAttrBlockProjectile  = 14,
    ThingAttrNotPathable      = 15,
    ThingAttrPickupable       = 16,
    ThingAttrHangable         = 17,
    ThingAttrHookSouth        = 18,
    ThingAttrHookEast         = 19,
    ThingAttrRotateable       = 20,
    ThingAttrLight            = 21,
    ThingAttrDontHide         = 22,
    ThingAttrTranslucent      = 23,
    ThingAttrDisplacement     = 24,
    ThingAttrElevation        = 25,
    ThingAttrLyingCorpse      = 26,
    ThingAttrAnimateAlways    = 27,
    ThingAttrMinimapColor     = 28,
    ThingAttrLensHelp         = 29,
    ThingAttrFullGround       = 30,
    ThingAttrLook             = 31,
    ThingAttrCloth            = 32,
    ThingAttrMarket           = 33,
    ThingAttrUsable           = 34,
    ThingAttrWrapable         = 35,
    ThingAttrUnwrapable       = 36,
    ThingAttrTopEffect        = 37,

    // additional
    ThingAttrOpacity          = 100,
    ThingAttrNotPreWalkable   = 101,

    ThingAttrFloorChange      = 252,
    ThingAttrNoMoveAnimation  = 253, // 10.10: real value is 16, but we need to do this for backwards compatibility
    ThingAttrChargeable       = 254, // deprecated
    ThingLastAttr             = 255
};

enum SpriteMask {
    SpriteMaskRed = 1,
    SpriteMaskGreen,
    SpriteMaskBlue,
    SpriteMaskYellow
};

struct MarketData {
    char name[512];
    int category;
    uint16 requiredLevel;
    uint16 restrictVocation;
    uint16 showAs;
    uint16 tradeAs;
};

struct Light {
    /*Light() { intensity = 0; color = 215; }*/
    uint16 intensity;
    uint16 color;
};

typedef struct point_int16_s
{
	int16 x, y;
} point_t;

typedef struct attrib_s
{
	bool bMarketDataPtr;
	union {
		bool b;
		int a;
		int elevation;
		struct Light l;
		struct MarketData *market;
	};
} attrib_t;

typedef struct thingtype
{
	uint16 id;
	enum ThingCategory category;
	attrib_t attribs[ThingLastAttr];
	bool isNull;

	point_t displacement;
	int animationPhases;
	uint8 width, height;
	uint8 realSize;
	int exactSize;
	uint8 layers, numPatternX, numPatternY, numPatternZ;
	animator_t *animator;

	int spriteCount;
	uint32 *spriteIds;

	struct thingtype *next;
} thingtype_t;

typedef thingtype_t *thingtypelist_t;
#define foreach_thingtype(list, i)	\
	for ((i) = *(list); (i); (i) = (i)->next)

typedef struct
{
	uint8 red;
	uint8 green;
	uint8 blue;
	uint8 alpha;
} pixel_t;

typedef struct
{
	pixel_t *pixels;
	size_t width;
	size_t height;
} bitmap_t;

#ifdef __GNUC__
__attribute__((__noreturn__, __format__(__printf__, 1, 2)))
#endif
void critical(const char *errmsg, ...);

extern int g_client_version;
extern bool g_game_feature_bGameIdleAnimations;
extern bool g_game_feature_bGameEnhancedAnimations;
extern bool g_game_feature_bGameSpritesU32;

void set_client_version(int version);

thingtype_t * thingtype_new(uint16 id, enum ThingCategory category);
void thingtype_destroy(thingtype_t *i);

thingtypelist_t * thingtypelist_init(void);
void thingtypelist_destroy(thingtypelist_t *list);
void thingtypelist_append(thingtypelist_t *listTail, thingtype_t *newItem);

thingtype_t * thingtype_unserialize(FILE *fp, uint16 clientId, enum ThingCategory category);

#endif
