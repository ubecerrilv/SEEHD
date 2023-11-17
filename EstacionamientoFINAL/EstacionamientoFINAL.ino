//LIBRERIAS SENSOR
#include <Adafruit_Fingerprint.h>

//LIBRERIAS PANTALLA
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "1.h"
#include "2.h"
#include "3.h"

// USO DEL SERIAL 2 PARA EL SENSOR
#define puerto Serial2
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&puerto);

//PINES DE LA PANTALLA
/*#define TFT_CS         15  //case
#define TFT_RST        19 //reset
#define TFT_DC         1 //AO 
#define TFT_MOSI       3 //Data = SDA 
#define TFT_SCLK       18 //Clock = SCK */



Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//VARIABLE QUE CONTROLA EL NUMERO DE HUELLAS
uint8_t id = 1;

//PENDIENTE
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

  //SENSOR INICIADO A 57600 BAUDIOS
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("No se logró encontrar el sensor");
    while (true) { 
      delay(1);
    }
  }

  //RECUPERAR EL NUMERO DE HUELLAS GUARDADO
  finger.getTemplateCount();
  id = finger.templateCount;
  finger.emptyDatabase();

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