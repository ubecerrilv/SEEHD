//LIBRERIAS SENSOR
#include <Adafruit_Fingerprint.h>

//LIBRERIAS PANTALLA
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
//#include "1.h"
//#include "2.h"
//#include "3.h"

// USO DEL SERIAL 2 PARA EL SENSOR
#define puerto Serial2
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&puerto);

//PINES DE LA PANTALLA
#define TFT_CS         15  //case
#define TFT_RST        19 //reset
#define TFT_DC         1 //AO 
#define TFT_MOSI       3 //Data = SDA 
#define TFT_SCLK       18 //Clock = SCK 
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
  //tft.drawRGBBitmap(0,0,Imagen1,128,128);

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
  getFingerprintID();
  delay(500);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    return p;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    return p;
  }

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.print("ID de huella encontrado: #");
    Serial.println(finger.fingerID);
    return finger.fingerID;
  } else {
    Serial.println("Huella no registrada, registrando nueva huella...");

    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
      Serial.println("Huella registrada exitosamente.");

      // Almacena el ID de la huella en la base de datos
      uint16_t newFingerprintID = finger.fingerID;
      Serial.print("Nuevo ID de huella registrado: #");
      Serial.println(newFingerprintID);
      return newFingerprintID;
    } else {
      Serial.println("Error al registrar la huella. Por favor, inténtalo de nuevo.");
      return p;
    }
  }
}