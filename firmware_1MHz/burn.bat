REM uses SPIFFS, ESP-32S
REM 2022-10-09, ESP32_Frequency_generation_2MHz_10MHz.ino firmware
REM burn test ok

:: To erase esp32 completely, do not rely on Arduino IDE and code upload, it has cluster and odd thing when uses FATFS, 
:: unless format SPIFFS or FATFS everytime on the fly
:: xiaolaba, 2020-MAR-02
:: Arduino 1.8.16, esptool and path,

cls
prompt $xiao

set comport=COM3
REM set esptoolpath="C:\Users\user0\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\3.1.0/esptool.exe"
set esptoolpath="%userprofile%\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\3.1.0/esptool.exe"
set project=ESP32_Frequency_generation_2MHz_10MHz

:: erase whole flash of esp32
%esptoolpath% --chip esp32 ^
--port %comport% ^
--baud 921600 ^
erase_flash

REM pause

REM burn firmware
%esptoolpath% --chip esp32 ^
--port %comport% ^
--baud 921600 ^
--before default_reset ^
--after hard_reset ^
write_flash -z ^
--flash_mode dio ^
--flash_freq 40m ^
--flash_size detect ^
0xe000 boot_app0.bin ^
0x1000 %project%.ino.bootloader.bin ^
0x10000 %project%.ino.bin ^
0x8000 %project%.ino.partitions.bin

pause

REM 0xe000 C:\Users\user0\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.1-RC1\tools\partitions/boot_app0.bin 
REM 0x1000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.bootloader.bin 
REM 0x10000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.bin 
REM 0x8000 C:\Users\user0\AppData\Local\Temp\arduino_build_160314/ESP32_Frequency_generation_2MHz_10MHz.ino.partitions.bin 






