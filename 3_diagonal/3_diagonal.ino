#include <Adafruit_NeoPixel.h>

#define PIN_DATOS     6
#define NUM_LEDS    256
#define speed        60

Adafruit_NeoPixel matriz = Adafruit_NeoPixel(NUM_LEDS,PIN_DATOS,NEO_RGB+NEO_KHZ800);

class Pixel{
private:
  short x;
  short y;
  short r;
  short g;
  short b;
public:
  Pixel();
  Pixel(short,short,short,short,short);
  void setPosition(short,short);
  void setColor(short,short,short);
  void draw();
  void off();

};

Pixel::Pixel(){
  y = x = r = b = g = 0;
}

Pixel::Pixel(short x, short y, short r, short g, short b){
  this->x=x;
  this->y=y;
  this->r=r;
  this->g=g;
  this->b=b;
}


void Pixel::setPosition(short x, short y){
  if (y % 2) {
    this->x = x;
  } else {
    this->x = 15-x;
  }
  this->y = y;
}
void Pixel::setColor(short r, short g, short b){
  this->r = r;
  this->g = g;
  this->b = b;
}
void Pixel::draw(){
  matriz.setPixelColor(this->x+16*this->y,this->r,this->g,this->b);
}

void Pixel::off(){
  matriz.setPixelColor(this->x+16*this->y,0,0,0);
}

Pixel P1;

void setup() {
  matriz.begin();
  matriz.setBrightness(10);
  matriz.show();
}

void loop() {
  for (int i = 0;i<16;i++){
    P1.setPosition(i,i);
    P1.setColor(100,0,200);
    P1.draw();
    matriz.show();
    delay(speed);
    P1.off();
  }
  for (int i = 0;i<16;i++){
    P1.setPosition(15,15-i);
    P1.setColor(100,0,200);
    P1.draw();
    matriz.show();
    delay(80);
    P1.off();
  }
  for (int i = 0;i<16;i++){
    P1.setPosition(15-i,0);
    P1.setColor(100,0,200);
    P1.draw();
    matriz.show();
    delay(80);
    P1.off();
  }

}
