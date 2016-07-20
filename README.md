# ITo Output Module 74HC595

This library allows Arduino work with modules based on 74HC595 to extend outputs.

For more information about this library please visit us at
[Project itooutputmodule74595 @ labirito.com](http://www.labirito.com/projetos/itooutputmodule74595 "Labirito projects")

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

The circuit below implements the 2 ports output expansion.
[![2 ports 74HC595 circuit](http://i.imgur.com/yh5pAQ0.png)](http://www.labirito.com/projetos/itooutputmodule74595)

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
