import serial
import time

arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)


def write_read(x):
    print("Sending:", x)
    arduino.write(x)
    time.sleep(0.2)
    while not (data := arduino.readline()):
        arduino.write(x)
        time.sleep(0.2)
    return data


def motor_packet(a_power, a_direction, b_power, b_direction):
    return (b'\x00' + a_power.to_bytes(1, 'big')
            + a_direction.to_bytes(1, 'big')
            + b_power.to_bytes(1, 'big')
            + b_direction.to_bytes(1, 'big'))


# while True:
    # command = int(input('1. forward\n2. backward\n3. stop\nEnter command: '))
    # if command < 3:
    #
    #     print(write_read(motor_packet(0, 2 - command, 200, 2 - command)))
    # else:
    #     print(write_read(motor_packet(0, 0, 0, 0)))

max = 130
# for s in range(50, 100):
#     write_read(motor_packet(130, 0, s, 0))
#     print(s)
#     time.sleep(0.5)
print(write_read(motor_packet(130, 1, 100, 1)))
time.sleep(10)
print(write_read(motor_packet(0, 1, 0, 1)))

