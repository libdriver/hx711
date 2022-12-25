### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: SCK/DT GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(hx711 REQUIRED)
```

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
./hx711 -i

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
./hx711 -p

hx711: SCK pin connected to GPIO27(BCM).
hx711: DT pin connected to GPIOA17(BCM).
```

```shell
./hx711 -t read --times=3

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
hx711: voltage is 2.304686mV.
hx711: voltage is 2.343749mV.
hx711: voltage is 2.294921mV.
hx711: channel B 32 gain mode test.
hx711: voltage is 9.355464mV.
hx711: voltage is 9.453120mV.
hx711: voltage is 9.199214mV.
hx711: channel A 64 gain mode test.
hx711: voltage is 4.746091mV.
hx711: voltage is 4.609373mV.
hx711: voltage is 4.814451mV.
hx711: finish read test
```

```shell
./hx711 -t reg

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
./hx711 -e read --times=3

hx711: 1/3.
hx711: raw voltage is 120333.
hx711: voltage is 0.000143V.
hx711: 2/3.
hx711: raw voltage is 120354.
hx711: voltage is 0.000143V.
hx711: 3/3.
hx711: raw voltage is 120334.
hx711: voltage is 0.000143V.
```

```shell
./hx711 -h

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

