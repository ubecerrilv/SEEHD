"""-------------------------------------------------------------------------------------
CLASE QUE SE COMUINICA CON EL SERIAL DENTRO DE ARDUINO PARA MOSTRAR LAS IMAGENES
--------------------------------------------------------------------------------------"""
class Pantalla:
    #ATRIBUTOS
    
    #METODOS
    def mostrarMPrincipal():
        puerto.write(str("1").enconde())
        
    def mostrarMCEntrada():
        puerto.write(str("2").enconde())
    
    def mostrarMCSalida():
        puerto.write(str("3").enconde())#PENDIENTE
    
    def mostrarMSalida():
        puerto.write(str("4").enconde())

"""-------------------------------------------------------------------------------------
CLASE QUE SE COMUNICA CON EL LECTOR DE HUELLAS DIGITALES PARA EL ACCESO EN LA BASE DE DATOS
--------------------------------------------------------------------------------------"""
class LectorDeHuellas:
    #ATRIBUTOS
    
    #METODOS
    def leerHuella():
        pass 
"""-------------------------------------------------------------------------------------
CLASE QUE REALIZA LAS INTERACCIONES CON LA BASE DE DATOS
--------------------------------------------------------------------------------------"""
class BaseDeDatos:
    #ATRIBUTOS
    
    #METODOS
    def validar ():#VALIDA SI UN USUARIO YA ESTÁ REGISTRADO EN LA BASE DE DATOS
        pass
    
    def registrarUsr():#USUARIO NUEVO
        pass
    
    def registrarSalida():#REGISTRAR LA SALIDA DE UN USUARIO
        pass
    
    def consultarUsr():#RETORNAR FALSO O VERDADERO
        pass
    
"""-------------------------------------------------------------------------------------
CLASE QUE REALIZA LOS MOVIMIENTOS DE SALIDA***
--------------------------------------------------------------------------------------"""
class Pluma:
    #ATRIBUTOS
    
    #METODOS
    def mover():#MOVER PARA SALIR O ENTRAR
        pass
    
"""-------------------------------------------------------------------------------------
CLASE QUE CONTIENE LOS DATOS DE UN USUARIO
--------------------------------------------------------------------------------------"""
class Usuario:
    #ATRIBUTOS
    pass
    #METODOS
    
"""EJECUCIÓN DE LOS METODOS"""
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
