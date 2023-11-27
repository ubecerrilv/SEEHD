//LIBRERIAS SENSOR
#include <Adafruit_Fingerprint.h>

//LIBRERIAS PANTALLA
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "1.h"
#include "2.h"
#include "3.h"

//LIBRERIAS SERVOS
#include <ESP32Servo.h>

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

//SERVOS
Servo entrada;
Servo salida;

//VARIABLE QUE CONTROLA EL NUMERO DE HUELLAS
int id;

void setup() {
  Serial.begin(9600);
  //INICIANDO SERVOS
  entrada.attach(2);
  salida.attach(4);
  entrada.write(0);
  salida.write(90);

  //PANTALLA
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setTextColor(ST77XX_BLACK);
  tft.drawRGBBitmap(0,0,Imagen1,128,128);

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
  //finger.emptyDatabase();
  finger.getTemplateCount();
  id = finger.templateCount;

}

void loop() {
  int idAct = obtenerID();
  if(idAct == -1){//NO ESTA REGISTRADA

    mensaje("Usuario nuevo");
    delay(500);
    mensaje("Seras registrado");
    delay(500);
    idAct = registrarID();

    if(idAct != -2){//REGISTRO EXITOSO
      mensaje("Registrado!");
      delay(700);
      mensaje("Bienvenido a la FI!");
      delay(1500);
      tft.drawRGBBitmap(0,0,Imagen1,128,128);
      Serial.println(idAct);

      //MOVER SERVO PARA ENTRAR
      entrar();

      id++;
      delay(1000);

      //Serial.println("Intenta de nuevo");
    }//FIN IF

  }else if (idAct != -2){//REGISTRADA
    //Serial.print("Ya registrada: ");
    Serial.println(idAct);
    delay(1000);

    //LEER COBRO DEL SERIAL MONITOR
    if (Serial.available() > 0) {

      String datoRecibido = Serial.readString();
      float cobro = datoRecibido.toFloat();

      //AGREGAR ELSE PENSIONADO -1
      //TIEMPO DE ESTANCIA
      //MOVER SERVO SALIR
      //BOTON DE CONFIRMACION DE PAGO
      if(cobro == 0.00){//MENOS DE 15 MIN
        mensaje("Tiempo de cortesia");
        tft.drawRGBBitmap(0,0,Imagen3,128,128);
        salir();
        tft.drawRGBBitmap(0,0,Imagen1,128,128);
      }else{
        mensaje("$"+datoRecibido);
        delay(3000);
        tft.drawRGBBitmap(0,0,Imagen3,128,128);
        salir();
        tft.drawRGBBitmap(0,0,Imagen1,128,128);
      }//FIN ELSE MOSTRAR COBRO
    }else{//FIN IF LEER COBRO

      mensaje("Bienvenido a la FI!");
      delay(3000);
      //MOVER SERVO PARA ENTRAR
      entrar();
      tft.drawRGBBitmap(0,0,Imagen1,128,128);
    }//FIN ELSE MOVER SERVO ENTRAR SI NO HAY NADA QUE LEER
  }//FIN ELSE YA REGISTRADA
}//FIN LOOP

//FUNCION PARA OBTENER ID DE UNA HUELLA YA GUARDADA
int obtenerID(void){
  //OBTENEMOS LA HUELLA A BUSCAR
  int p = -1;
  while(p != FINGERPRINT_OK){
    p = finger.getImage();
    if(p == FINGERPRINT_OK){
      //Serial.println("\nHuella capturada para busqueda");
    }else if(p == FINGERPRINT_NOFINGER){
      //Serial.print(".");
      parpadeo();
    }else{
      error();
      return -2;
    }//FIN IF
  }//FIN WHILE


  //CONVERTIMOS LA HUELLA A BUSCAR
  p = finger.image2Tz();
  if(p == FINGERPRINT_OK){
    //Serial.println("Huella a buscar convertida");
  }else{
    //Serial.println("Error al convertir la huella a buscar");
    error();
    return -2;
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
    error();
    return -2;
  }//FIN IF
}//FIN OBTENER

