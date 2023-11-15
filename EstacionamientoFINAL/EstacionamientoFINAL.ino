#include <Adafruit_Fingerprint.h>

//LIBRERIAS PANTALLA
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "1.h"
#include "2.h"
#include "3.h"

// Use the default hardware UART on ESP32 (Serial2)
#define mySerial Serial2

//PINES DE LA PANTALLA
  #define TFT_CS         15  //case
  #define TFT_RST        19 //reset
  #define TFT_DC         1 //AO 
  #define TFT_MOSI       3 //Data = SDA 
  #define TFT_SCLK       18 //Clock = SCK 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id = 1;

void mensaje(String mensaje){
  Serial.println("entra");
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0,60);
  tft.print(mensaje);
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
}

void setup() {
  //PANTALLA
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.drawRGBBitmap(0,0,Imagen1,128,128);

  Serial.begin(9600);
  while (!Serial);  // Wait for the serial port to open
  delay(100);
  Serial.println("Adafruit Fingerprint sensor enrollment");

  // Set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");//ERROR
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  id = finger.templateCount;
  //finger.emptyDatabase();

}


void loop() {
  while (!getFingerprintEnroll());
}//FIN LOOP

uint8_t getFingerprintEnroll() {
 // tft.drawRGBBitmap(0,0,Imagen1,128,128);

  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK){
    Serial.println("Error");
    //tft.drawRGBBitmap(0,0,Imagen2,128,128);
    return p;
  }

  // If fingerprint already saved, it doesn't stores it again
  int foundId = checkFingerprint();
  if (foundId == FINGERPRINT_OK){
    return true;
  }

  //Serial.println("Quita la huella");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  
  p = -1;
  Serial.println(""+-1);
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK){
    Serial.println("Error en la conversion 2");
    return p;
  }

  // OK converted!
  p = finger.createModel();
  if (p != FINGERPRINT_OK) {
    Serial.println("Huellas no coinciden");
    return p;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println(id);
    id ++;
  } else{
    Serial.println("Error guardando");
    return p;
  }
  delay(2000);
  return true;
}

uint8_t checkFingerprint(){
  uint8_t p = finger.fingerSearch();
  if (p != FINGERPRINT_OK) {
    //Serial.println("Error verificando");
    return p;
  }
  // found a match!
  //Serial.print("Found "); 
  int si = finger.fingerID;
  Serial.print(si);
  delay(2000);
  return p;
}