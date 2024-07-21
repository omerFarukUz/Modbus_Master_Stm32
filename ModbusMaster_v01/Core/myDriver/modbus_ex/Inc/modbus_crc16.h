#include <stdint.h>
#ifndef MYDRIVER_MODBUS_EX_INC_MODBUS_CRC16_H_
#define MYDRIVER_MODBUS_EX_INC_MODBUS_CRC16_H_


uint16_t crc16_calculator(uint16_t crcVal , uint8_t data);
uint16_t crc16_calculateWithLookupTable(uint8_t *buffer , uint16_t length);


#endif /* MYDRIVER_MODBUS_EX_INC_MODBUS_CRC16_H_ */
