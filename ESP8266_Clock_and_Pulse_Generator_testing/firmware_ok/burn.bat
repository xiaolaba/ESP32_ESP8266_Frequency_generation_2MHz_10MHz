REM uses SPIFFS, ESP32-CAM used
REM 2021-09-15, ESP32-CAM_RTSP firmware
REM burn test ok

:: To erase esp8266 completely, do not rely on Arduino IDE and code upload, it has cluster and odd thing when uses FATFS, 
:: unless format SPIFFS or FATFS everytime on the fly
:: xiaolaba, 2020-MAR-02
:: Arduino 1.8.13, esptool and path,

:: download esptool-ck.exe here
::https://github.com/igrr/esptool-ck/releases/tag/0.4.13

::%USERPROFILE%\AppData\Local\Arduino15\packages\esp8266\tools\python3\3.7.2-post1/python3
:: -I %USERPROFILE%\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.0.2/tools/upload.py 


set comport=COM8
set pythonPath=%USERPROFILE%\AppData\Local\Arduino15\packages\esp8266\tools\python3\3.7.2-post1
path = %PATH%;%pythonPath%
set py=upload.py

set project=espI2sClockGen

%USERPROFILE%\AppData\Local\Arduino15\packages\esp8266\tools\python3\3.7.2-post1/python3 ^
 -I %USERPROFILE%\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.0.2/tools/upload.py ^
--chip auto ^
--port %comport% ^
--baud 921600 ^
erase_flash ^
--before default_reset ^
--after hard_reset write_flash ^
0x0 %project%.ino.bin



pause