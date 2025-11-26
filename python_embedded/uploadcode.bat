esptool --port COMalgo erase_flash
esptool.py --port COMalgo --baud 460800 write_flash 0x1000 upy_20250911-v1.26.1.bin
ampy --port COMalgo put main.py
