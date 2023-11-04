#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Imagen1.h"
#include "Imagen2.h"
#include "Imagen3.h"


//Pines para pantalla
  #define TFT_CS         15  //case
  #define TFT_RST        19 //reset
  #define TFT_DC         16 //AO 
  #define TFT_MOSI       17 //Data = SDA 
  #define TFT_SCLK       18 //Clock = SCK 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(9600);
  Serial.print("Holi Test de prueba para ST7735 TFT");

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);

}//FIN SETUP

void loop(void ) {

     char opcion = Serial.read();
     if (opcion == '4'){
        tft.drawRGBBitmap(0,20,Imagen1,128,128);
        Serial.print("Hola1");
     }else if(opcion == '1'){
        tft.drawRGBBitmap(0,20,Imagen2,128,128);
        Serial.print("Hola2");
     }else if(opcion == '2'){
        tft.drawRGBBitmap(0,20,Imagen3,128,128);
        Serial.print("Hola3");
     }
     //FALTA IMAGEN DE PRECIO A PAGAR


 /* tft.fillScreen(ST77XX_RED);
  delay(3000);
  tft.fillScreen(ST77XX_BLUE);
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  delay(3000);
  tft.drawRGBBitmap(0,0,arc,128,128);
  delay(3000);*/
}//FIN LOOP

