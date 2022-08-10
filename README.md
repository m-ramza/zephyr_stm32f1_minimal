## Overview

Minimal Setup For STM32F1 Series.

Current Supported Board:
* stm32f103c8
***************************************

## Setting up west workspace for the first time
```
west init -l --mf west.yml
west update
```

## Building and Running

* must be in zephyr directory to follow below commands

**Build**
```
rm -rf build
./build.sh
```

**Flash**

* must have stm32flash.
```
./flash.sh
```
********************
**Test**

* must have minicom.
* Open serial port to see the logging and shell uart.
* Baudrate: 115200 bps
* Port: /dev/ttyUSB0
* Port can be check with 'ls dev'

```
minicom -b 115200 -D /dev/ttyUSB0 --color=on
```

********************
## Vs code integration
### Extenstion
* cortex-debug
* DeviceTree for the Zephyr
* Kconfig for the Zephyr project