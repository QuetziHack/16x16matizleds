#include <Adafruit_NeoPixel.h>

#define PIN_DATOS    6   // Pin del Arduino conectado a DIN de la matriz
#define NUM_LEDS   256   // 16 x 16 = 256 LEDs

// Configuración de la matriz
Adafruit_NeoPixel matriz = Adafruit_NeoPixel(NUM_LEDS, PIN_DATOS, NEO_GRB + NEO_KHZ800);

void setup() {
  matriz.begin();
  matriz.setBrightness(10); // Brillo bajo (0 a 255) para proteger tu fuente y tus ojos en las pruebas
  matriz.show();            // Inicializa todos los LEDs en apagado
}

void loop() {
  // Efecto sencillo: Enciende un LED tras otro en color azul
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<16;j++){
      matriz.setPixelColor((j%2?i:15-i)+j*16, matriz.Color(255,255,0)); // Color Amarillo(R, G, B)
    }
    matriz.show();
    delay(50); // Velocidad del encendido
    for(int j = 0; j<16;j++){
      matriz.setPixelColor((j%2?i:15-i)+j*16, matriz.Color(0, 0, 0));
    }
  }
  for (int i=0;i<16;i++){
    for (int a =0 ;a<16;a++){
      matriz.setPixelColor(i*16+a, matriz.Color(0,0,255)); // Color Amarillo(R, G, B)
    }
    matriz.show();
    delay(50);
    for (int a =0 ;a<16;a++){
      matriz.setPixelColor(i*16+a, matriz.Color(0,0,0)); // Color Amarillo(R, G, B)
    }
  }
  for(int i = 15; i >-1; i--) {
    for(int j = 0; j<16;j++){
      matriz.setPixelColor((j%2?i:16-i-1)+j*16, matriz.Color(255,0,255)); // Color Amarillo(R, G, B)
    }
    matriz.show();
    delay(50); // Velocidad del encendido
    for(int j = 0; j<16;j++){
      matriz.setPixelColor((j%2?i:16-i-1)+j*16, matriz.Color(0, 0, 0));
    }
  }
  for (int i=15;i>-1;i--){
    for (int a =0 ;a<16;a++){
      matriz.setPixelColor(i*16+a, matriz.Color(0,255,255)); // Color Amarillo(R, G, B)
    }
    matriz.show();
    delay(50);
    for (int a =0 ;a<16;a++){
      matriz.setPixelColor(i*16+a, matriz.Color(0,0,0)); // Color Amarillo(R, G, B)
    }
  }
  delay(100);
}