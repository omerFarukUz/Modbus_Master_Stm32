#include "modbus_ex.h"
#include <math.h>

Tick_Time_t idleTime,waitResponseTime,errorTime;

extern UART_HandleTypeDef huart2;
extern RingBuffer_t	      usart2_InRb;


#define LSB(x)			(uint8_t)(x & 0xFF)
#define MSB(x)			(uint8_t)(x>>8)
#define bitRead(x,y)    (uint8_t)((x & (1 << y)) >> y) // okunacak data = x , okunacak datanin hangi biti oldugu = y.

uint8_t cikis10Durum;
uint8_t girisDurum1,girisDurum2,girisDurum3,girisDurum4,girisDurum5,komut_durum=0;
uint16_t analogValue[5];


void Modbus_Master_Control(Modbus_t *modbus)
{
	switch (modbus->State)
	{
		case Idle:
			// Bosta Durumu: Mesaj gondermeye hazir hale gelecek
			if((modbus->TxMessage.NewSendMessageStatus) && Tick_Timer_Check_Elapsed_Time(&idleTime))
			{

				// bir mesaj gonderilmeye hazir
				modbus->TxMessage.NewSendMessageStatus = false;
				modbus->State					= Send_Request;
				modbus->TxMessage.TxIndex		= 0;
				Tick_Timer_Stop_Time(&idleTime);

			}


			break;

		case Send_Request:
			// Sorgu talebi gonder
			// ADU
			modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = modbus->TxMessage.SlaveAddress;
			modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = modbus->TxMessage.FunctionCode;


			switch(modbus->TxMessage.FunctionCode)
			{
			case Read_Coil_Status:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);
				break;

			case Read_Input_Status:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);

				break;

			case Read_Holding_Registers:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);

				break;

			case Read_Input_Registers:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);

				break;

     		case Write_Single_Coil:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.WriteData[0]);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.WriteData[0]);

				break;

			case Write_Single_Register:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.WriteData[0]);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.WriteData[0]);

				break;

			case Write_Multiple_Coils:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.WriteData[0]);   // bayt sayisi
				break;

			case Write_Multiple_Registers:
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.StartAddrress);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.NumOfRegisters);
				modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.WriteData[0]);   // bayt sayisi

				for (int i = 1; i <= modbus->TxMessage.NumOfRegisters; i++)
				{
					modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.WriteData[i]);
					modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.WriteData[i]);

				}

				break;
			}

			modbus->TxMessage.crc16	= 0xFF;
			modbus->TxMessage.crc16 = crc16_calculateWithLookupTable(modbus->TxMessage.TxData, modbus->TxMessage.TxIndex);
			modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = LSB(modbus->TxMessage.crc16);
			modbus->TxMessage.TxData[modbus->TxMessage.TxIndex++] = MSB(modbus->TxMessage.crc16);

			Ring_Buffer_Clear(&usart2_InRb);

			Modbus_Master_Write(modbus->TxMessage.TxData , modbus->TxMessage.TxIndex);

			Tick_Timer_Set_Time(&waitResponseTime, 1000);

			modbus->State = Waiting_For_Reply;

			break;

		case Waiting_For_Reply:
			// Cevap bekle

			if(usart2_InRb.writePoint > 2)
				modbus->RxMessage.NewReceiveMessageStatus = true;

			if (modbus->RxMessage.NewReceiveMessageStatus)
			{
				// zamani durdur ve processing reply'e gec
				// gelen mesajin adres bilgisini al ve kontrol et
				modbus->RxMessage.SlaveAddress = usart2_InRb.pBuffer[0];

				if(modbus->RxMessage.SlaveAddress == modbus->TxMessage.SlaveAddress)
				{
					// yanit beklenen bagimli cihazdan cevap geldi , mesaji islemeye basla
					modbus->State = Processing_Reply;
					modbus->RxMessage.NewReceiveMessageStatus = false;

				}
				else
				{
					// gelen yanit baska bir cihazdan geldi , yoksay ve beklemeye devam et
					// ring buffer temizle
					Ring_Buffer_Clear(&usart2_InRb);
				}

			}
			else
			{
				if(Tick_Timer_Check_Elapsed_Time(&waitResponseTime))
				{
					modbus->Error = Timeout;
					modbus->State = Processing_Error;
					Tick_Timer_Set_Time(&errorTime, 1000);
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
				}
			}


			break;

		case Processing_Reply:
			// Beklenilen sure zarfinda cevap dogru sekilde gelirse ,islenir
			// 1 - Gelen mesajin fonksiyon kodunu al
			modbus->RxMessage.FunctionCode = usart2_InRb.pBuffer[1];
			// 2 - Gelen fonksiyon kodunu kontrol et
			if((modbus->RxMessage.FunctionCode & 0x7F) != modbus->TxMessage.FunctionCode )
			{
				modbus->Error = Invalid_Function_Code;
				modbus->State = Processing_Error;
				Tick_Timer_Set_Time(&errorTime, 1000);

			}

			// istisna mesaji kontrolu yap
			if (bitRead(modbus->RxMessage.FunctionCode , 7))
			{
				modbus->Error = usart2_InRb.pBuffer[2];
				modbus->State = Processing_Error;
				Tick_Timer_Set_Time(&errorTime, 1000);

			}

			// Gelen data uzunlugunu al
			if((modbus->RxMessage.MessageLength == 0) && (modbus->RxMessage.FunctionCode <= Read_Input_Registers))
			{
				modbus->RxMessage.MessageLength = usart2_InRb.pBuffer[2] + 5;
			}
			else if(modbus->RxMessage.FunctionCode >= Write_Single_Coil)
			{
				modbus->RxMessage.MessageLength = modbus->TxMessage.TxIndex;
				if (modbus->RxMessage.FunctionCode >= Write_Multiple_Coils || modbus->RxMessage.FunctionCode >= Write_Multiple_Registers)
				{
					modbus->RxMessage.MessageLength = 8;
				}
			}

			// wait all data
			if((usart2_InRb.writePoint >= modbus->RxMessage.MessageLength) && modbus->RxMessage.MessageLength != 0)
			{
				modbus->RxMessage.MessageLength = 0;

				// CRC kontrol yap

				modbus->RxMessage.crc16 = 0xFFFF;
				memcpy(modbus->RxMessage.RxData , usart2_InRb.pBuffer , usart2_InRb.writePoint);
				modbus->RxMessage.RxIndex = usart2_InRb.writePoint;
				modbus->RxMessage.crc16 = crc16_calculateWithLookupTable(modbus->RxMessage.RxData, (modbus->RxMessage.RxIndex - 2));

				if((LSB(modbus->RxMessage.crc16) != modbus->RxMessage.RxData[modbus->RxMessage.RxIndex - 2]) ||
				   (MSB(modbus->RxMessage.crc16) != modbus->RxMessage.RxData[modbus->RxMessage.RxIndex - 1]))
				{
					// CRC Error
					modbus->Error = Invalid_CRC;
					modbus->State = Processing_Error;
				}

				//Tum veriler dogru bir sekilde geldi ve bilgileri isle

				if (modbus->State != Processing_Error)
				{
					switch (modbus->RxMessage.FunctionCode)
					{
						case Read_Coil_Status:
							//. . .

							cikis10Durum = bitRead(modbus->RxMessage.RxData[3] , 0);
							break;

						case Read_Input_Status:
							//. . .

							girisDurum1 = bitRead(modbus->RxMessage.RxData[3] , 0);
							girisDurum2 = bitRead(modbus->RxMessage.RxData[3] , 1);
							girisDurum3 = bitRead(modbus->RxMessage.RxData[3] , 2);
							girisDurum4 = bitRead(modbus->RxMessage.RxData[3] , 3);
							girisDurum5 = bitRead(modbus->RxMessage.RxData[3] , 4);

							break;

	/*					case Read_Holding_Registers:
							//. . .

							uint8_t dataLength = modbus->RxMessage.RxData[2] / 2;
							uint8_t index = 3;

							for (int i = 0; i < dataLength; i++)
							{
																// LSB											// MSB
								analogValue[i] = ((modbus->RxMessage.RxData[(index + 1) + i])  | (modbus->RxMessage.RxData[i+index]<< 8));
								index += 1;
							}

							break;*/

						case Read_Input_Registers:
							//. . .

							uint8_t dataLength = modbus->RxMessage.RxData[2] / 2;
							uint8_t index = 3;

							for (int i = 0; i < dataLength; i++)
							{
																// LSB											// MSB
								analogValue[i] = ((modbus->RxMessage.RxData[(index + 1) + i])  | (modbus->RxMessage.RxData[i+index]<< 8));
								index += 1;
							}

							break;

						case Write_Single_Coil:
							// . . .
							if (areelementsEqual(modbus->TxMessage.TxData, modbus->RxMessage.RxData, modbus->TxMessage.TxIndex) == true)
							{
								// komut basarili calisti
							}
							else
							{
								// komut basarisiz oldu
							}
							break;

						case Write_Single_Register:
							// . . .
							if (areelementsEqual(modbus->TxMessage.TxData, modbus->RxMessage.RxData, modbus->TxMessage.TxIndex) == true)
							{
								// komut basarili calisti
							}
							else
							{
								// komut basarisiz oldu
							}
							break;

						case Write_Multiple_Coils:
							//. . .
							if(modbus->RxMessage.RxData[5] == modbus->TxMessage.NumOfRegisters)
							{
								// komut basarili calisti
							}
							else
							{
								// komut basarisiz oldu
							}
							break;

						case Write_Multiple_Registers:
							//. . .
							if(modbus->RxMessage.RxData[5] == modbus->TxMessage.NumOfRegisters)
							{
								// komut basarili calisti
								komut_durum = 1;
							}
							else
							{
								// komut basarisiz oldu
								komut_durum = 2;
							}
							break;

					}

					modbus->State = Idle;
				}


			}

			break;

		case Processing_Error:
			// Hata durumu yonetimi

			if (Tick_Timer_Check_Elapsed_Time(&errorTime))
			{
				modbus->State = Idle;
			}

			break;

		default:

			break;
	}

}

