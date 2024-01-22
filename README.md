{
// EXAMPLE

#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "application.h"
#include "EEPROM.h"
uint8_t  VeriBufferTX  [ 30 ] = { '#','S','E','L','A','M','#' }; //{'#','M','E','R','H','A','B','A','#'};
uint8_t  VeriBufferRX  [ 30 ];
CS   cs1 = { GPIOC, 0x0001U };
WP   wp1 = { GPIOA, 0x0040U };
CMD cmd1 = { 3, 2 };
uint8_t Veri8 = 0;
uint16_t Veri16 = 0;
uint32_t Veri32 = 0;
EEPROM eeprom1 = { &hspi1 , 2, 15, &cs1, &wp1, &cmd1 };

int main1(void){

	CS_Moment_Set ( ON, &eeprom1);
	HAL_GPIO_WritePin ( GPIO_CS_GPIO_Port, GPIO_CS_Pin, GPIO_PIN_SET   );

	//EEPROM_WRITE_Nbyte(&eeprom1,5,VeriBufferTX,15);
	//EEPROM_READ_Nbyte(&eeprom1,5,VeriBufferRX,15);

	//EEPROM_WRITE_8 (&eeprom1,5,16);
	//Veri8 = EEPROM_READ_8 ( &eeprom1, 5 );

	//EEPROM_WRITE_16 (&eeprom1,5,456);
	//Veri16 = EEPROM_READ_16 ( &eeprom1, 5 );

	//EEPROM_WRITE_32 (&eeprom1,5,123);
	//Veri32 = EEPROM_READ_32 ( &eeprom1, 5 );

		while(1)
		{


		}

}

}
