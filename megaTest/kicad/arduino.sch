EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:shield_arduino
LIBS:74HC165
LIBS:arduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PWR_FLAG #FLG01
U 1 1 59F99CC3
P 10550 6225
F 0 "#FLG01" H 10550 6300 50  0001 C CNN
F 1 "PWR_FLAG" H 10550 6375 50  0000 C CNN
F 2 "" H 10550 6225 50  0001 C CNN
F 3 "" H 10550 6225 50  0001 C CNN
	1    10550 6225
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 59F99CDD
P 10200 6225
F 0 "#FLG02" H 10200 6300 50  0001 C CNN
F 1 "PWR_FLAG" H 10200 6375 50  0000 C CNN
F 2 "" H 10200 6225 50  0001 C CNN
F 3 "" H 10200 6225 50  0001 C CNN
	1    10200 6225
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR03
U 1 1 59F99E14
P 2075 6225
F 0 "#PWR03" H 2075 5975 50  0001 C CNN
F 1 "GND" H 2075 6075 50  0000 C CNN
F 2 "" H 2075 6225 50  0001 C CNN
F 3 "" H 2075 6225 50  0001 C CNN
	1    2075 6225
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR04
U 1 1 59F99E54
P 2075 7425
F 0 "#PWR04" H 2075 7275 50  0001 C CNN
F 1 "+5V" H 2075 7565 50  0000 C CNN
F 2 "" H 2075 7425 50  0001 C CNN
F 3 "" H 2075 7425 50  0001 C CNN
	1    2075 7425
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 59F9A078
P 2700 6775
F 0 "R1" V 2700 6925 50  0000 C CNN
F 1 "4.7k" V 2700 6775 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2630 6775 50  0001 C CNN
F 3 "" H 2700 6775 50  0001 C CNN
	1    2700 6775
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 59F9A0E7
P 2850 6775
F 0 "#PWR05" H 2850 6625 50  0001 C CNN
F 1 "+5V" H 2850 6915 50  0000 C CNN
F 2 "" H 2850 6775 50  0001 C CNN
F 3 "" H 2850 6775 50  0001 C CNN
	1    2850 6775
	0    1    1    0   
$EndComp
$Comp
L MAX485E U1
U 1 1 59F99D1E
P 2075 6825
F 0 "U1" H 1835 7275 50  0000 C CNN
F 1 "MAX485E" H 2105 7275 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 2075 6125 50  0001 C CNN
F 3 "" H 2075 6875 50  0001 C CNN
	1    2075 6825
	-1   0    0    1   
$EndComp
$Comp
L ARDUINO_MEGA SH1
U 1 1 59FF4C38
P 9150 3150
F 0 "SH1" H 9150 3675 60  0000 C CNN
F 1 "ARDUINO_MEGA" H 9150 3875 60  0000 C CNN
F 2 "" H 8200 3450 60  0000 C CNN
F 3 "" H 8200 3450 60  0000 C CNN
	1    9150 3150
	1    0    0    -1  
$EndComp
Text Label 10325 2750 0    60   ~ 0
MAX485_RX
Text Label 10325 2850 0    60   ~ 0
MAX485_TX
Text Label 2475 6625 0    60   ~ 0
MAX485_RX
Text Label 2475 6925 0    60   ~ 0
MAX485_TX
Text Label 10325 4100 0    60   ~ 0
MAX485_CTRL
Text Label 2550 6725 0    60   Italic 0
MAX485_CTRL
$Comp
L Conn_01x10_Female J1
U 1 1 59FF5BAF
P 1125 6425
F 0 "J1" H 1125 6925 50  0000 C CNN
F 1 "Conn_01x10_Female" V 1175 6425 50  0000 C CNN
F 2 "" H 1125 6425 50  0001 C CNN
F 3 "" H 1125 6425 50  0001 C CNN
	1    1125 6425
	0    -1   -1   0   
$EndComp
Wire Wire Line
	725  6625 1675 6625
Connection ~ 1525 6625
Connection ~ 1425 6625
Connection ~ 1325 6625
Connection ~ 1225 6625
Connection ~ 1125 6625
Connection ~ 1025 6625
Connection ~ 925  6625
Connection ~ 825  6625
$Comp
L Conn_01x10_Female J2
U 1 1 59FF631A
P 1225 7125
F 0 "J2" H 1225 7625 50  0000 C CNN
F 1 "Conn_01x10_Female" V 1275 7125 50  0000 C CNN
F 2 "" H 1225 7125 50  0001 C CNN
F 3 "" H 1225 7125 50  0001 C CNN
	1    1225 7125
	0    1    1    0   
$EndComp
Wire Wire Line
	725  6925 1675 6925
