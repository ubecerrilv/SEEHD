"""
-------------------------------------------------------------------------------------
                        CLASE QUE CONTROLA LAS DEMÁS CLASES
--------------------------------------------------------------------------------------
"""
import Usuario
class Controlador:
    def __init__(self):
        pass
        
    def __init__(self, pantalla, lector, baseDeDatos, pluma):
        self.pantalla = pantalla
        self.lector = lector
        self.baseDeDatos = baseDeDatos
        self.pluma = pluma
        
    def registrarEntrada(self, usuario):
        self.baseDeDatos.registrarEntrada(usuario)
        ##FALTA MENU EMERGENTE DE REGISTRO EXITOSO
        self.pantalla.mostrarMPrincipal()
        
    def registrarSalida(self, usuario):
        pago = self.pantalla.leerPago()
        
        if pago:
            self.baseDeDatos.registarSalida(usuario)
            self.pantalla.mostrarMCSalida()
            self.pantalla.mostrarMPrincipal()
        else:
            self.pantalla.mostrarMPrincipal()
    
    def iniciar(self): 
        #MOSTRAR MENU PRINCIPAL
        self.pantalla.mostrarMPrincipal()
        while True:
            #CREAR USUARIO PARA LAS LECTURAS Y ESCRITURAS
            usuario = Usuario.Usuario()
            #LEER DATOS DE ENTRADA SI ES QUE LOS HA
            usuario.setID(self.pantalla.leerIDHuella())
            #VERIFICAR SI EL USUARIO EXISTE            
            existeUsr = self.baseDeDatos.existeUsr(usuario)
            
            if existeUsr:
                #VERIFICAR SI EL USUARIO TIENE HISTORIA (HA ENTRADO)
                existeHistoria = self.baseDeDatos.existeHistoria(usuario)
                if existeHistoria:
                    self.registrarSalida(usuario)
                else:
                    self.registrarEntrada(usuario)
            else:
                self.baseDeDatos.registrarUsr(usuario)
                self.registrarEntrada(usuario)
