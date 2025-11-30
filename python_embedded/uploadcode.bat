esptool --port COM3 erase_flash
esptool --port COM3 --baud 460800 write_flash 0x1000 upy_20250911-v1.26.1.bin
ampy --port COM3 put main.py src\main.py
