#ifndef CRC_H
#define CRC_H

#include "board.h"

uint8_t crcCheck(uint8_t *data, uint8_t length);
void crcAppend(uint8_t *data, uint8_t length);

#endif
