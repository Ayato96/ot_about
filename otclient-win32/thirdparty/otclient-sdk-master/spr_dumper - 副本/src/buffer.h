#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

typedef struct buffer buffer_t;

extern buffer_t *balloc(const char *f);
extern void      bfree(buffer_t *b);

extern int       btell(const buffer_t *bp);
extern uint8_t   bgetc(buffer_t *bp);
extern uint16_t  bget16(buffer_t *bp);
extern uint32_t  bget32(buffer_t *bp);

extern void      bskip(buffer_t *bp, int size);
extern void	     bseek(buffer_t *bp, int pos);

#endif

