#IMPORTAR LAS LIBRERÍAS NECESARIAS
import serial

#DEFINIR VARIABLES NECESARIAS
puerto = serial.Serial('/dev/ttyUSB0', 9600)


#DEFINICIÓN DEL METODO PRICINCIPAL
def iniciar():
    entrada = input("Ingresa una imagen a mostrar: ")
    puerto.write(str(entrada).encode())
    
    
#EJECUCION
while True:
    iniciar()

