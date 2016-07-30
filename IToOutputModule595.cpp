/*
   Nome do Aquivo:   IToOutputModule595-YYYYMMDDa.cpp
   Descrição:        Library to expand output ports using 74HC595
   Data criada:      2016-06-23
   Versao do Aquivo: 2016-07-23
   Dependências:     IToOutputModule595.h
   Escrito por:      Celso Eiju Ito - eijuito@gmail.com
   MCU:              See IToOutputModule595.h
   Board:            See IToOutputModule595.h
   Compilador        See IToOutputModule595.h
   IDE:              See IToOutputModule595.h
   Hardware:         See IToOutputModule595.h
   Colaboradores:    See IToOutputModule595.h
   Uso:              See IToOutputModule595.h
   Diagrams:         See IToOutputModule595.h
   Copyright ®       See IToOutputModule595.h
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   REVISIONS: (latest entry first) See IToOutputModule595.h
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "IToOutputModule595.h"

#ifdef ITOOUTPUTMODULE595_MODE_1PORT
	IToOutputModule595::IToOutputModule595(uint8_t pinData, uint8_t moduleQty) {
		_pinData = pinData;
		pinMode(_pinData, OUTPUT);
		digitalWrite(_pinData, HIGH);
		_moduleQty = moduleQty;
		ResetAll();
	}
#endif // ITOOUTPUTMODULE595_MODE_1PORT
#ifdef ITOOUTPUTMODULE595_MODE_2PORTS
	IToOutputModule595::IToOutputModule595(uint8_t pinData, uint8_t pinClock, uint8_t moduleQty) {
		_pinData = pinData;
		pinMode(_pinData, OUTPUT);
		digitalWrite(_pinData, LOW);
		_pinClock = pinClock;
		pinMode(_pinClock, OUTPUT);
		digitalWrite(_pinClock, LOW);
		_moduleQty = moduleQty;
		ResetAll();
	}
#endif // ITOOUTPUTMODULE595_MODE_2PORTS
#ifdef ITOOUTPUTMODULE595_MODE_3PORTS
	IToOutputModule595::IToOutputModule595(uint8_t pinData, uint8_t pinClock, uint8_t pinLatch, uint8_t moduleQty) {
		_pinData = pinData;
		pinMode(_pinData, OUTPUT);
		digitalWrite(_pinData, LOW);
		_pinClock = pinClock;
		pinMode(_pinClock, OUTPUT);
		digitalWrite(_pinClock, LOW);
		_pinLatch = pinLatch;
		pinMode(_pinLatch, OUTPUT);
		digitalWrite(_pinLatch, LOW);
		_moduleQty = moduleQty;
		ResetAll();
	}
#endif // ITOOUTPUTMODULE595_MODE_3PORTS

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
	Send();
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
	Send();
	return 1; // true
}

const char* IToOutputModule595::Version() {
	return ITOOUTPUTMODULE595_VERSION;
}

void IToOutputModule595::Info(void) {
#ifdef ITOOUTPUTMODULE595_DEBUG
	Serial.print("Constructor Data:");
	Serial.print(_pinData);
#ifndef ITOOUTPUTMODULE595_MODE_1PORT
	Serial.print(" , Clock:");
	Serial.print(_pinClock);
#endif
	Serial.print(" , moduleQty:");
	Serial.println(_moduleQty);
#endif
}

// Send the data
void IToOutputModule595::Send(void){
	byte mask;
	cli();
#ifdef ITOOUTPUTMODULE595_MODE_1PORT
	for (uint8_t module = 0; module < _moduleQty; ++module) { // for each module
		mask = 0x80; // set first bit 1000 0000
		for (int bit = 0; bit < 8; ++bit) { // for each bit of the module
			if(_data[_moduleQty - module - 1] & mask) { // time in LOW is not enough to discharge capacitor
				digitalWrite(_pinData, LOW);
				delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_BITOFF);
				digitalWrite(_pinData, HIGH); // read the data according level of the capacitor
			} else { // time in LOW is long to discharge the capacitor
				digitalWrite(_pinData, LOW);
				delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_BITON);
				digitalWrite(_pinData, HIGH); // read the data according level of the capacitor
			}
			delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_SHIFT);
			mask >>= 1; // update mask for next bit
		} // end for each bit of the module
	}  // end for each module
	digitalWrite(_pinData, LOW);
	delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_LATCH * 3); // delay big to allow latch
	digitalWrite(_pinData, HIGH);
	delayMicroseconds(ITOOUTPUTMODULE595_DELAY_1F_LATCH); // delay big to asure capacitor discharge

#endif // ITOOUTPUTMODULE595_MODE_1PORT
#ifdef ITOOUTPUTMODULE595_MODE_2PORTS
	for (uint8_t module = 0; module < _moduleQty; ++module) { // for each module
		mask = 0x80; // set first bit 1000 0000
		for (uint8_t bit = 0; bit < 8; ++bit) { // for each bit of the module
			if(_data[_moduleQty - module - 1] & mask) digitalWrite(_pinData, HIGH); // set Data pin
			else digitalWrite(_pinData, LOW);

			delayMicroseconds(ITOOUTPUTMODULE595_DELAY_2F_DATA); // delay between Data and Clock signals

			digitalWrite(_pinClock, HIGH); // set Clock pin rising edge
			if((bit == 7) && (module == (_moduleQty - 1))) delayMicroseconds(ITOOUTPUTMODULE595_DELAY_2F_LATCH); // delay big to allow latch
			else delayMicroseconds(ITOOUTPUTMODULE595_DELAY_2F_CLOCK_HIGH); // delay small to just shift
			digitalWrite(_pinClock, LOW);

			delayMicroseconds(ITOOUTPUTMODULE595_DELAY_2F_CLOCK_LOW); // it is acceptable to have 5Âµs delay after the last bit has been sent
			mask >>= 1; // update mask for next bit
		} // end for each bit of the module
	}  // end for each module
	digitalWrite(_pinData, LOW); // reset to maintain LOW level when not in use
#endif // ITOOUTPUTMODULE595_MODE_2PORTS
#ifdef ITOOUTPUTMODULE595_MODE_3PORTS
	for (uint8_t module = 0; module < _moduleQty; ++module) { // for each module
		mask = 0x80; // set first bit 1000 0000
		for (int bit = 0; bit < 8; ++bit){ // for each bit of the module
			if(_data[_moduleQty - module - 1] & mask) digitalWrite(_pinData, HIGH); // set Data pin
			else digitalWrite(_pinData, LOW);
			digitalWrite(_pinClock, HIGH); // clock pin HIGH ====> do shift and effective changes
			digitalWrite(_pinClock, LOW); // clock pin LOW
			mask >>= 1; // update mask for next bit
		} // end for each bit of the module
	}  // end for each module
	digitalWrite(_pinLatch, HIGH); // make latch to HIGH to latch registers to output
	digitalWrite(_pinLatch, LOW); // latch = LOW
#endif // ITOOUTPUTMODULE595_MODE_3PORTS
	sei();
}
