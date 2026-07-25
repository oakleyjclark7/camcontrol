# For sending messages to the pico over usb for testing

import serial
import serial.tools.list_ports

ports = list(serial.tools.list_ports.comports())

for p in ports:
    print(p.device, p.description)

port = input("Enter Pico port: ")

ser = serial.Serial(
    port=port,
    baudrate=115200,
    timeout=0.1
)

print("Connected to Pico. Type messages and press Enter")

while True:
    msg = input("> ")
    ser.write((msg + "\n").encode())