"""
-------------------------------------------------------------------------------------
                    CLASE QUE CONTIENE LOS DATOS DE UN USUARIO
--------------------------------------------------------------------------------------
"""
class Usuario:
    def __init__(self, ID=None, entrada=None, salida=None, horas=None, cobroHora=None, cobroTotal=None):
        self.ID = ID
        self.nombre = None
        self.pago = None
        self.cargo = None
        self.entrada = entrada
        self.salida = salida
        self.horas = horas
        self.cobroHora = cobroHora
        self.cobroTotal = cobroTotal
        
    @classmethod   
    def sinPar(cls):
        return cls()
    
    @classmethod
    def noPen(cls, ID, entrada, salida, horas, cobroHora, cobroTotal):
        return cls(id, entrada, salida, horas, cobroHora, cobroTotal)
        
    def getID(self):
        return self.ID
        
    def setID(self, ID):
        self.ID = ID
        
    def getCobroTotal(self):
        return self.cobroTotal
