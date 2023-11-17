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
#define TFT_CS         15  //case
#define TFT_RST        19 //reset
#define TFT_DC         33 //AO 
#define TFT_MOSI       32 //Data = SDA 
#define TFT_SCLK       18 //Clock = SCK 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//VARIABLE QUE CONTROLA EL NUMERO DE HUELLAS
int id;

//PENDIENTE
void mensaje(String mensaje){
  tft.fillScreen(ST77XX_WHITE);

  tft.setTextSize(1);

  tft.setCursor(0,60);
  tft.print(mensaje);
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
}

void setup() {
  Serial.begin(9600);

  //PANTALLA
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setTextColor(ST77XX_BLACK);
  tft.drawRGBBitmap(0,0,Imagen1,128,128);

  //SENSOR INICIADO A 57600 BAUDIOS
  Serial.println("paso 1");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("No se logró encontrar el sensor");
    while (true) { 
      delay(1);
    }
  }
  Serial.println("paso 2");
  //RECUPERAR EL NUMERO DE HUELLAS GUARDADO
  finger.emptyDatabase();
  finger.getTemplateCount();
  id = finger.templateCount;

}

void loop() {
  int idAct = obtenerID();
  if(idAct == -1){//NO ESTA REGISTRADA

    mensaje("Usuario nuevo");
    delay(1000);
    idAct = registrarID();
    if(idAct == -1){//REGISTRO FALLIDO
      mensaje("Intenta de nuevo ):");
      tft.drawRGBBitmap(0,0,Imagen1,128,128);

      //Serial.println("Intenta de nuevo");
    }else{//REGISTRO EXITOSO
      //Serial.print("Recien registrada: ");
      mensaje("Registrado!");
      Serial.println(idAct);
      id++;
      delay(1000);
    }

  }else{//REGISTRADA
    //Serial.print("Ya registrada: ");
    Serial.println(idAct);
    delay(1000);
  }
}

//FUNCION PARA OBTENER ID DE UNA HUELLA YA GUARDADA
int obtenerID(void){
  //OBTENEMOS LA HUELLA A BUSCAR
  int p = -1;
  while(p != FINGERPRINT_OK){
    p = finger.getImage();
    if(p == FINGERPRINT_OK){
      //Serial.println("\nHuella capturada para busqueda");
    }else if(p == FINGERPRINT_NOFINGER){
      Serial.print(".");
      tft.writeFillRect(0, 0, 5, 5, ST77XX_BLACK);
      delay(500);
      tft.writeFillRect(0, 0, 5, 5, ST77XX_WHITE);
      delay(500);
    }else{
      //Serial.println("Error al leer la huella para busqueda");
      return -1;
    }//FIN IF
  }//FIN WHILE


  //CONVERTIMOS LA HUELLA A BUSCAR
  p = finger.image2Tz();
  if(p == FINGERPRINT_OK){
    //Serial.println("Huella a buscar convertida");
  }else{
    //Serial.println("Error al convertir la huella a buscar");
    return -1;
  }//FIN IF

  //BUSCAR LA HUELLA
  p = finger.fingerSearch();
  if(p == FINGERPRINT_OK){
    //Serial.println("Huella encontrada");
    return finger.fingerID;
  }else if(p == FINGERPRINT_NOTFOUND){
    //Serial.println("Huella no encontrada. Registrando");
    return -1;
  }else{
    //Serial.println("Error al buscar la huella");
    return -1;
  }//FIN IF
}//FIN OBTENER

//FUNCION PARA REGISTRAR UNA NUEVA HUELLA
int registrarID(void){
  //OBTENER PRIMERA HUELLA
  int p = -1;
  Serial.print("Esperando la huella: "); Serial.println(id);
  while (p != FINGERPRINT_OK) {//MIENTRAS TENGA UN DEDO EN EL SENSOR
    p = finger.getImage();

    if(p == FINGERPRINT_OK){
      //Serial.println("\nPrimera huella capturada");
    }else if(p == FINGERPRINT_NOFINGER){
      Serial.print(".");
      delay(500);
    }else{
      Serial.println("Error al capturar primera huella");
      return -1;
    }//FIN IF
  }//FIN WHILE

  //CONVERTIR Y GUARDAR LA PRIMERA HUELLA
  p = finger.image2Tz(1);
  if(p == FINGERPRINT_OK){
    //Serial.println("Primera huella convertida");
  }else{
    Serial.println("Error al convertir primera huella");
    return -1;
  }//FIN IF
  
  //OBTENER LA SEGUNDA HUELLA
  Serial.println("Quita el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {//MIENTRAS TENGA UN DEDO EN EL SENSOR
    p = finger.getImage();
  }//FIN WHILE

  p = -1;
  Serial.println("Coloca el mismo dedo de nuevo");
  while(p != FINGERPRINT_OK){
    p = finger.getImage();
    if(p == FINGERPRINT_OK){
      //Serial.println("\nSegunda huella capturada");
    }else if (p == FINGERPRINT_NOFINGER){
      Serial.print(".");
      delay(500);
    }else{
      Serial.println("Error al capturar la segunda huella");
      return -1;
    }//FIN IF
  }//FIN WHILE

  //CONVERTIR Y GUARDAR LA SEGUNDA HUELLA
  p = finger.image2Tz(2);
  if(p == FINGERPRINT_OK){
    //Serial.println("Segunda huella convertida");
  }else{
    Serial.println("Error al convertir la segunda huella");
    return -1;
  }//FIN IF

  //CREAR EL MODELO PARA LAS HUELLAS
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    //Serial.println("Huellas coinciden");
  }else{
    Serial.println("Error al crear el modelo");
    return -1;
  }//FIN IF

  //GUARDAR EL MODELO CON EL ID
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    //Serial.println("Huella guardada exitosamente");
    return id;
  }else{
    Serial.println("Error al guardar el modelo");
    return -1;
  }//FIN IF
}//FIN REGISTRAR