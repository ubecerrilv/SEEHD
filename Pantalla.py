"""
-------------------------------------------------------------------------------------
    CLASE QUE SE COMUNICA CON EL SERIAL DENTRO DE ARDUINO PARA MOSTRAR LAS IMÁGENES
--------------------------------------------------------------------------------------
"""
import serial

class Pantalla:
    def __init__(self):
        self.puerto = serial.Serial('/dev/ttyUSB0', 9600)
        
    def leerIDHuella(self):
        id = self.puerto.readline().decode().strip()
        
        try:
            id = int(id)
        except ValueError:
            print("Error al leer id entrante")
        
        return id
    
    def mostrarPago(self, pago):
        self.puerto.write(str(pago).encode())
