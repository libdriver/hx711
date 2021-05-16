<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver HX711

[English](/README.md) | [ 简体中文](/README_CN.md)

HX711 is a 24 bit A / D converter chip specially designed for high precision electronic scales, which adopts the patented technology of Haixin technology integrated circuit. Compared with other chips of the same type, the chip set is more stable.It has the advantages of high integration, fast response and strong anti-interference. It reduces the electron density. The overall cost of the scale improves the performance and reliability of the whole machine.

LibDriver HX711 is a full function driver of HX711 launched by LibDiver.It provides differential ad reading function.

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

/interface includes LibDriver HX711 gpio platform independent template。

/test includes LibDriver HX711driver test code and this code can test the chip necessary function simply。

/example includes LibDriver HX711 sample code.

/doc includes LibDriver HX711 offline document.

/datasheet includes HX711 datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface gpio platform independent template and finish your platform gpio driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t i;
int32_t raw_voltage;
double voltage_v;

res = hx711_basic_init();
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    res = hx711_basic_read((int32_t *)&raw_voltage, (double *)&voltage_v);
    if (res)
    {
        hx711_basic_deinit();

        return 1;
    }
    delay_ms(1000);
    hx711_interface_debug_print("hx711: raw voltage is %d.\n", raw_voltage);
    hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v); 

    ...
    
}

...

hx711_basic_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/hx711/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (C) LibDriver 2015-2021 All rights reserved 



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

Please sent an e-mail to lishifenging@outlook.com