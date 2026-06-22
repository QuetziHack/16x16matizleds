#include <Adafruit_NeoPixel.h>

#define PIN_DATOS     6
#define NUM_LEDS    256   // 16x16 = 256 LEDs

Adafruit_NeoPixel matriz = Adafruit_NeoPixel(NUM_LEDS, PIN_DATOS, NEO_RGB + NEO_KHZ800);

// --- 1. DEFINICIÓN DE FUENTE 8x8 (Letra por letra) ---
// Cada byte es una fila de 8 bits. 1 = LED encendido, 0 = LED apagado.
const uint8_t FONT_H[8] = {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00};
const uint8_t FONT_O[8] = {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00};
const uint8_t FONT_L[8] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x67, 0x7F, 0x00};
const uint8_t FONT_A[8] = {0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00};
const uint8_t FONT_SP[8]= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Espacio

// Función auxiliar para obtener el mapa de bits según el carácter
const uint8_t* obtenerBitmapChar(char c) {
  switch (c) {
    case 'H': return FONT_H;
    case 'O': return FONT_O;
    case 'L': return FONT_L;
    case 'A': return FONT_A;
    default:  return FONT_SP; // Espacio en blanco para caracteres desconocidos
  }
}

// --- 2. TU CLASE PIXEL (INTACTA) ---
class Pixel {
private:
  short x;
  short y;
  short r;
  short g;
  short b;

  int obtenerIndice() {
    if (y % 2 != 0) {
      return (y * 16) + x;       
    } else {
      return (y * 16) + (15 - x); 
    }
  }

public:
  Pixel();
  void setPosition(short, short);
  void setColor(short, short, short);
  void draw();
};

Pixel::Pixel() { y = x = r = b = g = 0; }
void Pixel::setPosition(short x, short y) { this->x = x; this->y = y; }
void Pixel::setColor(short r, short g, short b) { this->r = r; this->g = g; this->b = b; }
void Pixel::draw() { matriz.setPixelColor(obtenerIndice(), this->r, this->g, this->b); }

Pixel pintor;

// --- 3. CONFIGURACIÓN DEL MENSAJE ---
const char* mensaje = "HOLA  "; // El mensaje a mostrar (con espacios al final para el ciclo)
int longitudMensaje = 6;       // Cantidad de caracteres en el mensaje
int anchoTotalPixeles = longitudMensaje * 8; // Cada letra mide 8 píxeles de ancho

void setup() {
  matriz.begin();
  matriz.setBrightness(15);
  matriz.show();
}

void loop() {
  // scrollX comienza en 16 (el texto empieza oculto a la derecha)
  // y disminuye hasta desaparecer por completo a la izquierda (-anchoTotalPixeles)
  for (int scrollX = 16; scrollX > -anchoTotalPixeles; scrollX--) {
    
    matriz.clear(); // Limpiamos la matriz en cada frame de la animación

    // Recorremos las filas de la matriz donde queremos centrar el texto
    // Como la fuente mide 8 de alto, si empezamos en la fila Y=4, ocupará de la 4 a la 11 (centrado en tus 16 filas)
    for (int y = 0; y < 8; y++) {
      int filaMatriz = y + 4; 

      // Recorremos las 16 columnas físicas de la matriz
      for (int x = 0; x < 16; x++) {
        
        // Calculamos qué columna del "Lienzo Virtual" del texto corresponde a esta coordenada X física
        int xVirtual = x - scrollX;

        // Si esa columna virtual cae dentro de los límites de nuestro mensaje largo:
        if (xVirtual >= 0 && xVirtual < anchoTotalPixeles) {
          int letraIndex = xVirtual / 8;     // Qué letra del string estamos evaluando
          int pixelXEnLetra = xVirtual % 8;  // Qué columna (0 a 7) de esa letra específica

          char caracterActual = mensaje[letraIndex];
          const uint8_t* bitmapLetra = obtenerBitmapChar(caracterActual);

          // Leemos el byte de la fila actual 'y' para esa letra
          uint8_t filaByte = bitmapLetra[y];

          // Evaluamos con operaciones de bits si el pixel exacto debe encenderse
          // (De izquierda a derecha: el bit más significativo 7 es el primer pixel de la letra)
          if (filaByte & (1 << (7 - pixelXEnLetra))) {
            pintor.setPosition(x, filaMatriz);
            pintor.setColor(0, 100, 255); // Texto color Celeste/Azul
            pintor.draw();
          }
        }
      }
    }

    matriz.show(); // Mostramos el frame actual
    delay(60);     // Controla la velocidad del carrusel (menor tiempo = más rápido)
  }
}