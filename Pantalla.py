"""
-------------------------------------------------------------------------------------
   CLASE QUE SE COMUNICA CON EL SERIAL DENTRO DE ARDUINO PARA MOSTRAR LAS IMÁGENES
--------------------------------------------------------------------------------------
"""
import serial

class Pantalla:
    def __init__(self):
     self.puerto = serial.Serial('/dev/ttyUSB0', 9600)
        
    def mostrarMPrincipal(self):
        self.puerto.write(str("1").encode())
        
    def mostrarMCEntrada(self):
        self.puerto.write(str("2").encode())
    
    def mostrarMCSalida(self):
        self.puerto.write(str("3").encode())#PENDIENTE
    
    def mostrarMSalida(self):
        self.puerto.write(str("4").encode())
        
    def leerIDHuella(self):
        self.puerto.read() #PENDIENTE
        pass
