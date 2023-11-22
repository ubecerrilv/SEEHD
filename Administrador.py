import tkinter as tk
import mysql.connector

def login():
    username = username_entry.get()
    password = password_entry.get()

    db = mysql.connector.connect(
        host="localhost",
        user="ubecerril",
        password="bEVUM2K8F8,",
        database="estacionamiento")
    cursor = db.cursor()

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

    # Consultar datos de la tabla Historia
    def show_history():
        # Aquí se puede realizar la consulta a la base de datos y mostrar los datos en esta sección
        pass

    # Insertar registros en la tabla Usuario
    def insert_user():
        # Aquí se puede insertar un nuevo registro en la tabla Usuario
        pass

    # Sección izquierda para mostrar datos de Historia
    history_frame = tk.Frame(main_window, bd=2, relief=tk.GROOVE)
    history_frame.pack(side=tk.LEFT, padx=10, pady=10, expand=True, fill=tk.BOTH)

    history_label = tk.Label(history_frame, text="Datos de Historia")
    history_label.pack()

    show_history_button = tk.Button(history_frame, text="Mostrar Historia", command=show_history)
    show_history_button.pack(pady=10)

    # Sección derecha para insertar registros en Usuario
    user_frame = tk.Frame(main_window, bd=2, relief=tk.GROOVE)
    user_frame.pack(side=tk.RIGHT, padx=10, pady=10, expand=True, fill=tk.BOTH)

    user_label = tk.Label(user_frame, text="Insertar Registro en Usuario")
    user_label.pack()

    user_id_label = tk.Label(user_frame, text="ID:")
    user_id_label.pack()
    user_id_entry = tk.Entry(user_frame)
    user_id_entry.pack()

    user_name_label = tk.Label(user_frame, text="Nombre:")
    user_name_label.pack()
    user_name_entry = tk.Entry(user_frame)
    user_name_entry.pack()

    user_payment_label = tk.Label(user_frame, text="Pago (True/False):")
    user_payment_label.pack()
    user_payment_entry = tk.Entry(user_frame)
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
