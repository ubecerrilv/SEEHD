"""
-------------------------------------------------------------------------------------
                    CLASE QUE CONTIENE LOS DATOS DE UN USUARIO
--------------------------------------------------------------------------------------
"""
class Usuario:
    def __init__(self, ID, entrada, salida, horas, cobroHora, cobroTotal):
        self.ID = ID
        self.entrada = entrada
        self.salida = salida
        self.horas = horas
        self.cobroHora = cobroHora
        self.cobroTotal = cobroTotal
        
    def __init__(self):
        self.ID = None
        self.entrada = None
        self.salida = None
        self.horas = None
        self.cobroHora = None
        self.cobroTotal = None
        
    def getID(self):
        return self.ID
        
    def setID(self, ID):
        self.ID = ID
