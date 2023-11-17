"""
-------------------------------------------------------------------------------------
                    CLASE PRINCIPAL QUE INVOCA A LAS DEMÁS
--------------------------------------------------------------------------------------
"""
#IMPORTAR LOS ARCHIVOS NECESARIOS PARA CREAR LOS OBJETOS
import Controlador
import Pantalla
import BaseDeDatos
import LectorDeHuellas
import Pluma

class SEEHD:
    def __init__(self):
        pass
    
    def main(self):#MÉTODO QUE REALIZA LA IMPLEMENTACIÓN DE TODAS LAS DEMÁS CLASES
        #CREACIÓN DE LAS VARIABLES NECESARIAS
        pantalla =  Pantalla.Pantalla()
        lector = LectorDeHuellas.LectorDeHuellas()
        base = BaseDeDatos.BaseDeDatos()
        pluma = Pluma.Pluma()
        controlador = Controlador.Controlador(pantalla, lector, base, pluma)
        
        #INICIAR EL PROGRAMA (POSIBLE WHILE TRUE AQUI)
        controlador.iniciar()