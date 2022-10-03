### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

gpio pin: SCK/DT GPIO27/GPIO17.

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

​          hx711 is a basic command which can test all hx711 driver function:

​           -h        show hx711 help. 

​           -i         show hx711 chip and driver information.

​           -p        show hx711 pin connections of the current board.

​           -t (reg | read <times>)

​           -t reg        run hx711 register test.

​           -t read <times>        run hx711 read times. times means test times. 

​           -c read <times>        run hx711 read function. times means read times.

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
./hx711 -t read 3

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
hx711: voltage is 0.135182 mV.
hx711: voltage is 0.135254 mV.
hx711: voltage is 0.135167 mV.
hx711: channel B 32 gain mode test.
hx711: voltage is 0.030808 mV.
hx711: voltage is -0.012517 mV.
hx711: voltage is 0.008421 mV.
hx711: channel A 64 gain mode test.
hx711: voltage is 0.137765 mV.
hx711: voltage is 0.137773 mV.
hx711: voltage is 0.137732 mV.
hx711: finish read test.
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
./hx711 -c read 3

hx711: 1/3.
hx711: raw voltage is 113396.
hx711: voltage is 0.000135mV.
hx711: 2/3.
hx711: raw voltage is 113382.
hx711: voltage is 0.000135mV.
hx711: 3/3.
hx711: raw voltage is 113389.
hx711: voltage is 0.000135mV.
```

```shell
./hx711 -h

hx711 -h
	show hx711 help.
hx711 -i
	show hx711 chip and driver information.
hx711 -p
	show hx711 pin connections of the current board.
hx711 -t reg
	run hx711 register test.
hx711 -t read <times>
	run hx711 read times.times means test times.
hx711 -c read <times>
	run hx711 read function.times means read times.
```

