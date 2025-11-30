unsigned char estadoLed = 0;

void setup() {
  DDRB = B00000000;   
  PORTB = B00000100;  
  DDRD = B00000100;  
}

void loop() {

  if (PINB == B00000100) {   // Botón presionado
    delay(20);               // Antirebote

    if (PINB == B00000100) { // Confirmación

      // Toggle:
      estadoLed = !estadoLed;

      if (estadoLed)
        PORTD = B00000100;   // LED ON
      else
        PORTD = B00000000;   // LED OFF

      while (PINB == B00000100);
    }
  }
}
