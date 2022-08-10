
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

BUILD_FILE=$(pwd)/build/zephyr/zephyr.hex
stm32flash -w $BUILD_FILE -v -g 0x0 /dev/ttyUSB0

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Flash Success \n"
    echo -e "${NC}Make sure Boot_0 is set to 1 after flashing the code. \n"
else
    echo -e "${RED}Flash Failed \n"
    echo -e "${NC}Make sure usb port is connected and does not open by other program."
    echo -e "${NC}Set Boot_0 to [1]"
    echo -e "${NC}Set Boot_1 to [0]"
    echo -e "${NC}Reset the MCU before flash. \n"
fi