Connection ~ 825  6925
Connection ~ 925  6925
Connection ~ 1025 6925
Connection ~ 1125 6925
Connection ~ 1225 6925
Connection ~ 1325 6925
Connection ~ 1425 6925
Connection ~ 1525 6925
Connection ~ 1625 6925
Connection ~ 1625 6625
NoConn ~ 8000 1050
NoConn ~ 8000 1150
NoConn ~ 8000 1250
NoConn ~ 8000 1550
NoConn ~ 8000 1850
NoConn ~ 8000 1950
NoConn ~ 8000 2050
NoConn ~ 8000 2150
NoConn ~ 8000 2250
NoConn ~ 8000 2350
NoConn ~ 8000 2450
NoConn ~ 8000 2550
NoConn ~ 8000 2750
NoConn ~ 8000 2850
NoConn ~ 8000 2950
NoConn ~ 8000 3050
NoConn ~ 8000 3150
NoConn ~ 8000 3250
NoConn ~ 8000 3350
NoConn ~ 8000 3450
NoConn ~ 8000 3650
NoConn ~ 8000 3750
NoConn ~ 8000 3925
NoConn ~ 8000 4125
NoConn ~ 8000 4425
NoConn ~ 8000 4525
NoConn ~ 8000 4625
NoConn ~ 8000 4725
NoConn ~ 8000 4825
NoConn ~ 8000 4925
NoConn ~ 8000 5025
NoConn ~ 8000 5125
NoConn ~ 8000 5325
NoConn ~ 8000 5425
NoConn ~ 8000 5525
NoConn ~ 8000 5625
NoConn ~ 10325 750 
NoConn ~ 10325 850 
NoConn ~ 10325 950 
NoConn ~ 10325 1050
NoConn ~ 10325 1150
NoConn ~ 10325 1250
NoConn ~ 10325 1350
NoConn ~ 10325 1450
NoConn ~ 10325 1550
NoConn ~ 10325 1850
NoConn ~ 10325 1950
NoConn ~ 10325 2050
NoConn ~ 10325 2150
NoConn ~ 10325 2250
NoConn ~ 10325 2350
NoConn ~ 10325 2450
NoConn ~ 10325 2550
NoConn ~ 10325 2950
NoConn ~ 10325 3050
NoConn ~ 10325 3150
NoConn ~ 10325 3250
NoConn ~ 10325 3350
NoConn ~ 10325 3450
NoConn ~ 10325 3650
NoConn ~ 10325 3750
NoConn ~ 10325 3900
NoConn ~ 10325 4000
NoConn ~ 10325 4200
NoConn ~ 10325 4300
NoConn ~ 10325 4400
NoConn ~ 10325 4500
NoConn ~ 10325 4600
NoConn ~ 10325 4800
NoConn ~ 10325 4900
NoConn ~ 10325 5000
NoConn ~ 10325 5100
NoConn ~ 10325 5200
NoConn ~ 10325 5300
NoConn ~ 10325 5400
NoConn ~ 10325 5500
$Comp
L C C1
U 1 1 59FF8477
P 2325 7425
F 0 "C1" H 2350 7525 50  0000 L CNN
F 1 "0.1uF" V 2375 7175 50  0000 L CNN
F 2 "" H 2363 7275 50  0001 C CNN
F 3 "" H 2325 7425 50  0001 C CNN
	1    2325 7425
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2475 6725 2550 6725
Wire Wire Line
	2550 6725 2550 6825
Connection ~ 2550 6775
Wire Wire Line
	2550 6825 2475 6825
Wire Wire Line
	2075 7325 2075 7425
Wire Wire Line
	2075 7425 2175 7425
$Comp
L GND #PWR06
U 1 1 59FF8F58
P 2475 7425
F 0 "#PWR06" H 2475 7175 50  0001 C CNN
F 1 "GND" H 2475 7275 50  0000 C CNN
F 2 "" H 2475 7425 50  0001 C CNN
F 3 "" H 2475 7425 50  0001 C CNN
	1    2475 7425
	1    0    0    -1  
$EndComp
Wire Wire Line
	7425 4025 8000 4025
Text Label 7425 4025 0    60   Italic 0
SHIFTIN_CLK
Wire Wire Line
	8000 4225 7425 4225
Text Label 7425 4225 0    60   Italic 0
SHIFTIN_DATA
Text Label 10325 1650 0    60   Italic 0
SHIFTIN_SELECT
$Comp
L GND #PWR020
U 1 1 59FFFABD
P 10550 6225
F 0 "#PWR020" H 10550 5975 50  0001 C CNN
F 1 "GND" H 10550 6075 50  0000 C CNN
F 2 "" H 10550 6225 50  0001 C CNN
F 3 "" H 10550 6225 50  0001 C CNN
	1    10550 6225
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 59FFFB35
P 10200 6225
F 0 "#PWR021" H 10200 6075 50  0001 C CNN
F 1 "+5V" H 10200 6365 50  0000 C CNN
F 2 "" H 10200 6225 50  0001 C CNN
F 3 "" H 10200 6225 50  0001 C CNN
	1    10200 6225
	1    0    0    -1  
$EndComp
NoConn ~ 8000 1650
$Comp
L GND #PWR022
U 1 1 5A003571
P 8000 1450
F 0 "#PWR022" H 8000 1200 50  0001 C CNN
F 1 "GND" H 8000 1300 50  0000 C CNN
F 2 "" H 8000 1450 50  0001 C CNN
F 3 "" H 8000 1450 50  0001 C CNN
	1    8000 1450
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR023
U 1 1 5A00364F
P 8000 1350
F 0 "#PWR023" H 8000 1200 50  0001 C CNN
F 1 "+5V" H 8000 1490 50  0000 C CNN
F 2 "" H 8000 1350 50  0001 C CNN
F 3 "" H 8000 1350 50  0001 C CNN
	1    8000 1350
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
