"""
-------------------------------------------------------------------------------------
              CLASE QUE REALIZA LAS INTERACCIONES CON LA BASE DE DATOS
--------------------------------------------------------------------------------------
"""
import mysql.connector
import Usuario
from datetime import datetime

class BaseDeDatos:
    global conexion
    conexion = mysql.connector.connect(
            host="localhost",
            user="ubecerril",
            password="bEVUM2K8F8,",
            database="estacionamiento")
    global cursor
    cursor = conexion.cursor()
        
    def __init__(self):
        pass
        
    def existeUsr(self, usuario):
        usuario_id = usuario.getID()
        sql = "SELECT COUNT(*) FROM Usuario WHERE ID = %s"
        val = (usuario_id,)
        cursor.execute(sql, val)
        resultado = cursor.fetchone()

        # Si el resultado es 1, significa que el usuario existe; de lo contrario, no existe
        return resultado[0] == 1
        
    def existeHistoria(self, usuario):
        usuario_id = usuario.getID()
        # Consulta para verificar si el usuario con el ID proporcionado está en la tabla Historia y tiene salida nula
        sql = "SELECT COUNT(*) FROM Historia WHERE usuario_id = %s AND salida IS NULL"
        val = (usuario_id,)
        cursor.execute(sql, val)
        resultado = cursor.fetchone()

        # Si el resultado es mayor que 0, significa que el usuario existe en Historia con salida nula; de lo contrario, no existe
        return resultado[0] > 0
    
    def registrarEntrada(self, usuario):
        id_usuario = usuario.getID()
        # Obtener el último registro en la tabla Cobro
        cursor.execute("SELECT id FROM Cobro ORDER BY id DESC LIMIT 1")
        ultimo_cobro_id = cursor.fetchone()[0]  # Obtenemos el ID del último registro en Cobro

        # Obtener la fecha y hora actuales
        fecha_hora_actual = datetime.now()

        # Insertar una nueva historia con los valores deseados
        sql = "INSERT INTO Historia (entrada, usuario_id, cobro_id) VALUES (%s, %s, %s)"
        val = (fecha_hora_actual, id_usuario, ultimo_cobro_id)
        cursor.execute(sql, val)
        conexion.commit()
    
    def registrarUsr(self, usuario):#USUARIO NUEVO PARA ENTRADA (NO PENSION)#VERIFICAR
        usuario_id = usuario.getID()
        tipo = False
        sql = "INSERT INTO Usuario (id, tipo) VALUES(%s, %s)"
        val = (usuario_id, tipo)
        
        cursor.execute(sql, val)
        conexion.commit()
    
    def registrarSalida(self, usuario):#REGISTRAR LA SALIDA DE UN USUARIO RETORNA USUARIO CON LAS HORAS Y EL COBRO
        usuario_id = usuario.getID()
        fecha_hora_actual = datetime.now()

        # Actualizar el registro en la tabla Historia
        sql = "UPDATE Historia SET salida = %s, horas = TIMEDIFF(%s, entrada) WHERE usuario_id = %s AND salida IS NULL"
        val = (fecha_hora_actual, fecha_hora_actual, usuario_id)
        cursor.execute(sql, val)
        conexion.commit()
        
       # Consulta para obtener los datos del usuario y la última tarifa de cobro
        sql = """
        SELECT u.ID, h.entrada, h.salida, h.horas, c.precio AS cobroHora
        FROM Usuario u
        INNER JOIN Historia h ON u.ID = h.usuario_id
        LEFT JOIN Cobro c ON h.cobro_id = c.id
        WHERE u.ID = %s
        ORDER BY h.entrada DESC
        LIMIT 1
        """
        val = (usuario_id,)
        cursor.execute(sql, val)
        resultado = cursor.fetchone()

        if resultado:
            ID, entrada, salida, horas, cobroHora = resultado
            if horas is not None:
                cobroTotal = round(horas * cobroHora, 2)
            else:
                cobroTotal = None
            usr = Usuario(ID, entrada, salida, horas, cobroHora, cobroTotal)
            return usr
        else:
            return None
