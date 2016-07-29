/*
   Nome do Aquivo:   IToOutputModule595-YYYYMMDDa.h
   Descrição:        Library to expand output ports using 74HC595
   Data criada:      2016-06-23
   Versao do Aquivo: 2016-07-23
   Dependências:     N/A
   Escrito por:      Celso Eiju Ito - eijuito@gmail.com

   MCU:              ATMEGA 328P 16 MHz
   Board:            Arduino Uno/Mega/Mini
   Compilador        N/A
   IDE:              Eclipse Mars CDT 8.8.1 com plugin Arduino C++ Jantje Baeyens 3.0.0
   Hardware:         Arduino UNO
   Colaboradores:    Rui Viana - ruianaiv@gmail.com
                     Natalia Ayako Takano - natalia.takano@gmail.com
   Uso:              Generico
   Diagrams:         http://github.com/eijuito/IToOutputModule595
                     http://www.labirito.com/projetos/itooutputmodule74595
   Copyright ®       2016 Celso Eiju Ito eijuito@gmail.com (www.itosa.com.br)
                     Este programa e de propriedade do Celso Eiju Ito eijuito@gmail.com
                     E vedada a copia total ou parcial por pessoas nao autorizadas
                     Nao e permitida a comercializacao ou locacao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   REVISIONS: (latest entry first)
   2016-07-23 Implemented 3 ports mode
   2016-07-13 Implemented 1 port mode but not working correct
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

#define ITOOUTPUTMODULE595_VERSION "IToOutputModule595 v0.2.0"

// =============================================================================
// Options to be included into sketch to selectoperation mode, debug or reduced code
// -----------------------------------------------------------------------------
#define ITOOUTPUTMODULE595_MODE_1PORT
// #define ITOOUTPUTMODULE595_MODE_2PORTS
// #define ITOOUTPUTMODULE595_MODE_3PORTS
#define ITOOUTPUTMODULE595_DEBUG
#define ITOOUTPUTMODULE595_REDUCEDFUNCS

#define ITOOUTPUTMODULE595_MAX_MODULES 10

#define ITOOUTPUTMODULE595_DELAY_2F_DATA           5 // [µs]
#define ITOOUTPUTMODULE595_DELAY_2F_CLOCK_HIGH     5 // [µs]
#define ITOOUTPUTMODULE595_DELAY_2F_CLOCK_LOW     20 // [µs]
#define ITOOUTPUTMODULE595_DELAY_2F_LATCH       1100 // [µs]

#define ITOOUTPUTMODULE595_DELAY_1F_BITON          1 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_BITOFF        20 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_SHIFT         20 // [µs]
#define ITOOUTPUTMODULE595_DELAY_1F_LATCH         50 // [µs]
#define UNDEF  0x2

#ifndef ITOOUTPUTMODULE595_REDUCEDFUNCS
static const char _hexachars[] = "0123456789ABCDEFabcdef";
#endif // ITOOUTPUTMODULE595_REDUCEDFUNCS

class IToOutputModule595 {
	public:
	// Construtor
#ifdef ITOOUTPUTMODULE595_MODE_1PORT
	IToOutputModule595(uint8_t pinData, uint8_t moduleQty = 1);
#endif // ITOOUTPUTMODULE595_MODE_1PORT
#ifdef ITOOUTPUTMODULE595_MODE_2PORTS
	IToOutputModule595(uint8_t pinData, uint8_t pinClock, uint8_t moduleQty = 1);
#endif // ITOOUTPUTMODULE595_MODE_2PORTS
#ifdef ITOOUTPUTMODULE595_MODE_3PORTS
	IToOutputModule595(uint8_t pinData, uint8_t pinClock, uint8_t pinLatch, uint8_t moduleQty = 1);
#endif // ITOOUTPUTMODULE595_MODE_3PORTS

	// Clean all pins of all modules
	virtual uint8_t ResetAll(void);

#ifndef ITOOUTPUTMODULE595_REDUCEDFUNCS
	// Returns the status of all ports of the modules
	virtual uint8_t GetModules(char* hexaValues);

	// Set all ports of the mudules according hexaValues provided
	virtual uint8_t SetModules(char* hexaValues);
#endif // ITOOUTPUTMODULE595_REDUCEDFUNCS

	// Returns the number of modules
	virtual uint8_t NumModules();

	// Returns the status of all ports of the module [0-255]
	virtual uint8_t GetModule(uint8_t module = 0);

	// Set all ports of the module [0-255]
	virtual uint8_t SetModule(uint8_t value, uint8_t module = 0);

	// Returns the status of the port, LOW, HIGH or UNDEF, module = 0 if not provided and calculated if pin > 7
	virtual uint8_t GetOutput(uint8_t pin, uint8_t module = 0);

	// Set status of the port, module = 0 if not provided and calculated if pin > 7
	virtual uint8_t SetOutput(uint8_t pin, uint8_t state, uint8_t module = 0);

	// virtual Info(HardwareSerial *stream, byte format = HEX);
	virtual const char* Version();

	// Display information of config
	void Info(void);

private:
#ifdef ITOOUTPUTMODULE595_MODE_1PORT
    uint8_t _pinData;
#endif // ITOOUTPUTMODULE595_MODE_1PORT
#ifdef ITOOUTPUTMODULE595_MODE_2PORTS
    uint8_t _pinData;
	uint8_t _pinClock;
#endif // ITOOUTPUTMODULE595_MODE_2PORTS
#ifdef ITOOUTPUTMODULE595_MODE_3PORTS
    uint8_t _pinData;
	uint8_t _pinClock;
    uint8_t _pinLatch;
#endif // ITOOUTPUTMODULE595_MODE_3PORTS
	uint8_t _moduleQty;
	uint8_t _data[ITOOUTPUTMODULE595_MAX_MODULES];
	void Send(void);
};

#endif /* ITOOUTPUTMODULE595_H_ */
