#include "Arduino.h"
#include "IToOutputModule595.h"

const uint8_t output_modules_max = 2; // 2 bytes = 4 digitos hexa no outputs
IToOutputModule595 outs(output_modules_max, 2, 3); // (quantidade de módulos, pino de data, pino de clock)

void setup() {
  Serial.begin(9600);
  Serial.println("Test begin ================== Send anything to stop");
  outs.ResetAll(); // desliga todas as saidas
}

void loop() {
  if(Serial.available()) while(true) delay(10000);
  for(int i = 0; i < 8; ++i) {
    outs.SetOutput(i, !outs.GetOutput(i)); // togle outputs filling all pins
    Serial.print("outs=");
    Serial.print(outs.GetModule(0));
    Serial.println(" Send anything to stop");
    delay(100);
  }
  for(int i = 0; i < 8; ++i) {
    outs.SetOutput(i, !outs.GetOutput(i)); // togle outputs clearing all pins
    Serial.print("outs=");
    Serial.print(outs.GetModule(0));
    Serial.println(" Send anything to stop");
    delay(100);
  }
  for(int i = 0; i < 8; ++i) {
    outs.SetModule((1 << i), 0); // set all 8 pins from module 0
    Serial.print("outs=");
    Serial.print(outs.GetModule(0));
    Serial.println(" Send anything to stop");
    delay(100);
  }
}
