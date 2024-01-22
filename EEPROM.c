/*
 * EEPROM.c
 *
 *  Created on: Sep 2, 2022
 *      Author: yunus
 */
#include "main.h"
#include "spi.h"
#include "EEPROM.h"
#include "application.h"

void CS_Moment_Set 	 ( PinState gpio, EEPROM *EeproM ) {

	HAL_GPIO_WritePin(EeproM->PinName->GPIOx, EeproM->PinName->GPIO_PIN, gpio );

}

PinState CS_Moment_Get	   (EEPROM *EeproM) {

	return HAL_GPIO_ReadPin(EeproM->PinName->GPIOx, EeproM->PinName->GPIO_PIN);

}

void WP_Moment_Set(PinState gpio, EEPROM *EeproM) {
	HAL_GPIO_WritePin(EeproM->PinName_WP->GPIOx, EeproM->PinName_WP->GPIO_PIN,
			gpio);
}

PinState WP_Moment_Get(EEPROM *EeproM) {
	return HAL_GPIO_ReadPin(EeproM->PinName->GPIOx, EeproM->PinName->GPIO_PIN);
}

uint8_t EEPROM_READ_8(EEPROM *EeproM, uint32_t adres) {
	uint8_t GeneralBuffer[1] = { 0 };
	EEPROM_READ_Nbyte(EeproM, adres, GeneralBuffer, 1);
	return GeneralBuffer[0];
}
uint16_t EEPROM_READ_16(EEPROM *EeproM, uint32_t adres) {

	uint8_t GeneralBuffer[2] = { 0 };
	EEPROM_READ_Nbyte(EeproM, adres, GeneralBuffer, 2);
	uint16_t Data = GeneralBuffer[0] << 8 | GeneralBuffer[1];
	return Data;
}
uint32_t EEPROM_READ_32(EEPROM *EeproM, uint32_t adres) {

	uint8_t GeneralBuffer[4] = { 0 };

	EEPROM_READ_Nbyte(EeproM, adres, GeneralBuffer, 4);

	uint32_t Data = GeneralBuffer[0] << 24 | GeneralBuffer[1] << 16
			| GeneralBuffer[2] << 8 | GeneralBuffer[3];

	return Data;

}
void EEPROM_READ_Nbyte(EEPROM *EeproM, uint32_t adres, uint8_t *Veri,
		uint8_t adet) {

	uint8_t GeneralBuffer[255] = { 0 };
	GeneralBuffer[0] = EeproM->Command->Read;
	uint8_t indexCounter = 0;
	uint8_t Adress_process = (EeproM->AdresByteType - 1) * 8;
	for (uint8_t i = 1; i <= (EeproM->AdresByteType - 1); i++) {

		GeneralBuffer[i] = adres >> Adress_process;
		indexCounter = i;
		Adress_process -= 8;

	}
	indexCounter++;
	GeneralBuffer[indexCounter] = adres;
	indexCounter++;
	CS_Moment_Set	(OFF, EeproM);
	HAL_SPI_Transmit(EeproM->hspi, GeneralBuffer, indexCounter, 10);
	HAL_SPI_Receive (EeproM->hspi, Veri, adet, 10);
	CS_Moment_Set	( ON, EeproM);
}

void EEPROM_WRITE_Nbyte(EEPROM *EeproM, uint32_t adres, uint8_t *Veri,
		uint8_t adet) {

	uint8_t command[1] = { 0 };
	command[0] = 6;

	uint8_t GeneralBuffer[255] = { 0 };
	GeneralBuffer[0] = EeproM->Command->Write;

	uint8_t indexCounter = 0;
	uint8_t Adress_process = (EeproM->AdresByteType - 1) * 8;

	for (uint8_t i = 1; i <= (EeproM->AdresByteType - 1); i++) {

		GeneralBuffer[i] = adres >> Adress_process;
		indexCounter = i;
		Adress_process -= 8;
	}

	indexCounter++;
	GeneralBuffer[indexCounter] = adres;
	indexCounter++;

	for (uint8_t i = 0; i < adet; i++) {
		GeneralBuffer[indexCounter + i] = Veri[i];
	}
	indexCounter += adet;

	CS_Moment_Set(OFF, EeproM);
	HAL_SPI_Transmit(EeproM->hspi, command, 1, 10);
	CS_Moment_Set( ON, EeproM);

	CS_Moment_Set(OFF, EeproM);
	HAL_SPI_Transmit(EeproM->hspi, GeneralBuffer, indexCounter, 10);
	CS_Moment_Set (ON, EeproM);
	HAL_Delay(5);

}

void EEPROM_WRITE_8(EEPROM *EeproM, uint32_t adres, uint8_t Veri) {
	EEPROM_WRITE_Nbyte(EeproM, adres, &Veri, 1);
}

void EEPROM_WRITE_16(EEPROM *EeproM, uint32_t adres, uint16_t Veri) {
	uint8_t GeneralBuffer[2] = { 0 };

	GeneralBuffer[0] = Veri >> 8;
	GeneralBuffer[1] = Veri;

	EEPROM_WRITE_Nbyte(EeproM, adres, GeneralBuffer, 2);
}

void EEPROM_WRITE_32(EEPROM *EeproM, uint32_t adres, uint32_t Veri) {
	uint8_t GeneralBuffer[4] = { 0 };

	GeneralBuffer[0] = Veri >> 24;
	GeneralBuffer[1] = Veri >> 16;
	GeneralBuffer[2] = Veri >> 8;
	GeneralBuffer[3] = Veri;

	EEPROM_WRITE_Nbyte(EeproM, adres, GeneralBuffer, 4);
}

