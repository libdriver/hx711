### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: DT/SCK PA8/PA0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. HX711

#### 3.1 Command Instruction

1. Show hx711 chip and driver information.

   ```shell
   hx711 (-i | --information)
   ```

2. Show hx711 help. 

   ```shell
   hx711 (-h | --help)
   ```

3. Show hx711 pin connections of the current board.

   ```shell
   hx711 (-p | --port)
   ```

4. Run hx711 register test.

   ```shell
   hx711 (-t reg | --test=reg)
   ```

5. Run hx711 read times, num means test times. 

   ```shell
   hx711 (-t read | --test=read) [--times=<num>]
   ```

6. Run hx711 read function, num means read times.

   ```shell
   hx711 (-e read | --example=read) [--times=<num>]
   ```


#### 3.2 Command Example

```shell
hx711 -i

hx711: chip is Aviaic HX711.
hx711: manufacturer is Aviaic.
hx711: interface is GPIO.
hx711: driver version is 2.0.
hx711: min supply voltage is 2.6V.
hx711: max supply voltage is 5.5V.
hx711: max current is 1.50mA.
hx711: max temperature is 85.0C.
hx711: min temperature is -40.0C.
```

```shell
hx711 -p

hx711: SCK pin connected to GPIOA PIN0.
hx711: DT pin connected to GPIOA PIN8.
```

```shell
hx711 -t read --times=3

hx711: chip is Aviaic HX711.
hx711: manufacturer is Aviaic.
hx711: interface is GPIO.
hx711: driver version is 2.0.
hx711: min supply voltage is 2.6V.
hx711: max supply voltage is 5.5V.
hx711: max current is 1.50mA.
hx711: max temperature is 85.0C.
hx711: min temperature is -40.0C.
hx711: start read test.
hx711: channel A 128 gain mode test.
hx711: voltage is 2.231444mV.
hx711: voltage is 2.246093mV.
hx711: voltage is 2.280272mV.
hx711: channel B 32 gain mode test.
hx711: voltage is 9.492183mV.
hx711: voltage is 9.257808mV.
hx711: voltage is 9.374995mV.
hx711: channel A 64 gain mode test.
hx711: voltage is 4.648435mV.
hx711: voltage is 4.619138mV.
hx711: voltage is 4.667966mV.
hx711: finish read test.
```

```shell
hx711 -t reg

hx711: chip is Aviaic HX711.
hx711: manufacturer is Aviaic.
hx711: interface is GPIO.
hx711: driver version is 2.0.
hx711: min supply voltage is 2.6V.
hx711: max supply voltage is 5.5V.
hx711: max current is 1.50mA.
hx711: max temperature is 85.0C.
hx711: min temperature is -40.0C.
hx711: start register test.
hx711: hx711_set_mode/hx711_get_mode test.
hx711: set channel a gain 128 mode.
hx711: check mode ok.
hx711: set channel b gain 32 mode.
hx711: check mode ok.
hx711: set channel a gain 64 mode.
hx711: check mode ok.
hx711: finish register test.
```

```shell
hx711 -e read --times=3

hx711: 1/3.
hx711: raw voltage is 1916927.
hx711: voltage is 0.002285V.
hx711: 2/3.
hx711: raw voltage is 1921023.
hx711: voltage is 0.002290V.
hx711: 3/3.
hx711: raw voltage is 1904639.
hx711: voltage is 0.002271V.
```

```shell
hx711 -h

Usage:
  hx711 (-i | --information)
  hx711 (-h | --help)
  hx711 (-p | --port)
  hx711 (-t reg | --test=reg)
  hx711 (-t read | --test=read) [--times=<num>]
  hx711 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>             Run the driver example.
  -h, --help                              Show the help.
  -i, --information                       Show the chip information.
  -p, --port                              Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>    Run the driver test.
      --times=<num>                       Set the running times.([default: 3])
```

