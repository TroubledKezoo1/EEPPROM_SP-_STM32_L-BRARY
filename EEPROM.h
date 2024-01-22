/*
 * EEPROM.h
 *
 *  Created on: Sep 2, 2022
 *      Author: yunus
 */
#include "stdio.h"
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "application.h"

typedef enum
{
  OFF= 0U,
  ON

}PinState;

typedef struct ChipSelect_portpin{

	GPIO_TypeDef	 *GPIOx;

	uint16_t		  GPIO_PIN;

}CS;

typedef struct WriteProtect_portpin{

	GPIO_TypeDef	 *GPIOx;

	uint16_t		  GPIO_PIN;

}WP;

typedef struct command{

	uint8_t	 		    Read;

	uint8_t		  		Write;

}CMD;

typedef struct eeprom{


    SPI_HandleTypeDef   *hspi;

	uint8_t 		     AdresByteType;

	uint32_t		     Adress;

		  CS            *PinName;

		  WP 		    *PinName_WP;

		  CMD		    *Command;


}EEPROM;

void CS_Moment_Set 		( PinState gpio, EEPROM *EeproM  );
void WP_Moment_Set 		( PinState gpio, EEPROM *EeproM  );

PinState CS_Moment_Get  ( EEPROM *EeproM  );
PinState WP_Moment_Get  ( EEPROM *EeproM  );

void EEPROM_WRITE_8     ( EEPROM *EeproM, uint32_t adres, uint8_t  Veri  );
void EEPROM_WRITE_16    ( EEPROM *EeproM, uint32_t adres, uint16_t Veri  );
void EEPROM_WRITE_32    ( EEPROM *EeproM, uint32_t adres, uint32_t Veri  );
void EEPROM_WRITE_Nbyte ( EEPROM *EeproM, uint32_t adres, uint8_t *Veri, uint8_t adet);
void EEPROM_READ_Nbyte  ( EEPROM *EeproM, uint32_t adres, uint8_t *Veri, uint8_t adet);
uint8_t  EEPROM_READ_8  ( EEPROM *EeproM, uint32_t adres  );
uint16_t EEPROM_READ_16 ( EEPROM *EeproM, uint32_t adres  );
uint32_t EEPROM_READ_32 ( EEPROM *EeproM, uint32_t adres  );

