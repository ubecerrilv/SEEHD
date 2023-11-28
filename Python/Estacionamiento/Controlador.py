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
        print("Registrando entrada del usuario #"+str(usuario.ID)+"\n")
        
    def registrarSalida(self, usuario):
        usrCompleto = self.baseDeDatos.registrarSalida(usuario)
        print("Registrando salida del usuario #"+str(usuario.ID)+"\nTiempo: "+str(usrCompleto.horas)+" horas\nCobro: $"+str(usrCompleto.cobroTotal)+"\n")
        self.pantalla.mostrarPago(usrCompleto.cobroTotal)
        
    
    def iniciar(self): 
        while True:
            #CREAR USUARIO PARA LAS LECTURAS Y ESCRITURAS
            usuario = Usuario.Usuario.sinPar()
            #LEER DATOS DE ENTRADA SI ES QUE LOS HAY
            usuario_id = self.pantalla.leerIDHuella()
            #SETEAR EL ID DEL USUARIO
            usuario.setID(usuario_id)
            
            #VERIFICAR SI EL USUARIO EXISTE            
            existeUsr = self.baseDeDatos.existeUsr(usuario)
            
            if existeUsr:
                #VERIFICAR SI EL USUARIO TIENE HISTORIA Y NO HA SALIDO(HA ENTRADO)
                existeHistoria = self.baseDeDatos.existeHistoria(usuario)
                if existeHistoria:
                    self.registrarSalida(usuario)
                else:
                    self.registrarEntrada(usuario)
            else:
                self.baseDeDatos.registrarUsr(usuario)
                print("Registrando al usuario #"+str(usuario.ID)+"\n")
                self.registrarEntrada(usuario)
