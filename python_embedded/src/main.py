from machine import Pin
import time
print("Hello, ESP32!")

led = Pin(2, Pin.OUT)
while True:
  led.on()
  time.sleep(0.5)
  led.off()
  time.sleep(0.5)