//FUNCION PARA REGISTRAR UNA NUEVA HUELLA
int registrarID(void){
  //OBTENER PRIMERA HUELLA
  int p = -1;
  mensaje("Coloca tu dedo para registrarlo");
  //Serial.print("Esperando la huella: "); Serial.println(id);
  while (p != FINGERPRINT_OK) {//MIENTRAS TENGA UN DEDO EN EL SENSOR
    p = finger.getImage();

    if(p == FINGERPRINT_OK){
      //Serial.println("\nPrimera huella capturada");
      mensaje("Primera huella capturada");
    }else if(p == FINGERPRINT_NOFINGER){
      //Serial.print(".");
      parpadeo();
    }else{
      //Serial.println("Error al capturar primera huella");
      error();
      return -2;
    }//FIN IF
  }//FIN WHILE

  //CONVERTIR Y GUARDAR LA PRIMERA HUELLA
  p = finger.image2Tz(1);
  if(p == FINGERPRINT_OK){
    //Serial.println("Primera huella convertida");
  }else{
    //Serial.println("Error al convertir primera huella");
    error();
    return -2;
  }//FIN IF
  
  //OBTENER LA SEGUNDA HUELLA
  //Serial.println("Quita el dedo");
  mensaje("Retira el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {//MIENTRAS TENGA UN DEDO EN EL SENSOR
    p = finger.getImage();
  }//FIN WHILE

  p = -1;
  //Serial.println("Coloca el mismo dedo de nuevo");
  mensaje("Coloca el mismo dedo de nuevo");
  while(p != FINGERPRINT_OK){
    p = finger.getImage();
    if(p == FINGERPRINT_OK){
      //Serial.println("\nSegunda huella capturada");
    }else if (p == FINGERPRINT_NOFINGER){
      //Serial.print(".");
      parpadeo();
    }else{
      //Serial.println("Error al capturar la segunda huella");
      error();
      return -2;
    }//FIN IF
  }//FIN WHILE

  //CONVERTIR Y GUARDAR LA SEGUNDA HUELLA
  p = finger.image2Tz(2);
  if(p == FINGERPRINT_OK){
    //Serial.println("Segunda huella convertida");
  }else{
    //Serial.println("Error al convertir la segunda huella");
    error();
    return -2;
  }//FIN IF

  //CREAR EL MODELO PARA LAS HUELLAS
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    //Serial.println("Huellas coinciden");
    mensaje("Huellas coinciden");
  }else{
    //Serial.println("Error al crear el modelo");
    error();
    return -2;
  }//FIN IF

  //GUARDAR EL MODELO CON EL ID
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    //Serial.println("Huella guardada exitosamente");
    return id;
  }else{
    //Serial.println("Error al guardar el modelo");
    error();
    return -2;
  }//FIN IF
}//FIN REGISTRAR

//FUNCION PARA ESCRIBIR MENSAJE EN LA PANTALLA
void mensaje(String mensaje){
  tft.fillScreen(ST77XX_WHITE);

  tft.setTextSize(1);

  tft.setCursor(0,60);
  tft.print(mensaje);
  delay(500);
}

//FUNCION PARA MANDAR UN PARPADEO EN LA PANTALLA
void parpadeo(void){
  tft.fillRect(110, 30, 10, 10, ST77XX_GREEN);
  delay(500);
  tft.fillRect(110, 30, 10, 10, ST77XX_WHITE);
  delay(500);
}//FIN PARPADEO

//FUNCION PARA MANDAR ERROR
void error(){
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.setCursor(15,60);
  tft.print("ERROR");
  delay(1000);
  tft.setCursor(0,75);
  tft.print("Intenta de nuevo");
  delay(1000);
  tft.drawRGBBitmap(0,0,Imagen1,128,128);
  tft.setTextColor(ST77XX_BLACK);
}//FIN ERROR

//FUNCION PARA MOVER EL SERVO AL ENTRAR 
void entrar(void){
  entrada.write(90);
  delay(3000);
  entrada.write(0);
}//FIN ENTRAR

//FUNCION PARA MOVER EL SERVO AL SALIR
void salir(void){
  salida.write(0);
  delay(3000);
  salida.write(90);
}//FIN SALIR