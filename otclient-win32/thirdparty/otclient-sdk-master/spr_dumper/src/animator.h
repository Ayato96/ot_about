#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <stdbool.h>
#include <stdio.h>

#include "types.h"

enum AnimationPhase
{
    AnimPhaseAutomatic = -1,
    AnimPhaseRandom = 254,
    AnimPhaseAsync = 255,
};

enum AnimationDirection
{
    AnimDirForward = 0,
    AnimDirBackward = 1
};

typedef struct phase_duration_s
{
	int minimum, maximum;
} phase_duration_t;

typedef struct animator_s
{
	int animationPhases;
	int8 startPhase;
	int loopCount;
	bool async;

	phase_duration_t *phaseDurations;

	int currentDuration;
	enum AnimationDirection currentDirection;
	int currentLoop;

	ticks_t lastPhaseTicks;
	bool isComplete;

	int phase;

} animator_t;

animator_t * animator_unserialize(FILE *fp, int animationPhases);

#endif
