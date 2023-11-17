#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "1.h"
#include "2.h"
#include "3.h"


//Pines para pantalla
  /*#define TFT_CS         15  //case
  #define TFT_RST        19 //reset
  #define TFT_DC         16 //AO 
  #define TFT_MOSI       17 //Data = SDA 
  #define TFT_SCLK       18 //Clock = SCK */

#define TFT_CS         15  //case
#define TFT_RST        19 //reset
#define TFT_DC         33 //AO 
#define TFT_MOSI       32 //Data = SDA 
#define TFT_SCLK       18 //Clock = SCK 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  Serial.begin(9600);
  Serial.print("Holi Test de prueba para ST7735 TFT");

}//FIN SETUP

void loop(void ) {

     String opcion = Serial.readString();
     Serial.println(opcion);
     if (opcion == "1"){
        Serial.print("1");
        tft.drawRGBBitmap(0,0,Imagen1,128,128);
     }else if(opcion == "2"){
        Serial.print("2");
        tft.drawRGBBitmap(0,0,Imagen2,128,128);
     }else if(opcion == "3"){
        Serial.print("3");
        tft.drawRGBBitmap(0,0,Imagen3,128,128);
     }else if (opcion != ""){
        tft.fillScreen(ST77XX_WHITE);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(1);
        tft.setCursor(15,15);
        tft.print("Total a pagar: ");

        tft.setCursor(0, 60);

          /*Serial.print(opcion.compareTo("0.00"));

        if (opcion.compareTo("0.00")==10){
          tft.setTextSize(2);
          tft.println("Pension activa");
          tft.println("Puede salir");
        }else{
          tft.setCursor(10, 60);
          tft.setTextSize(3);
          tft.print("$"+opcion);
        }*/

        delay(5000);
        tft.fillScreen(ST77XX_BLACK);
        tft.drawRGBBitmap(0,0,Imagen3,128,128);
        delay(5000);
        tft.drawRGBBitmap(0,0,Imagen1,128,128);
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

