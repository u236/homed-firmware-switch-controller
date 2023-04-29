#include "crc.h"

static uint16_t crcCalc(uint8_t *data, uint8_t length)
{
    uint16_t crc = 0xFFFF;

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t) *data++;

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 1)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }

    return crc;
}

uint8_t crcCheck(uint8_t *data, uint8_t length)
{
    uint16_t crc;
    memcpy(&crc, data + length - sizeof(crc), sizeof(crc));
    return crc == crcCalc(data, length - sizeof(crc));
}

void crcAppend(uint8_t *data, uint8_t length)
{
    uint16_t crc = crcCalc(data, length - sizeof(crc));
    memcpy(data + length - sizeof(crc), &crc, sizeof(crc));
}
