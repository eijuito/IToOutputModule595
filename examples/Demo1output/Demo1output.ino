#include "Arduino.h"
#include "IToOutputModule595.h"
/*
// Para configurar o modo 1 porta, certifique-se que o IToOutputModule595.h
   esteja habilitando somente o ITOOUTPUTMODULE595_MODE_1PORT conforme abaixo:

#define ITOOUTPUTMODULE595_MODE_1PORT
// #define ITOOUTPUTMODULE595_MODE_2PORTS
// #define ITOOUTPUTMODULE595_MODE_3PORTS

*/
const uint8_t qtd_modules = 2; // 2 modules or 2 74HC595
IToOutputModule595 outs(2, qtd_modules); // (pino de data, quantidade de módulos)

void setup() {
  Serial.begin(9600);
  Serial.println("Inicio ================== Envie algo para parar");
  outs.ResetAll(); // desliga todas as saidas
}

void loop() {
  if(Serial.available()) while(true) delay(10000);
  for(int i = 0; i < 8; ++i) {
    outs.SetOutput(i, !outs.GetOutput(i)); // altera as saidas ligando todos os pinos
    Serial.print("saida = ");
    Serial.print(outs.GetModule(0));
    Serial.println(" - Envie algo para parar");
    delay(100);
  }
  for(int i = 0; i < 8; ++i) {
    outs.SetOutput(i, !outs.GetOutput(i)); // altera as saidas desligando todos os pinos
    Serial.print("saida = ");
    Serial.print(outs.GetModule(0));
    Serial.println(" - Envie algo para parar");
    delay(100);
  }
  for(int i = 0; i < 8; ++i) {
    outs.SetModule((1 << i), 0); // liga todos os pinos do modulo 0
    Serial.print("saida = ");
    Serial.print(outs.GetModule(0));
    Serial.println(" - Envie algo para parar");
    delay(100);
  }
}
