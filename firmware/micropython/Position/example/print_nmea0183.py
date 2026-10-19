# -*- coding:utf-8 -*-

from pico import l76x

# define the UART number and its baudrate , when UARTx is 1 please solder the UART1 0R resistor on Pico-GPS-L76B
UARTx = 0
# define the rp2040 uart baudrate , the default baudrate is 9600 of L76B 
BAUDRATE = 9600

# make an object of gnss device , the default uart is UART0 and its baudrate is 9600bps
gnss_l76b=l76x.L76x(uartx=UARTx,_baudrate = BAUDRATE)



# loop
while True:
    # if gnss available,then print the nmea0183 sentence
    if gnss_l76b.uart_any():
        print(chr(gnss_l76b.uart_receive_byte()[0]),end="")

