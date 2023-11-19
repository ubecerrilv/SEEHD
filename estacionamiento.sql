-- Crear la tabla Administrador
CREATE TABLE Administrador (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(15) NOT NULL,
    contrasena VARCHAR(10) NOT NULL
);

-- Crear la tabla Cobro
CREATE TABLE Cobro (
    id INT AUTO_INCREMENT PRIMARY KEY,
    precio DECIMAL(10, 2) NOT NULL,
    Fecha DATE NOT NULL
);

-- Crear la tabla Usuario
CREATE TABLE Usuario (
    id INT PRIMARY KEY,
    nombre VARCHAR(50),
    pago BOOLEAN,
    cargo VARCHAR(15)
);

-- Crear la tabla Historia
CREATE TABLE Historia (
    id INT AUTO_INCREMENT PRIMARY KEY,
    entrada DATETIME NOT NULL,
    salida DATETIME,
    horas DECIMAL(10, 2),
    usuario_id INT NOT NULL,
    cobro_id INT NOT NULL,
    FOREIGN KEY (usuario_id) REFERENCES Usuario(id),
    FOREIGN KEY (cobro_id) REFERENCES Cobro(id)
);

INSERT INTO Cobro (precio, Fecha) VALUES (15.00, '2023-11-04');
INSERT INTO Administrador(nombre, contrasena) VALUES('ubecerril', 'uli2002bec');

CREATE USER 'ubecerril'@'localhost' IDENTIFIED BY 'bEVUM2K8F8,';
GRANT ALL PRIVILEGES ON estacionamiento.* TO 'ubecerril'@'localhost';
FLUSH PRIVILEGES;


