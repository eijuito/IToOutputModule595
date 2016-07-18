/*
   Nome do Aquivo:   IToOutputModule595-YYYYMMDDa.cpp
   Descrição:        Library to expand output ports using 74HC595
   Versao do Aquivo: 20160602
   Dependências:     N/A
   MCU:              ATMEGA 328P 16 MHz
   Board:            Arduino Uno/Mega/Mini
   Compilador        N/A
   IDE:              Eclipse Mars CDT 8.8.1 com plugin Arduino C++ Jantje Baeyens 3.0.0
   Hardware:         Arduino UNO
   Escrito por:      Celso Eiju Ito - eijuito@gmail.com
   Colaboradores:    Rui Viana - ruianaiv@gmail.com
   Data:             2016-06-23
   Uso:              IToPeggou
   Diagrams:         N/A
   Copyright ®       2016 Celso Eiju Ito eijuito@gmail.com (www.itosa.com.br)
                     Este programa e de propriedade do Celso Eiju Ito eijuito@gmail.com
                     E vedada a copia total ou parcial por pessoas nao autorizadas
                     Nao e permitida a comercializacao ou locacao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   REVISIONS: (latest entry first) See IToOutputModule595.h
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "IToOutputModule595.h"

IToOutputModule595::IToOutputModule595(uint8_t moduleQty, uint8_t pinData, uint8_t pinClock) {
	_pinData = pinData;
	_pinClock = pinClock;
	pinMode(_pinData, OUTPUT);
	pinMode(_pinClock, OUTPUT);
	if(_pinClock == 255) {
		digitalWrite(_pinData, HIGH);
	} else {
		digitalWrite(_pinData, LOW);
		digitalWrite(_pinClock, LOW);
	}
	// Caso o _moduleQty for 255, sera ativado o modo sem pino de clock
	_moduleQty = moduleQty;
#ifdef ITOOUTPUTMODULE595_DEBUG
	Serial.print("Constructor Data:");
	Serial.print(_pinData);
	Serial.print(" , Clock:");
	Serial.print(_pinClock);
	Serial.print(" , moduleQty:");
	Serial.println(_moduleQty);
#endif
	ResetAll();
}

uint8_t IToOutputModule595::ResetAll(void) {
	for (uint8_t i = 0; i < _moduleQty; ++i)
		SetModule(0, i); // default all LOW
	return 1; // true
}

uint8_t IToOutputModule595::NumModules() {
	return _moduleQty;
}

uint8_t IToOutputModule595::GetModule(uint8_t module) {
	return _data[module];
}

uint8_t IToOutputModule595::SetModule(uint8_t value, uint8_t module) {
	if(module >= _moduleQty) return 0; // false
	_data[module] = value;
	PrivateSend();
	return 1; // true
}

uint8_t IToOutputModule595::GetOutput(uint8_t pin, uint8_t module) { // zero based
	module += pin / 8;
	pin = pin % 8;
	if (pin < 0 || (module > _moduleQty)) return UNDEF;
	byte mask = (1 << pin);
	if(mask & _data[module]) return HIGH;
	else return LOW;
}

uint8_t IToOutputModule595::SetOutput(uint8_t pin, uint8_t state, uint8_t module) {
	if(pin > 7) {
		module += pin / 8;
		pin = pin % 8;
	}
	if(module >= _moduleQty) return 0; // false
	byte mask = (1 << pin);
	if(state == HIGH) _data[module] |= mask;
	else _data[module] &= ~mask;
	PrivateSend();
	return 1; // true
}

const char* IToOutputModule595::Version() {
	return ITOOUTPUTMODULE595_VERSION;
}

// Send the data
void IToOutputModule595::PrivateSend(void){
	byte mask;
	if(_pinClock == 255) { // If is working without pinClock
		for (uint8_t module = 0; module < _moduleQty; ++module) { // for each module

			mask = 0x80; // set first bit 1000 0000
			for (uint8_t bit = 0; bit < 8; ++bit) { // for each bit of the module
				if(_data[_moduleQty - module - 1] & mask) {
					digitalWrite(_pinData, LOW);
					delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_BITON);
				} else {
					digitalWrite(_pinData, LOW);
					delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_BITOFF);
				}
				digitalWrite(_pinData, HIGH);
				delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_SHIFT);

				if((bit == 7) && (module == (_moduleQty - 1))) delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_LATCH); // delay big to allow latch
				else delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_SHIFT); // delay small to just shift

				mask >>= 1; // update mask for next bit
			} // end for each bit of the module

		}  // end for each module
	} else { // If is working without pinClock
		for (uint8_t module = 0; module < _moduleQty; ++module) { // for each module

			mask = 0x80; // set first bit 1000 0000
			for (uint8_t bit = 0; bit < 8; ++bit) { // for each bit of the module
				if(_data[_moduleQty - module - 1] & mask) digitalWrite(_pinData, HIGH); // set Data pin
				else digitalWrite(_pinData, LOW);

				delayMicroseconds(ITOOUTPUTMODULE595_DELAY_DATA); // delay between Data and Clock signals

				digitalWrite(_pinClock, HIGH); // set Clock pin rising edge
				if((bit == 7) && (module == (_moduleQty - 1))) delayMicroseconds(ITOOUTPUTMODULE595_DELAY_LATCH); // delay big to allow latch
				else delayMicroseconds(ITOOUTPUTMODULE595_DELAY_CLOCK_HIGH); // delay small to just shift
				digitalWrite(_pinClock, LOW);

				delayMicroseconds(ITOOUTPUTMODULE595_DELAY_CLOCK_LOW); // it is acceptable to have 5Âµs delay after the last bit has been sent
				mask >>= 1; // update mask for next bit
			} // end for each bit of the module

		}  // end for each module
		digitalWrite(_pinData, LOW); // reset to maintain LOW level when not in use
	}
}
