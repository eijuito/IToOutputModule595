# ITo Output Module 74HC595

Esta biblioteca permite ao Arduino trabalhar com módulos baseados no 74HC595 para extender o número de portas de saída digitais.

Para mais informações, exemplos e circuitos desta biblioteca, por favor, nos visite no
[Project ITo Output Module 74HC595 @ labirito.com](http://www.labirito.com/projetos/itooutputmodule74595 "Labirito projects")

Muito obrigado ao Rui Viana que desenvolveu, testou e refinou esta biblioteca.

## How use this library?

```cpp
#include "IToOutputModule595.h"

IToOutputModule595 outs(output_modules_max, 2, 3);

setup() {
  outs.ResetAll(); // desliga todas as saidas
}

loop() {
  for(int i = 0; i < 8; ++i) { // liga todos os leds sequencialmente
    outs.SetOutput(i, HIGH);
    delay(100);
  }
  for(int i = 0; i < 8; ++i) { // desliga todos os leds sequencialmente
    outs.SetOutput(i, LOW);
    delay(100);
  }
  for(int i = 0; i < 8; ++i) { // 1 led acesso passeia pra direita
    outs.SetModule(1 << i);
    delay(100);
  }
  for(int i = 0; i < 8; ++i) { // 1 led acesso passeia pra esquerda
    outs.SetModule(1 << (7 - i));
    delay(100);
  }
}
```

## Circuit

O circuito abaixo, implementa o modo de expansão com 1 porta do Arduino
[![Circuito de expansão com 74HC595 que usa 1 porta do arduino](http://i.imgur.com/xDvFeTp.png)](http://www.labirito.com/projetos/itooutputmodule74595)

O circuito abaixo, implementa o modo de expansão com 2 portas do Arduino
[![Circuito de expansão com 74HC595 que usa 2 portas do arduino](http://i.imgur.com/yh5pAQ0.png)](http://www.labirito.com/projetos/itooutputmodule74595)

O circuito abaixo, implementa o modo de expansão com 3 portas do Arduino
<< brevevente será postado o esquema de 3 portas aqui >>

## License

**Copyright (c) 2010 Labirito. All right reserved.**

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
