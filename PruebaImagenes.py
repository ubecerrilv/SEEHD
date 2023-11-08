import serial

puerto = serial.Serial('/dev/ttyUSB0', 9600)

while True:
	si = int(input("Coloca el numero de la imagen a mostrar: "))
	if si == 1:
		puerto.write(str("1").encode())
	elif si == 2:
		puerto.write(str("2").encode())
	elif si == 3: 
		puerto.write(str("4").encode())	
