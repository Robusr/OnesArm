# -*- coding:utf-8 -*-

import time
from pico import l76x
import math

# define the UART number and its baudrate , when UARTx is 1 please solder the UART1 0R resistor on Pico-GPS-L76B board
# UARTx = 1
UARTx = 0
# define the rp2040 uart baudrate , the default baudrate is 9600 of L76B 
BAUDRATE = 9600

# make an object of gnss device , the default uart is UART0 and its baudrate is 9600bps
gnss_l76b=l76x.L76x(uartx=UARTx,_baudrate = BAUDRATE)

# set L76B baudrate
'''
optional:
SET_NMEA_BAUDRATE_115200
SET_NMEA_BAUDRATE_57600
SET_NMEA_BAUDRATE_38400
SET_NMEA_BAUDRATE_19200
SET_NMEA_BAUDRATE_14400
SET_NMEA_BAUDRATE_9600
SET_NMEA_BAUDRATE_4800
'''
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_NMEA_BAUDRATE_9600)
time.sleep(2)

# set rp2040 UARTx baudrate , it should be same as L76B baudrate , otherwise GPS NMEA sentence parser doesnt work
gnss_l76b.L76x_Set_Baudrate(_baudrate=BAUDRATE, uartx=UARTx)

# set NMEA0183 sentence output frequence
'''
optional:
SET_POS_FIX_100MS
SET_POS_FIX_200MS
SET_POS_FIX_400MS
SET_POS_FIX_800MS
SET_POS_FIX_1S
SET_POS_FIX_2S
SET_POS_FIX_4S
SET_POS_FIX_8S
SET_POS_FIX_10S
'''
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_POS_FIX_1S)

# exit the backup mode when start
gnss_l76b.L76x_Exit_BackupMode()

# enable/disable sync PPS when NMEA output
'''
optional:
SET_SYNC_PPS_NMEA_ON
SET_SYNC_PPS_NMEA_OFF
'''
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_SYNC_PPS_NMEA_ON)

# L76B will enter STANDBY mode, the NMEA0183 sentence stop output
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_STANDBY_MODE)
time.sleep(10)

# wake up L76B 
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_NORMAL_MODE)
gnss_l76b.StandBy.value(1)

# enable NMEA0183 sentence output
gnss_l76b.L76x_Send_Command(gnss_l76b.SET_NMEA_OUTPUT) 
