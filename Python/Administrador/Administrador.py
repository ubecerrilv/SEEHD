import tkinter as tk
from tkinter import ttk
import mysql.connector
from datetime import datetime, timedelta
import serial
from tkinter import messagebox

db = mysql.connector.connect(
        host="localhost",
        user="ubecerril",
        password="bEVUM2K8F8,",
        database="estacionamiento")

cursor = db.cursor()
puerto = serial.Serial('/dev/ttyUSB0', 9600)
global id
id = 0

def login():
    username = username_entry.get()
    password = password_entry.get()

    query = "SELECT id FROM Administrador WHERE nombre = %s AND contrasena = %s"
    cursor.execute(query, (username, password))
    result = cursor.fetchone()

    if result:
        print("Inicio de sesión exitoso")
        show_main_window()
    else:
        print("Credenciales incorrectas")

def show_main_window():
    root.destroy()

    main_window = tk.Tk()
    main_window.title("Ventana del Administrador")
    
    #PEDIR EL ID DESDE EL SENSOR
    def obtenerID():
        obID = tk.Tk()
        obID.title("Obtener ID")
        
        for etq in id_frame.winfo_children():
            etq.destroy()
        
        frame_x = tk.Frame(obID, bd=2, relief=tk.GROOVE)
        
        inst = tk.Label(frame_x, text="Pida al usuario introducir su huella en el lector")
        inst.pack(expand=True, fill=tk.BOTH)
        
        while True:
            if puerto.in_waiting>0:
                id = int(puerto.readline().decode().strip())
                break
        
        etqID = tk.Label(frame_x, text="ID de usuario: "+str(id))
        etqID = tk.Label(id_frame, text="ID de usuario: "+str(id))
        obID.destroy()
        
    # Consultar datos de la tabla Historia
    def show_history():
        fecha_actual = datetime.now()
        opcion_tiempo = combo.get()
        for si in tabla_frame.winfo_children():
            si.destroy()
        
        
        # Definir las fechas según la opción seleccionada
        if opcion_tiempo == "Mes actual":
            fecha_inicio = fecha_actual.replace(day=1)
            fecha_fin = fecha_actual.replace(day=1, month=fecha_actual.month + 1) - timedelta(days=1)
        elif opcion_tiempo == "Mes pasado":
            fecha_inicio = fecha_actual.replace(day=1, month=fecha_actual.month - 1)
            fecha_fin = fecha_actual.replace(day=1) - timedelta(days=1)
        elif opcion_tiempo == "Semana actual":
            fecha_inicio = fecha_actual - timedelta(days=fecha_actual.weekday())
            fecha_fin = fecha_inicio + timedelta(days=6)
        elif opcion_tiempo == "Semana pasada":
            fecha_inicio = fecha_actual - timedelta(days=fecha_actual.weekday() + 7)
            fecha_fin = fecha_inicio + timedelta(days=6)
        elif opcion_tiempo == "Hoy":
            fecha_inicio = fecha_actual.replace(hour=0, minute=0, second=0, microsecond=0)
            fecha_fin = fecha_actual.replace(hour=23, minute=59, second=59, microsecond=999999)

        # Consulta SQL dinámica basada en las fechas
        query = "SELECT h.entrada, h.salida, h.horas, u.nombre FROM Historia h, Usuario u WHERE h.usuario_id = u.id AND entrada BETWEEN %s AND %s"
        cursor.execute(query, (fecha_inicio, fecha_fin))
        result = cursor.fetchall()
        
        label = tk.Label(tabla_frame, text="\tEntrada\t|\tSalida\t|Horas|\t  Usuario\t\t", borderwidth=1, relief="solid")
        label.pack(padx=200)
        suma_multiplicaciones = 0
        for row in result:
            formatted_row = '|'.join(str(attr) for attr in row)
            
            label = tk.Label(tabla_frame, text=formatted_row, borderwidth=1, relief="solid")
            label.pack(padx=200)
            print(formatted_row)
            
            #Obtener horas
            horas = float(row[2])
            if horas > 0.25:
                multiplicacion = horas * 20
                suma_multiplicaciones += multiplicacion
            
        label = tk.Label(tabla_frame, text="Total ganado: $"+str(suma_multiplicaciones))
        label.pack(side=tk.RIGHT)

    # Insertar registros en la tabla Usuario
    def insert_user():
        nombre = user_name_entry.get()
        pago = True
        cargo = user_role_entry.get()

        if id != 0:
            query = "INSERT INTO Usuario (id, nombre, pago, cargo) VALUES (%s, %s, %s, %s) " \
                "ON DUPLICATE KEY UPDATE nombre=VALUES(nombre), pago=VALUES(pago), cargo=VALUES(cargo)"

            datos_usuario = (id, nombre, pago, cargo)
            cursor.execute(query, datos_usuario)
            db.commit()
            id=0
            messagebox.showinfo("Información", "Pensionado resgistrado")
        
        else:
            messagebox.showinfo("Error", "Asegurarse de que el ID y el resto de datos han sido incluidos")
        
    # Sección izquierda para mostrar datos de Historia
    history_frame = tk.Frame(main_window, bd=2, relief=tk.GROOVE)
    history_frame.pack(side=tk.LEFT, padx=10, pady=10, expand=True, fill=tk.BOTH)

    history_label = tk.Label(history_frame, text="Datos de Historia")
    history_label.pack()
    #COMBO DE OPCIONES
    opciones = ["Mes actual","Mes pasado","Semana actual","Semana pasada","Hoy"]
    selecionado = tk.StringVar()
    
    combo = ttk.Combobox(history_frame, textvariable=selecionado, values=opciones)
    combo.pack()

    show_history_button = tk.Button(history_frame, text="Mostrar Historia", command=show_history)
    show_history_button.pack(pady=10)
    
    tabla_frame = tk.Frame(history_frame, bd=2, relief=tk.GROOVE)
    tabla_frame.pack(expand=True, fill=tk.BOTH)

    # Sección derecha para insertar registros en Usuario
    user_frame = tk.Frame(main_window, bd=2, relief=tk.GROOVE)
    user_frame.pack(side=tk.RIGHT, padx=10, pady=10, expand=True, fill=tk.BOTH)

    user_label = tk.Label(user_frame, text="Registrar pensionado")
    user_label.pack()

    user_id_label = tk.Button(user_frame,text="Obtener ID", command=obtenerID)
    user_id_label.pack()
    id_frame = tk.Frame(user_frame)
    id_frame.pack()

    user_name_label = tk.Label(user_frame, text="Nombre:")
    user_name_label.pack()
    user_name_entry = tk.Entry(user_frame)
    user_name_entry.pack()

    user_payment_label = tk.Label(user_frame, text="Pago (Activo/Inactivo):")
    user_payment_label.pack()
    
    user_payment_entry = tk.Entry(user_frame)
    user_payment_entry.insert(0,"Activo")
    user_payment_entry.pack()

    user_role_label = tk.Label(user_frame, text="Cargo:")
    user_role_label.pack()
    user_role_entry = tk.Entry(user_frame)
    user_role_entry.pack()

    insert_user_button = tk.Button(user_frame, text="Insertar Usuario", command=insert_user)
    insert_user_button.pack(pady=10)

    main_window.mainloop()

# Ventana de inicio de sesión
root = tk.Tk()
root.title("Inicio de Sesión")

username_label = tk.Label(root, text="Usuario:")
username_label.pack()
username_entry = tk.Entry(root)
username_entry.pack()

password_label = tk.Label(root, text="Contraseña:")
password_label.pack()
password_entry = tk.Entry(root, show="*")
password_entry.pack()

login_button = tk.Button(root, text="Iniciar Sesión", command=login)
login_button.pack()

root.mainloop()