uint8_t Modbus_Master_Write(uint8_t *buffer , uint8_t length)
{
	HAL_GPIO_WritePin(TX_RX_EN1_GPIO_Port, TX_RX_EN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TX_RX_EN2_GPIO_Port, TX_RX_EN2_Pin, GPIO_PIN_SET);

	if(HAL_UART_Transmit(&huart2, buffer, length, HAL_MAX_DELAY) == HAL_OK)
	{
		HAL_GPIO_WritePin(TX_RX_EN1_GPIO_Port, TX_RX_EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TX_RX_EN2_GPIO_Port, TX_RX_EN2_Pin, GPIO_PIN_RESET);
		return HAL_OK;

	}
	else
	{
		HAL_GPIO_WritePin(TX_RX_EN1_GPIO_Port, TX_RX_EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TX_RX_EN2_GPIO_Port, TX_RX_EN2_Pin, GPIO_PIN_RESET);
		return HAL_ERROR;
	}
}

void Modbus_Read_Coil_Status(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfCoils)
{
	modbus->TxMessage.FunctionCode				= Read_Coil_Status;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= StartAddress;
	modbus->TxMessage.NumOfRegisters			= NumberOfCoils;


	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

void Modbus_Read_Input_Status(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfInputs)
{
	modbus->TxMessage.FunctionCode				= Read_Input_Status;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= StartAddress;
	modbus->TxMessage.NumOfRegisters			= NumberOfInputs;


	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

void Modbus_Read_Holding_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfRegisters)
{
	modbus->TxMessage.FunctionCode				= Read_Holding_Registers;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= StartAddress;
	modbus->TxMessage.NumOfRegisters			= NumberOfRegisters;


	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}
}

