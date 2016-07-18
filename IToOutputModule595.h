/*
   Nome do Aquivo:   IToOutputModule595-YYYYMMDDa.h
   Descri��o:        Library to expand output ports using 74HC595
   Versao do Aquivo: 20160602
   Depend�ncias:     N/A
   MCU:              ATMEGA 328P 16 MHz
   Board:            Arduino Uno/Mega/Mini
   Compilador        N/A
   IDE:              Eclipse Mars CDT 8.8.1 com plugin Arduino C++ Jantje Baeyens 3.0.0
   Hardware:         Arduino UNO
   Escrito por:      Celso Eiju Ito - eijuito@gmail.com
   Colaboradores:    Rui Viana - ruianaiv@gmail.com
   Data:             2016-06-02
   Uso:              IToPeggou
   Diagrams:         N/A
   Copyright �       2016 Celso Eiju Ito eijuito@gmail.com (www.itosa.com.br)
                     Este programa e de propriedade do Celso Eiju Ito eijuito@gmail.com
                     E vedada a copia total ou parcial por pessoas nao autorizadas
                     Nao e permitida a comercializacao ou locacao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   REVISIONS: (latest entry first)
   2016-06-23 Optimized to save memory
   2016-06-18 Second version eliminating Robocore dependency
   2016-06-02 Primeira versao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   NEXT STEPS: (priority first)
   Implement 1 output por required, already in development by Rui Viana
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef ITOOUTPUTMODULE595_H_
#define ITOOUTPUTMODULE595_H_

#include "Arduino.h"

#define ITOOUTPUTMODULE595_MAX_MODULES 10
#define ITOOUTPUTMODULE595_DELAY_DATA           5 // [µs]
#define ITOOUTPUTMODULE595_DELAY_CLOCK_HIGH     5 // [µs]
#define ITOOUTPUTMODULE595_DELAY_CLOCK_LOW     20 // [µs]
#define ITOOUTPUTMODULE595_DELAY_LATCH       1100 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_BITON      25 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_BITOFF    120 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_SHIFT      50 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_LATCH   70000 // [µs]
#define UNDEF  0x2

#define ITOOUTPUTMODULE595_VERSION "IToOutputModule595 v0.1.2"
#define ITOOUTPUTMODULE595_DEBUG
#define ITOOUTPUTMODULE595_REDUCEDFUNCS
static const char _hexachars[] = "0123456789ABCDEFabcdef";

class IToOutputModule595 {
	public:
	// Construtor
	IToOutputModule595(uint8_t moduleQty, uint8_t pinData, uint8_t pinClock = 255);

	// Clean all pins of all modules
	virtual uint8_t ResetAll(void);

#ifndef ITOOUTPUTMODULE595_REDUCEDFUNCS
	// Retorna o estado de todos os pins dos modulos
	virtual uint8_t GetModules(char* hexaValues);

	// Altera todos os pins dos modulos de acordo com hexaValues
	virtual uint8_t SetModules(char* hexaValues);
#endif

	// Retorna a quantidade de modulos
	virtual uint8_t NumModules();

	// Altera todos os pins de um modulo [0-255]
	virtual uint8_t GetModule(uint8_t module = 0);

	// Altera todos os pins de um modulo [0-255]
	virtual uint8_t SetModule(uint8_t value, uint8_t module = 0);

	// Retorna o estado do pin, LOW, HIGH or UNDEF
	virtual uint8_t GetOutput(uint8_t pin, uint8_t module = 0);

	// Set output pin, module = 0 if not provided and calculated if pin > 7
	virtual uint8_t SetOutput(uint8_t pin, uint8_t state, uint8_t module = 0);

	// virtual Info(HardwareSerial *stream, byte format = HEX);
	virtual const char* Version();


private:
	uint8_t _pinClock;
    uint8_t _pinData;
	uint8_t _moduleQty;
	uint8_t _data[ITOOUTPUTMODULE595_MAX_MODULES];
	void PrivateSend(void);
};

#endif /* ITOOUTPUTMODULE595_H_ */
