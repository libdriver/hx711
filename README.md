[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HX711

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hx711/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

HX711 is a 24 bit A / D converter chip specially designed for high precision electronic scales, which adopts the patented technology of Haixin technology integrated circuit. Compared with other chips of the same type, the chip set is more stable.It has the advantages of high integration, fast response and strong anti-interference. It reduces the electron density. The overall cost of the scale improves the performance and reliability of the whole machine.

LibDriver HX711 is a full function driver of HX711 launched by LibDiver.It provides differential ad reading function.LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver HX711 source files.

/interface includes LibDriver HX711 gpio platform independent template.

/test includes LibDriver HX711driver test code and this code can test the chip necessary function simply.

/example includes LibDriver HX711 sample code.

/doc includes LibDriver HX711 offline document.

/datasheet includes HX711 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface gpio platform independent template and finish your platform gpio driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_hx711_basic.h"

uint8_t res;
uint8_t i;
int32_t raw_voltage;
double voltage_v;

res = hx711_basic_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    res = hx711_basic_read((int32_t *)&raw_voltage, (double *)&voltage_v);
    if (res != 0)
    {
        (void)hx711_basic_deinit();

        return 1;
    }
    hx711_interface_delay_ms(1000);
    hx711_interface_debug_print("hx711: raw voltage is %d.\n", raw_voltage);
    hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v); 

    ...
    
}

...

(void)hx711_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/hx711/index.html](https://www.libdriver.com/docs/hx711/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.