#include <Adafruit_NeoPixel.h>

#define PIN_DATOS     6
#define NUM_LEDS    256   // 16x16 = 256 LEDs

Adafruit_NeoPixel matriz = Adafruit_NeoPixel(NUM_LEDS, PIN_DATOS, NEO_RGB + NEO_KHZ800);

// Representación binaria de la imagen (1 = Hoja, 0 = Vacío)
const uint16_t HOJA_BITMAP[16] = {
  0b0000000010000000, // Fila 0
  0b0000000010000000, // Fila 1
  0b0000000110000000, // Fila 2
  0b0100000111000010, // Fila 3
  0b0100000111000010, // Fila 4
  0b0110001111000110, // Fila 5
  0b0011001111001100, // Fila 6
  0b0011101111011100, // Fila 7
  0b0001111111111000, // Fila 8
  0b1100111111110011, // Fila 9
  0b0111111111111110, // Fila 10
  0b0011111111111100, // Fila 11
  0b0000111111110000, // Fila 12
  0b0011110110111100, // Fila 13
  0b0000000110000000, // Fila 14
  0b0000000110000000  // Fila 15
};

class Pixel {
private:
  short x;
  short y;
  short r;
  short g;
  short b;

  int obtenerIndice() {
    if (y % 2 != 0) {
      return (y * 16) + x;       // Filas impares
    } else {
      return (y * 16) + (15 - x); // Filas pares (Zigzag)
    }
  }

public:
  Pixel();
  void setPosition(short, short);
  void setColor(short, short, short);
  void draw();
  void off();
};

Pixel::Pixel() {
  y = x = r = b = g = 0;
}

void Pixel::setPosition(short x, short y) {
  this->x = x;
  this->y = y;
}

void Pixel::setColor(short r, short g, short b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

void Pixel::draw() {
  matriz.setPixelColor(obtenerIndice(), this->r, this->g, this->b);
}

void Pixel::off() {
  matriz.setPixelColor(obtenerIndice(), 0, 0, 0);
}

// Instancia global de nuestro objeto pixel de control
Pixel pintor;

void setup() {
  matriz.begin();
  matriz.setBrightness(15); // Brillo moderado para distinguir bien los colores
  matriz.show();
}

void loop() {
  // Definición de los colores del diseño
  short hojaR = 30,   hojaG = 0, hojaB = 0;  // Color de la hoja (Verde)
  short fondoR = 10, fondoG = 10,  fondoB = 20;  // Color de fondo tenue (puedes dejarlo 0,0,0 si lo quieres apagado)

  // Recorremos las coordenadas cartesianas completas (X, Y)
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 16; x++) {
      
      pintor.setPosition(x, y);
      
      // Con una operación de bits (Bitwise shift) evaluamos si el bit en la posición X es 1 o 0
      if (HOJA_BITMAP[y] & (1 << (15 - x))) {
        pintor.setColor(hojaR, hojaG, hojaB);
      } else {
        pintor.setColor(fondoR, fondoG, fondoB);
      }
      
      pintor.draw();
    }
  }

  matriz.show(); // Desplegamos todo el cuadro en la matriz física
  delay(5000);   // Mantiene la imagen fija por 5 segundos
}