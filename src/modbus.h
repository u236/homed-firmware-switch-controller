#ifndef MODBUS_H
#define MODBUS_H

#define MODBUS_MAX_LENGTH                   0xFF
#define MODBUS_MAX_ADDRESS                  0xF7
#define MODBUS_MAX_COUNT                    0x7D

#define MODBUS_READ_HOLDING_REGISERS        0x03
#define MODBUS_READ_INPUT_REGISERS          0x04
#define MODBUS_WRITE_SINGLE_COIL            0x05
#define MODBUS_WRITE_SINGLE_REGISER         0x06
#define MODBUS_WRITE_MULTIPLE_REGISERS      0x10
#define MODBUS_REPORT_SLAVE_ID              0x11

#define MODBUS_ERROR_FUNCTION               0x01
#define MODBUS_ERROR_ADDRESS                0x02
#define MODBUS_ERROR_VALUE                  0x03
#define MODBUS_ERROR_FAILURE                0x04
#define MODBUS_ERROR_BUSY                   0x06

#include "board.h"

struct request_struct
{
    uint8_t address;
    uint8_t function;
    uint8_t *data;
};

void modbusHandler(uint8_t *frame, uint8_t length);

#endif
