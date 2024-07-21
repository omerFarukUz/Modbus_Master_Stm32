/*
 * modbus_ex.h
 *
 *  Created on: Jul 15, 2024
 *      Author: UZLAR
 */

#ifndef MYDRIVER_MODBUS_EX_INC_MODBUS_EX_H_
#define MYDRIVER_MODBUS_EX_INC_MODBUS_EX_H_


#include "main.h"
#include <stdbool.h>
#include "modbus_crc16.h"
#include "timer_ex.h"
#include "RingBuffer.h"
#include <string.h>



#define MODBUS_TX_MAX_SIZE					252
#define MODBUS_RX_MAX_SIZE					64



typedef enum
{
	Read_Coil_Status			= 0x01,
	Read_Input_Status			= 0x02,
	Read_Holding_Registers		= 0x03,
	Read_Input_Registers		= 0x04,
	Write_Single_Coil			= 0x05,
	Write_Single_Register		= 0x06,
	Write_Multiple_Coils		= 0x0F,
	Write_Multiple_Registers	= 0x10

}Modbus_Function_Code_t;


typedef enum
{
	ASCII,
	RTU
}Modbus_Mode_t;

typedef struct
{
	uint8_t 					SlaveAddress;
	Modbus_Function_Code_t		FunctionCode;
	uint16_t					StartAddrress;
	uint16_t 					NumOfRegisters;
	uint8_t						MessageLength;
	uint8_t						TxData[MODBUS_TX_MAX_SIZE];
	uint16_t					WriteData[MODBUS_TX_MAX_SIZE];
	uint8_t						TxIndex;
	uint16_t					crc16;
	bool						NewSendMessageStatus;

}Modbus_Tx_Message_t;

typedef struct
{
	uint8_t 					SlaveAddress;
	uint8_t						FunctionCode;
	uint8_t 					RxData[MODBUS_RX_MAX_SIZE];
	uint8_t						MessageLength;
	Tick_Time_t					RxTime;
	uint8_t						RxIndex;
	uint16_t					crc16;
	bool						NewReceiveMessageStatus;

}Modbus_Rx_Message_t;;

typedef	enum
{
	Idle						= 0,
	Send_Request				= 1,
	Waiting_For_Reply   		= 2,
	Processing_Reply			= 3,
	Processing_Error			= 4

}Modbus_State_t;

typedef enum
{
	No_Error					= 0,
	Invalid_Function_Code		= 1,
	Invalid_Data_Address		= 2,
	Invalid_Data_Value			= 3,
	Slave_Device_Error			= 4,
	Info_Message				= 5,
	Invalid_CRC					= 6,
	Timeout						= 7

}Modbus_Error_Code_t;

typedef struct
{
	Modbus_Tx_Message_t			TxMessage;
	Modbus_Rx_Message_t			RxMessage;
	Modbus_Mode_t				Mode;
	Modbus_State_t				State;
	Modbus_Error_Code_t			Error;

}Modbus_t;

typedef enum
{
	Coil_Out_Status_Off			= 0x0000,
	Coil_Out_Status_On			= 0xFF00
}Modbus_Coil_Status_t;


void Modbus_Master_Control(Modbus_t *modbus);
void Modbus_Read_Coil_Status(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfCoils);
void Modbus_Read_Input_Status(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfInputs);
void Modbus_Read_Holding_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfregisters);
void Modbus_Read_Input_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfRegisters);
void Modbus_Write_Single_Coil(Modbus_t *modbus , uint8_t SlaveId , uint16_t numOfCoil , Modbus_Coil_Status_t status);
void Modbus_Write_Single_Register(Modbus_t *modbus , uint8_t SlaveId , uint16_t numOfRegister , uint16_t data);
void Modbus_Write_Multiple_Coils(Modbus_t *modbus , uint8_t SlaveId , uint16_t startAddress , float numOfCoils , uint16_t coilStatus);
void Modbus_Write_Multiple_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t startAddress , uint16_t numOfRegisters , uint16_t *data);
uint8_t Modbus_Master_Write(uint8_t *buffer , uint8_t length);
bool areelementsEqual(uint8_t *txArray , uint8_t *rxArray , uint8_t numOfElements);


#endif /* MYDRIVER_MODBUS_EX_INC_MODBUS_EX_H_ */