void Modbus_Read_Input_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t StartAddress , uint16_t NumberOfRegisters)
{
	modbus->TxMessage.FunctionCode				= Read_Input_Registers;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= StartAddress;
	modbus->TxMessage.NumOfRegisters			= NumberOfRegisters;


	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}
}

void Modbus_Write_Single_Coil(Modbus_t *modbus , uint8_t SlaveId , uint16_t numOfCoil , Modbus_Coil_Status_t status)
{
	modbus->TxMessage.FunctionCode				= Write_Single_Coil;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= numOfCoil;

	modbus->TxMessage.WriteData[0]				= status;

	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

void Modbus_Write_Single_Register(Modbus_t *modbus , uint8_t SlaveId , uint16_t numOfRegister , uint16_t data)
{
	modbus->TxMessage.FunctionCode				= Write_Single_Register;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= numOfRegister;

	modbus->TxMessage.WriteData[0]				= data;

	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus) )
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

void Modbus_Write_Multiple_Coils(Modbus_t *modbus , uint8_t SlaveId , uint16_t startAddress , float numOfCoils , uint16_t coilStatus)
{
	modbus->TxMessage.FunctionCode				= Write_Multiple_Coils;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= startAddress;
	modbus->TxMessage.NumOfRegisters			= numOfCoils;

	modbus->TxMessage.WriteData[0]				= (ceil(numOfCoils/8));
	modbus->TxMessage.WriteData[1]				= coilStatus;

	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus))
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

void Modbus_Write_Multiple_Registers(Modbus_t *modbus , uint8_t SlaveId , uint16_t startAddress , uint16_t numOfRegisters , uint16_t *data)
{
	modbus->TxMessage.FunctionCode				= Write_Multiple_Registers;
	modbus->TxMessage.SlaveAddress				= SlaveId;
	modbus->TxMessage.StartAddrress				= startAddress;
	modbus->TxMessage.NumOfRegisters			= numOfRegisters;

	modbus->TxMessage.WriteData[0]				= numOfRegisters * 2;

	for (int i = 0; i <= numOfRegisters; i++)
	{
		modbus->TxMessage.WriteData[i+1] = data[i];
	}

	if((modbus->State == Idle) && !(modbus->TxMessage.NewSendMessageStatus))
	{
		modbus->TxMessage.NewSendMessageStatus = true;
		Tick_Timer_Set_Time(&idleTime, 100);
	}

}

bool areelementsEqual(uint8_t *txArray , uint8_t *rxArray , uint8_t numOfElements)
{
	for (int i = 0; i < numOfElements; i++)
	{
		if (txArray[i] != rxArray[i])
		{
			return false;
		}
	}

	return true;
}
