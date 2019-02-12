#include "animator.h"

#include <stdlib.h>
#include <assert.h>
#include <time.h>

animator_t *
animator_unserialize(FILE *fp, int animationPhases)
{
	animator_t *ret;

	ret = malloc(sizeof(*ret));
    ret->animationPhases = animationPhases;

	int async = fgetc(fp);
	ret->async = (async == 0);
    ret->loopCount = fread(&ret->loopCount, 4, 1, fp);
	ret->startPhase = fgetc(fp);

	ret->phaseDurations = malloc(sizeof(phase_duration_t) * ret->animationPhases);

    for(int i = 0; i < ret->animationPhases; ++i) {
		phase_duration_t duration;
		fread(&duration.minimum, 4, 1, fp);
		fread(&duration.maximum, 4, 1, fp);
		ret->phaseDurations[i] = duration;
    }

	if (ret->startPhase > -1) {
		ret->phase = ret->startPhase;
	}
	else {
		/*srand(time(NULL));*/
		ret->phase = rand() % ret->animationPhases;
	}

    assert(ret->startPhase >= -1 && ret->startPhase < ret->animationPhases);
	return ret;
}
