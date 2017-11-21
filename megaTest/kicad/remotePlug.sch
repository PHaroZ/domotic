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
LIBS:input-cache
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
Text Label 7350 2825 0    60   ~ 0
MAX485_A
Text Label 7350 2725 0    60   ~ 0
MAX485_B
$Comp
L 74HC165 U101
U 1 1 59FF914B
P 1875 1550
F 0 "U101" H 1574 2352 50  0000 L BNN
F 1 "74HC165" H 1575 2250 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 1875 1550 60  0001 C CNN
F 3 "STMicroelectronics" H 1875 1550 50  0001 L BNN
F 4 "" H 1875 1550 50  0001 L BNN "Description"
F 5 "Unavailable" H 1875 1550 50  0001 L BNN "Availability"
F 6 "VFQFN-16 STMicroelectronics" H 1875 1550 50  0001 L BNN "Package"
F 7 "74HC165" H 1875 1550 50  0001 L BNN "MP"
F 8 "None" H 1875 1550 50  0001 L BNN "Price"
	1    1875 1550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 59FF949A
P 1150 950
F 0 "#PWR03" H 1150 800 50  0001 C CNN
F 1 "+5V" H 1150 1090 50  0000 C CNN
F 2 "" H 1150 950 50  0001 C CNN
F 3 "" H 1150 950 50  0001 C CNN
	1    1150 950 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 59FF94C2
P 1475 1750
F 0 "#PWR04" H 1475 1500 50  0001 C CNN
F 1 "GND" H 1475 1600 50  0000 C CNN
F 2 "" H 1475 1750 50  0001 C CNN
F 3 "" H 1475 1750 50  0001 C CNN
	1    1475 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	1475 1650 1475 1750
NoConn ~ 1475 1050
Wire Wire Line
	1000 1550 1475 1550
Text Label 1000 1550 0    60   Italic 0
SHIFTIN_CLK
Text Label 7350 3125 0    60   Italic 0
SHIFTIN_CLK
Text Label 7350 3325 0    60   Italic 0
SHIFTIN_DATA
Text Label 2300 1850 0    60   Italic 0
SHIFTIN_SELECT
Wire Wire Line
	2300 1850 2900 1850
NoConn ~ 1475 1350
$Comp
L 74HC165 U111
U 1 1 59FF9D59
P 1875 2775
F 0 "U111" H 1574 3577 50  0000 L BNN
F 1 "74HC165" H 1575 3475 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 1875 2775 60  0001 C CNN
F 3 "STMicroelectronics" H 1875 2775 50  0001 L BNN
F 4 "" H 1875 2775 50  0001 L BNN "Description"
F 5 "Unavailable" H 1875 2775 50  0001 L BNN "Availability"
F 6 "VFQFN-16 STMicroelectronics" H 1875 2775 50  0001 L BNN "Package"
F 7 "74HC165" H 1875 2775 50  0001 L BNN "MP"
F 8 "None" H 1875 2775 50  0001 L BNN "Price"
	1    1875 2775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 59FF9D65
P 1475 2975
F 0 "#PWR05" H 1475 2725 50  0001 C CNN
F 1 "GND" H 1475 2825 50  0000 C CNN
F 2 "" H 1475 2975 50  0001 C CNN
F 3 "" H 1475 2975 50  0001 C CNN
	1    1475 2975
	0    1    1    0   
$EndComp
Wire Wire Line
	1475 2875 1475 2975
Wire Wire Line
	1000 2775 1475 2775
Text Label 1000 2775 0    60   Italic 0
SHIFTIN_CLK
NoConn ~ 1475 2575
Wire Wire Line
	1475 1250 875  1250
Wire Wire Line
	875  1250 875  2275
Wire Wire Line
	875  2275 1475 2275
$Comp
L 74HC165 U121
U 1 1 59FFA173
P 1875 3975
F 0 "U121" H 1574 4777 50  0000 L BNN
F 1 "74HC165" H 1575 4675 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 1875 3975 60  0001 C CNN
F 3 "STMicroelectronics" H 1875 3975 50  0001 L BNN
F 4 "" H 1875 3975 50  0001 L BNN "Description"
F 5 "Unavailable" H 1875 3975 50  0001 L BNN "Availability"
F 6 "VFQFN-16 STMicroelectronics" H 1875 3975 50  0001 L BNN "Package"
F 7 "74HC165" H 1875 3975 50  0001 L BNN "MP"
F 8 "None" H 1875 3975 50  0001 L BNN "Price"
	1    1875 3975
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3975 1475 3975
Text Label 1000 3975 0    60   Italic 0
SHIFTIN_CLK
NoConn ~ 1475 3775
Wire Wire Line
	875  3475 1475 3475
Wire Wire Line
	1475 2475 875  2475
Wire Wire Line
	875  2475 875  3475
$Comp
L 74HC165 U131
U 1 1 59FFA2F1
P 1875 5175
F 0 "U131" H 1574 5977 50  0000 L BNN
F 1 "74HC165" H 1575 5875 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 1875 5175 60  0001 C CNN
F 3 "STMicroelectronics" H 1875 5175 50  0001 L BNN
F 4 "" H 1875 5175 50  0001 L BNN "Description"
F 5 "Unavailable" H 1875 5175 50  0001 L BNN "Availability"
F 6 "VFQFN-16 STMicroelectronics" H 1875 5175 50  0001 L BNN "Package"
F 7 "74HC165" H 1875 5175 50  0001 L BNN "MP"
F 8 "None" H 1875 5175 50  0001 L BNN "Price"
	1    1875 5175
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 59FFA2FD
P 1475 5375
F 0 "#PWR06" H 1475 5125 50  0001 C CNN
F 1 "GND" H 1475 5225 50  0000 C CNN
F 2 "" H 1475 5375 50  0001 C CNN
F 3 "" H 1475 5375 50  0001 C CNN
	1    1475 5375
	0    1    1    0   
$EndComp
Wire Wire Line
	1475 5275 1475 5375
Wire Wire Line
	1000 5175 1475 5175
Text Label 1000 5175 0    60   Italic 0
SHIFTIN_CLK
NoConn ~ 1475 4975
Wire Wire Line
	875  4675 1475 4675
Wire Wire Line
	1475 3675 875  3675
Wire Wire Line
	875  3675 875  4675
Wire Wire Line
	1475 4875 875  4875
Text Label 875  4875 0    60   Italic 0
SHIFTIN_DATA
Text Label 7350 3225 0    60   Italic 0
SHIFTIN_SELECT
$Comp
L R R101
U 1 1 59FFA9E3
P 2450 950
F 0 "R101" V 2450 1125 50  0000 C CNN
F 1 "1k" V 2450 950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 950 50  0001 C CNN
F 3 "" H 2450 950 50  0001 C CNN
	1    2450 950 
	0    1    1    0   
$EndComp
$Comp
L Conn_01x08_Female J101
U 1 1 59FFAE55
P 3200 1200
F 0 "J101" H 3200 1600 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3250 1150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3200 1200 50  0001 C CNN
F 3 "" H 3200 1200 50  0001 C CNN
	1    3200 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 900  3000 900 
Wire Wire Line
	2300 1000 3000 1000
Wire Wire Line
	2300 1100 3000 1100
Wire Wire Line
	2300 1200 3000 1200
Wire Wire Line
	2300 1300 3000 1300
Wire Wire Line
	2300 1400 3000 1400
Wire Wire Line
	2300 1500 3000 1500
Wire Wire Line
	2300 1600 3000 1600
$Comp
L R R102
U 1 1 59FFB2CB
P 2450 1050
F 0 "R102" V 2450 1225 50  0000 C CNN
F 1 "1k" V 2450 1050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1050 50  0001 C CNN
F 3 "" H 2450 1050 50  0001 C CNN
	1    2450 1050
	0    1    1    0   
$EndComp
$Comp
L R R103
U 1 1 59FFB305
P 2450 1150
F 0 "R103" V 2450 1325 50  0000 C CNN
F 1 "1k" V 2450 1150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1150 50  0001 C CNN
F 3 "" H 2450 1150 50  0001 C CNN
	1    2450 1150
	0    1    1    0   
$EndComp
$Comp
L R R104
U 1 1 59FFB348
P 2450 1250
F 0 "R104" V 2450 1425 50  0000 C CNN
F 1 "1k" V 2450 1250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1250 50  0001 C CNN
F 3 "" H 2450 1250 50  0001 C CNN
	1    2450 1250
	0    1    1    0   
$EndComp
$Comp
L R R105
U 1 1 59FFB3C5
P 2450 1350
F 0 "R105" V 2450 1525 50  0000 C CNN
F 1 "1k" V 2450 1350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1350 50  0001 C CNN
F 3 "" H 2450 1350 50  0001 C CNN
	1    2450 1350
	0    1    1    0   
$EndComp
$Comp
L R R106
U 1 1 59FFB400
P 2450 1450
F 0 "R106" V 2450 1625 50  0000 C CNN
F 1 "1k" V 2450 1450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1450 50  0001 C CNN
F 3 "" H 2450 1450 50  0001 C CNN
	1    2450 1450
	0    1    1    0   
$EndComp
$Comp
L R R107
U 1 1 59FFB451
P 2450 1550
F 0 "R107" V 2450 1725 50  0000 C CNN
F 1 "1k" V 2450 1550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1550 50  0001 C CNN
F 3 "" H 2450 1550 50  0001 C CNN
	1    2450 1550
	0    1    1    0   
$EndComp
$Comp
L R R108
U 1 1 59FFB53D
P 2450 1650
F 0 "R108" V 2450 1825 50  0000 C CNN
F 1 "1k" V 2450 1650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 1650 50  0001 C CNN
F 3 "" H 2450 1650 50  0001 C CNN
	1    2450 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 825  2700 1650
$Comp
L +5V #PWR07
U 1 1 59FFB610
P 2700 825
F 0 "#PWR07" H 2700 675 50  0001 C CNN
F 1 "+5V" H 2700 965 50  0000 C CNN
F 2 "" H 2700 825 50  0001 C CNN
F 3 "" H 2700 825 50  0001 C CNN
	1    2700 825 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1650 2600 1650
Wire Wire Line
	2600 1550 2700 1550
Connection ~ 2700 1550
Wire Wire Line
	2600 1450 2700 1450
Wire Wire Line
	2700 1450 2700 1425
Wire Wire Line
	2600 1350 2700 1350
Connection ~ 2700 1350
Wire Wire Line
	2600 1250 2700 1250
Connection ~ 2700 1250
Wire Wire Line
	2600 1150 2700 1150
Connection ~ 2700 1150
Wire Wire Line
	2600 1050 2700 1050
Connection ~ 2700 1050
Wire Wire Line
	2600 950  2700 950 
Connection ~ 2700 950 
Connection ~ 2700 1450
$Comp
L Conn_01x08_Female J102
U 1 1 59FFBBA8
P 3550 1200
F 0 "J102" H 3550 1600 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3600 1150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3550 1200 50  0001 C CNN
F 3 "" H 3550 1200 50  0001 C CNN
	1    3550 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 900  3350 1600
$Comp
L GND #PWR08
U 1 1 59FFBC5C
P 3350 1600
F 0 "#PWR08" H 3350 1350 50  0001 C CNN
F 1 "GND" H 3350 1450 50  0000 C CNN
F 2 "" H 3350 1600 50  0001 C CNN
F 3 "" H 3350 1600 50  0001 C CNN
	1    3350 1600
	1    0    0    -1  
$EndComp
Connection ~ 3350 1600
Connection ~ 3350 1500
Connection ~ 3350 1400
Connection ~ 3350 1300
Connection ~ 3350 1200
Connection ~ 3350 1100
Connection ~ 3350 1000
Wire Wire Line
	2275 1650 2300 1650
Wire Wire Line
	2300 1650 2300 1600
Wire Wire Line
	2275 1550 2300 1550
Wire Wire Line
	2300 1550 2300 1500
Wire Wire Line
	2275 1450 2300 1450
Wire Wire Line
	2300 1450 2300 1400
Wire Wire Line
	2275 1350 2300 1350
Wire Wire Line
	2300 1350 2300 1300
Wire Wire Line
	2275 1250 2300 1250
Wire Wire Line
	2300 1250 2300 1200
Wire Wire Line
	2275 1150 2300 1150
Wire Wire Line
	2300 1150 2300 1100
Wire Wire Line
	2275 1050 2300 1050
Wire Wire Line
	2300 1050 2300 1000
Wire Wire Line
	2275 950  2300 950 
Wire Wire Line
	2300 950  2300 900 
Wire Wire Line
	2275 1750 2300 1750
Wire Wire Line
	2300 1750 2300 1850
Text Label 2300 3075 0    60   Italic 0
SHIFTIN_SELECT
Wire Wire Line
	2300 3075 2900 3075
$Comp
L R R111
U 1 1 59FFD02C
P 2450 2175
F 0 "R111" V 2450 2350 50  0000 C CNN
F 1 "1k" V 2450 2175 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2175 50  0001 C CNN
F 3 "" H 2450 2175 50  0001 C CNN
	1    2450 2175
	0    1    1    0   
$EndComp
$Comp
L Conn_01x08_Female J111
U 1 1 59FFD032
P 3200 2425
F 0 "J111" H 3200 2825 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3250 2375 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3200 2425 50  0001 C CNN
F 3 "" H 3200 2425 50  0001 C CNN
	1    3200 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2125 3000 2125
Wire Wire Line
	2300 2225 3000 2225
Wire Wire Line
	2300 2325 3000 2325
Wire Wire Line
	2300 2425 3000 2425
Wire Wire Line
	2300 2525 3000 2525
Wire Wire Line
	2300 2625 3000 2625
Wire Wire Line
	2300 2725 3000 2725
Wire Wire Line
	2300 2825 3000 2825
$Comp
L R R112
U 1 1 59FFD040
P 2450 2275
F 0 "R112" V 2450 2450 50  0000 C CNN
F 1 "1k" V 2450 2275 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2275 50  0001 C CNN
F 3 "" H 2450 2275 50  0001 C CNN
	1    2450 2275
	0    1    1    0   
$EndComp
$Comp
L R R113
U 1 1 59FFD046
P 2450 2375
F 0 "R113" V 2450 2550 50  0000 C CNN
F 1 "1k" V 2450 2375 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2375 50  0001 C CNN
F 3 "" H 2450 2375 50  0001 C CNN
	1    2450 2375
	0    1    1    0   
$EndComp
$Comp
L R R114
U 1 1 59FFD04C
P 2450 2475
F 0 "R114" V 2450 2650 50  0000 C CNN
F 1 "1k" V 2450 2475 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2475 50  0001 C CNN
F 3 "" H 2450 2475 50  0001 C CNN
	1    2450 2475
	0    1    1    0   
$EndComp
$Comp
L R R115
U 1 1 59FFD052
P 2450 2575
F 0 "R115" V 2450 2750 50  0000 C CNN
F 1 "1k" V 2450 2575 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2575 50  0001 C CNN
F 3 "" H 2450 2575 50  0001 C CNN
	1    2450 2575
	0    1    1    0   
$EndComp
$Comp
L R R116
U 1 1 59FFD058
P 2450 2675
F 0 "R116" V 2450 2850 50  0000 C CNN
F 1 "1k" V 2450 2675 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2675 50  0001 C CNN
F 3 "" H 2450 2675 50  0001 C CNN
	1    2450 2675
	0    1    1    0   
$EndComp
$Comp
L R R117
U 1 1 59FFD05E
P 2450 2775
F 0 "R117" V 2450 2950 50  0000 C CNN
F 1 "1k" V 2450 2775 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2775 50  0001 C CNN
F 3 "" H 2450 2775 50  0001 C CNN
	1    2450 2775
	0    1    1    0   
$EndComp
$Comp
L R R118
U 1 1 59FFD064
P 2450 2875
F 0 "R118" V 2450 3050 50  0000 C CNN
F 1 "1k" V 2450 2875 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2875 50  0001 C CNN
F 3 "" H 2450 2875 50  0001 C CNN
	1    2450 2875
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR09
U 1 1 59FFD06B
P 2700 2100
F 0 "#PWR09" H 2700 1950 50  0001 C CNN
F 1 "+5V" H 2700 2240 50  0000 C CNN
F 2 "" H 2700 2100 50  0001 C CNN
F 3 "" H 2700 2100 50  0001 C CNN
	1    2700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 2875 2600 2875
Wire Wire Line
	2700 2775 2600 2775
Connection ~ 2700 2775
Wire Wire Line
	2700 2675 2600 2675
Wire Wire Line
	2700 2650 2700 2875
Wire Wire Line
	2700 2575 2600 2575
Connection ~ 2700 2575
Wire Wire Line
	2700 2475 2600 2475
Connection ~ 2700 2475
Wire Wire Line
	2700 2375 2600 2375
Connection ~ 2700 2375
Wire Wire Line
	2700 2275 2600 2275
Connection ~ 2700 2275
Wire Wire Line
	2600 2175 2700 2175
Connection ~ 2700 2175
Connection ~ 2700 2675
$Comp
L Conn_01x08_Female J112
U 1 1 59FFD081
P 3550 2425
F 0 "J112" H 3550 2825 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3600 2375 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3550 2425 50  0001 C CNN
F 3 "" H 3550 2425 50  0001 C CNN
	1    3550 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2125 3350 2825
$Comp
L GND #PWR010
U 1 1 59FFD088
P 3350 2825
F 0 "#PWR010" H 3350 2575 50  0001 C CNN
F 1 "GND" H 3350 2675 50  0000 C CNN
F 2 "" H 3350 2825 50  0001 C CNN
F 3 "" H 3350 2825 50  0001 C CNN
	1    3350 2825
	1    0    0    -1  
$EndComp
Connection ~ 3350 2825
Connection ~ 3350 2725
Connection ~ 3350 2625
Connection ~ 3350 2525
Connection ~ 3350 2425
Connection ~ 3350 2325
Connection ~ 3350 2225
Wire Wire Line
	2275 2875 2300 2875
Wire Wire Line
	2300 2875 2300 2825
Wire Wire Line
	2275 2775 2300 2775
Wire Wire Line
	2300 2775 2300 2725
Wire Wire Line
	2275 2675 2300 2675
Wire Wire Line
	2300 2675 2300 2625
Wire Wire Line
	2275 2575 2300 2575
Wire Wire Line
	2300 2575 2300 2525
Wire Wire Line
	2275 2475 2300 2475
Wire Wire Line
	2300 2475 2300 2425
Wire Wire Line
	2275 2375 2300 2375
Wire Wire Line
	2300 2375 2300 2325
Wire Wire Line
	2275 2275 2300 2275
Wire Wire Line
	2300 2275 2300 2225
Wire Wire Line
	2275 2175 2300 2175
Wire Wire Line
	2300 2175 2300 2125
Wire Wire Line
	2275 2975 2300 2975
Wire Wire Line
	2300 2975 2300 3075
Wire Wire Line
	2700 2100 2700 2675
Text Label 2300 4275 0    60   Italic 0
SHIFTIN_SELECT
Wire Wire Line
	2300 4275 2900 4275
$Comp
L R R121
U 1 1 59FFD6F7
P 2450 3375
F 0 "R121" V 2450 3550 50  0000 C CNN
F 1 "1k" V 2450 3375 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3375 50  0001 C CNN
F 3 "" H 2450 3375 50  0001 C CNN
	1    2450 3375
	0    1    1    0   
$EndComp
$Comp
L Conn_01x08_Female J121
U 1 1 59FFD6FD
P 3200 3625
F 0 "J121" H 3200 4025 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3250 3575 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3200 3625 50  0001 C CNN
F 3 "" H 3200 3625 50  0001 C CNN
	1    3200 3625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3325 3000 3325
Wire Wire Line
	2300 3425 3000 3425
Wire Wire Line
	2300 3525 3000 3525
Wire Wire Line
	2300 3625 3000 3625
Wire Wire Line
	2300 3725 3000 3725
Wire Wire Line
	2300 3825 3000 3825
Wire Wire Line
	2300 3925 3000 3925
Wire Wire Line
	2300 4025 3000 4025
$Comp
L R R122
U 1 1 59FFD70B
P 2450 3475
F 0 "R122" V 2450 3650 50  0000 C CNN
F 1 "1k" V 2450 3475 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3475 50  0001 C CNN
F 3 "" H 2450 3475 50  0001 C CNN
	1    2450 3475
	0    1    1    0   
$EndComp
$Comp
L R R123
U 1 1 59FFD711
P 2450 3575
F 0 "R123" V 2450 3750 50  0000 C CNN
F 1 "1k" V 2450 3575 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3575 50  0001 C CNN
F 3 "" H 2450 3575 50  0001 C CNN
	1    2450 3575
	0    1    1    0   
$EndComp
$Comp
L R R124
U 1 1 59FFD717
P 2450 3675
F 0 "R124" V 2450 3850 50  0000 C CNN
F 1 "1k" V 2450 3675 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3675 50  0001 C CNN
F 3 "" H 2450 3675 50  0001 C CNN
	1    2450 3675
	0    1    1    0   
$EndComp
$Comp
L R R125
U 1 1 59FFD71D
P 2450 3775
F 0 "R125" V 2450 3950 50  0000 C CNN
F 1 "1k" V 2450 3775 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3775 50  0001 C CNN
F 3 "" H 2450 3775 50  0001 C CNN
	1    2450 3775
	0    1    1    0   
$EndComp
$Comp
L R R126
U 1 1 59FFD723
P 2450 3875
F 0 "R126" V 2450 4050 50  0000 C CNN
F 1 "1k" V 2450 3875 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3875 50  0001 C CNN
F 3 "" H 2450 3875 50  0001 C CNN
	1    2450 3875
	0    1    1    0   
$EndComp
$Comp
L R R127
U 1 1 59FFD729
P 2450 3975
F 0 "R127" V 2450 4150 50  0000 C CNN
F 1 "1k" V 2450 3975 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 3975 50  0001 C CNN
F 3 "" H 2450 3975 50  0001 C CNN
	1    2450 3975
	0    1    1    0   
$EndComp
$Comp
L R R128
U 1 1 59FFD72F
P 2450 4075
F 0 "R128" V 2450 4250 50  0000 C CNN
F 1 "1k" V 2450 4075 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4075 50  0001 C CNN
F 3 "" H 2450 4075 50  0001 C CNN
	1    2450 4075
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR011
U 1 1 59FFD735
P 2700 3300
F 0 "#PWR011" H 2700 3150 50  0001 C CNN
F 1 "+5V" H 2700 3440 50  0000 C CNN
F 2 "" H 2700 3300 50  0001 C CNN
F 3 "" H 2700 3300 50  0001 C CNN
	1    2700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4075 2600 4075
Wire Wire Line
	2700 3975 2600 3975
Connection ~ 2700 3975
Wire Wire Line
	2700 3875 2600 3875
Wire Wire Line
	2700 3850 2700 4075
Wire Wire Line
	2700 3775 2600 3775
Connection ~ 2700 3775
Wire Wire Line
	2700 3675 2600 3675
Connection ~ 2700 3675
Wire Wire Line
	2700 3575 2600 3575
Connection ~ 2700 3575
Wire Wire Line
	2700 3475 2600 3475
Connection ~ 2700 3475
Wire Wire Line
	2600 3375 2700 3375
Connection ~ 2700 3375
Connection ~ 2700 3875
$Comp
L Conn_01x08_Female J122
U 1 1 59FFD74B
P 3550 3625
F 0 "J122" H 3550 4025 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3600 3575 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3550 3625 50  0001 C CNN
F 3 "" H 3550 3625 50  0001 C CNN
	1    3550 3625
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3325 3350 4025
$Comp
L GND #PWR012
U 1 1 59FFD752
P 3350 4025
F 0 "#PWR012" H 3350 3775 50  0001 C CNN
F 1 "GND" H 3350 3875 50  0000 C CNN
F 2 "" H 3350 4025 50  0001 C CNN
F 3 "" H 3350 4025 50  0001 C CNN
	1    3350 4025
	1    0    0    -1  
$EndComp
Connection ~ 3350 4025
Connection ~ 3350 3925
Connection ~ 3350 3825
Connection ~ 3350 3725
Connection ~ 3350 3625
Connection ~ 3350 3525
Connection ~ 3350 3425
Wire Wire Line
	2275 4075 2300 4075
Wire Wire Line
	2300 4075 2300 4025
Wire Wire Line
	2275 3975 2300 3975
Wire Wire Line
	2300 3975 2300 3925
Wire Wire Line
	2275 3875 2300 3875
Wire Wire Line
	2300 3875 2300 3825
Wire Wire Line
	2275 3775 2300 3775
Wire Wire Line
	2300 3775 2300 3725
Wire Wire Line
	2275 3675 2300 3675
Wire Wire Line
	2300 3675 2300 3625
Wire Wire Line
	2275 3575 2300 3575
Wire Wire Line
	2300 3575 2300 3525
Wire Wire Line
	2275 3475 2300 3475
Wire Wire Line
	2300 3475 2300 3425
Wire Wire Line
	2275 3375 2300 3375
Wire Wire Line
	2300 3375 2300 3325
Wire Wire Line
	2275 4175 2300 4175
Wire Wire Line
	2300 4175 2300 4275
Wire Wire Line
	2700 3300 2700 3875
Text Label 2300 5475 0    60   Italic 0
SHIFTIN_SELECT
Wire Wire Line
	2300 5475 2900 5475
$Comp
L R R131
U 1 1 59FFD96A
P 2450 4575
F 0 "R131" V 2450 4750 50  0000 C CNN
F 1 "1k" V 2450 4575 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4575 50  0001 C CNN
F 3 "" H 2450 4575 50  0001 C CNN
	1    2450 4575
	0    1    1    0   
$EndComp
$Comp
L Conn_01x08_Female J131
U 1 1 59FFD970
P 3200 4825
F 0 "J131" H 3200 5225 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3250 4775 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3200 4825 50  0001 C CNN
F 3 "" H 3200 4825 50  0001 C CNN
	1    3200 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4525 3000 4525
Wire Wire Line
	2300 4625 3000 4625
Wire Wire Line
	2300 4725 3000 4725
Wire Wire Line
	2300 4825 3000 4825
Wire Wire Line
	2300 4925 3000 4925
Wire Wire Line
	2300 5025 3000 5025
Wire Wire Line
	2300 5125 3000 5125
Wire Wire Line
	2300 5225 3000 5225
$Comp
L R R132
U 1 1 59FFD97E
P 2450 4675
F 0 "R132" V 2450 4850 50  0000 C CNN
F 1 "1k" V 2450 4675 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4675 50  0001 C CNN
F 3 "" H 2450 4675 50  0001 C CNN
	1    2450 4675
	0    1    1    0   
$EndComp
$Comp
L R R133
U 1 1 59FFD984
P 2450 4775
F 0 "R133" V 2450 4950 50  0000 C CNN
F 1 "1k" V 2450 4775 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4775 50  0001 C CNN
F 3 "" H 2450 4775 50  0001 C CNN
	1    2450 4775
	0    1    1    0   
$EndComp
$Comp
L R R134
U 1 1 59FFD98A
P 2450 4875
F 0 "R134" V 2450 5050 50  0000 C CNN
F 1 "1k" V 2450 4875 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4875 50  0001 C CNN
F 3 "" H 2450 4875 50  0001 C CNN
	1    2450 4875
	0    1    1    0   
$EndComp
$Comp
L R R135
U 1 1 59FFD990
P 2450 4975
F 0 "R135" V 2450 5150 50  0000 C CNN
F 1 "1k" V 2450 4975 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 4975 50  0001 C CNN
F 3 "" H 2450 4975 50  0001 C CNN
	1    2450 4975
	0    1    1    0   
$EndComp
$Comp
L R R136
U 1 1 59FFD996
P 2450 5075
F 0 "R136" V 2450 5250 50  0000 C CNN
F 1 "1k" V 2450 5075 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 5075 50  0001 C CNN
F 3 "" H 2450 5075 50  0001 C CNN
	1    2450 5075
	0    1    1    0   
$EndComp
$Comp
L R R137
U 1 1 59FFD99C
P 2450 5175
F 0 "R137" V 2450 5350 50  0000 C CNN
F 1 "1k" V 2450 5175 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 5175 50  0001 C CNN
F 3 "" H 2450 5175 50  0001 C CNN
	1    2450 5175
	0    1    1    0   
$EndComp
$Comp
L R R138
U 1 1 59FFD9A2
P 2450 5275
F 0 "R138" V 2450 5450 50  0000 C CNN
F 1 "1k" V 2450 5275 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 5275 50  0001 C CNN
F 3 "" H 2450 5275 50  0001 C CNN
	1    2450 5275
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR013
U 1 1 59FFD9A8
P 2700 4500
F 0 "#PWR013" H 2700 4350 50  0001 C CNN
F 1 "+5V" H 2700 4640 50  0000 C CNN
F 2 "" H 2700 4500 50  0001 C CNN
F 3 "" H 2700 4500 50  0001 C CNN
	1    2700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5275 2600 5275
Wire Wire Line
	2700 5175 2600 5175
Connection ~ 2700 5175
Wire Wire Line
	2700 5075 2600 5075
Wire Wire Line
	2700 5050 2700 5275
Wire Wire Line
	2700 4975 2600 4975
Connection ~ 2700 4975
Wire Wire Line
	2700 4875 2600 4875
Connection ~ 2700 4875
Wire Wire Line
	2700 4775 2600 4775
Connection ~ 2700 4775
Wire Wire Line
	2700 4675 2600 4675
Connection ~ 2700 4675
Wire Wire Line
	2600 4575 2700 4575
Connection ~ 2700 4575
Connection ~ 2700 5075
$Comp
L Conn_01x08_Female J132
U 1 1 59FFD9BE
P 3550 4825
F 0 "J132" H 3550 5225 50  0000 C CNN
F 1 "Conn_01x08_Female" V 3600 4775 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 3550 4825 50  0001 C CNN
F 3 "" H 3550 4825 50  0001 C CNN
	1    3550 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4525 3350 5225
$Comp
L GND #PWR014
U 1 1 59FFD9C5
P 3350 5225
F 0 "#PWR014" H 3350 4975 50  0001 C CNN
F 1 "GND" H 3350 5075 50  0000 C CNN
F 2 "" H 3350 5225 50  0001 C CNN
F 3 "" H 3350 5225 50  0001 C CNN
	1    3350 5225
	1    0    0    -1  
$EndComp
Connection ~ 3350 5225
Connection ~ 3350 5125
Connection ~ 3350 5025
Connection ~ 3350 4925
Connection ~ 3350 4825
Connection ~ 3350 4725
Connection ~ 3350 4625
Wire Wire Line
	2275 5275 2300 5275
Wire Wire Line
	2300 5275 2300 5225
Wire Wire Line
	2275 5175 2300 5175
Wire Wire Line
	2300 5175 2300 5125
Wire Wire Line
	2275 5075 2300 5075
Wire Wire Line
	2300 5075 2300 5025
Wire Wire Line
	2275 4975 2300 4975
Wire Wire Line
	2300 4975 2300 4925
Wire Wire Line
	2275 4875 2300 4875
Wire Wire Line
	2300 4875 2300 4825
Wire Wire Line
	2275 4775 2300 4775
Wire Wire Line
	2300 4775 2300 4725
Wire Wire Line
	2275 4675 2300 4675
Wire Wire Line
	2300 4675 2300 4625
Wire Wire Line
	2275 4575 2300 4575
Wire Wire Line
	2300 4575 2300 4525
Wire Wire Line
	2275 5375 2300 5375
Wire Wire Line
	2300 5375 2300 5475
Wire Wire Line
	2700 4500 2700 5075
Wire Wire Line
	1475 4075 1475 4175
$Comp
L GND #PWR015
U 1 1 59FFEA08
P 1475 4175
F 0 "#PWR015" H 1475 3925 50  0001 C CNN
F 1 "GND" H 1475 4025 50  0000 C CNN
F 2 "" H 1475 4175 50  0001 C CNN
F 3 "" H 1475 4175 50  0001 C CNN
	1    1475 4175
	0    1    1    0   
$EndComp
$Comp
L GND #PWR016
U 1 1 59FFFABD
P 10550 6225
F 0 "#PWR016" H 10550 5975 50  0001 C CNN
F 1 "GND" H 10550 6075 50  0000 C CNN
F 2 "" H 10550 6225 50  0001 C CNN
F 3 "" H 10550 6225 50  0001 C CNN
	1    10550 6225
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR017
U 1 1 59FFFB35
P 10200 6225
F 0 "#PWR017" H 10200 6075 50  0001 C CNN
F 1 "+5V" H 10200 6365 50  0000 C CNN
F 2 "" H 10200 6225 50  0001 C CNN
F 3 "" H 10200 6225 50  0001 C CNN
	1    10200 6225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5A003571
P 8175 3025
F 0 "#PWR018" H 8175 2775 50  0001 C CNN
F 1 "GND" H 8175 2875 50  0000 C CNN
F 2 "" H 8175 3025 50  0001 C CNN
F 3 "" H 8175 3025 50  0001 C CNN
	1    8175 3025
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR019
U 1 1 5A00364F
P 8175 2925
F 0 "#PWR019" H 8175 2775 50  0001 C CNN
F 1 "+5V" H 8175 3065 50  0000 C CNN
F 2 "" H 8175 2925 50  0001 C CNN
F 3 "" H 8175 2925 50  0001 C CNN
	1    8175 2925
	0    -1   -1   0   
$EndComp
$Comp
L C C101
U 1 1 5A0043D4
P 1250 800
F 0 "C101" H 1275 900 50  0000 L CNN
F 1 "0.1uF" V 1200 800 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 1288 650 50  0001 C CNN
F 3 "" H 1250 800 50  0001 C CNN
	1    1250 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 950  1475 950 
$Comp
L GND #PWR020
U 1 1 5A004ED3
P 1100 800
F 0 "#PWR020" H 1100 550 50  0001 C CNN
F 1 "GND" H 1100 650 50  0000 C CNN
F 2 "" H 1100 800 50  0001 C CNN
F 3 "" H 1100 800 50  0001 C CNN
	1    1100 800 
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR021
U 1 1 5A0058B5
P 1150 2175
F 0 "#PWR021" H 1150 2025 50  0001 C CNN
F 1 "+5V" H 1150 2315 50  0000 C CNN
F 2 "" H 1150 2175 50  0001 C CNN
F 3 "" H 1150 2175 50  0001 C CNN
	1    1150 2175
	0    -1   -1   0   
$EndComp
$Comp
L C C111
U 1 1 5A0058BB
P 1250 2025
F 0 "C111" H 1275 2125 50  0000 L CNN
F 1 "0.1uF" V 1200 2025 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 1288 1875 50  0001 C CNN
F 3 "" H 1250 2025 50  0001 C CNN
	1    1250 2025
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 2175 1475 2175
$Comp
L GND #PWR022
U 1 1 5A0058C3
P 1100 2025
F 0 "#PWR022" H 1100 1775 50  0001 C CNN
F 1 "GND" H 1100 1875 50  0000 C CNN
F 2 "" H 1100 2025 50  0001 C CNN
F 3 "" H 1100 2025 50  0001 C CNN
	1    1100 2025
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR023
U 1 1 5A005AD1
P 1150 3375
F 0 "#PWR023" H 1150 3225 50  0001 C CNN
F 1 "+5V" H 1150 3515 50  0000 C CNN
F 2 "" H 1150 3375 50  0001 C CNN
F 3 "" H 1150 3375 50  0001 C CNN
	1    1150 3375
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 3375 1475 3375
$Comp
L GND #PWR024
U 1 1 5A005ADF
P 1100 3225
F 0 "#PWR024" H 1100 2975 50  0001 C CNN
F 1 "GND" H 1100 3075 50  0000 C CNN
F 2 "" H 1100 3225 50  0001 C CNN
F 3 "" H 1100 3225 50  0001 C CNN
	1    1100 3225
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR025
U 1 1 5A005CEC
P 1150 4575
F 0 "#PWR025" H 1150 4425 50  0001 C CNN
F 1 "+5V" H 1150 4715 50  0000 C CNN
F 2 "" H 1150 4575 50  0001 C CNN
F 3 "" H 1150 4575 50  0001 C CNN
	1    1150 4575
	0    -1   -1   0   
$EndComp
$Comp
L C C131
U 1 1 5A005CF2
P 1250 4425
F 0 "C131" H 1275 4525 50  0000 L CNN
F 1 "0.1uF" V 1200 4425 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 1288 4275 50  0001 C CNN
F 3 "" H 1250 4425 50  0001 C CNN
	1    1250 4425
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 4575 1475 4575
$Comp
L GND #PWR026
U 1 1 5A005CFA
P 1100 4425
F 0 "#PWR026" H 1100 4175 50  0001 C CNN
F 1 "GND" H 1100 4275 50  0000 C CNN
F 2 "" H 1100 4425 50  0001 C CNN
F 3 "" H 1100 4425 50  0001 C CNN
	1    1100 4425
	0    1    1    0   
$EndComp
$Comp
L C C121
U 1 1 5A005AD7
P 1250 3225
F 0 "C121" H 1275 3325 50  0000 L CNN
F 1 "0.1uF" V 1200 3225 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 1288 3075 50  0001 C CNN
F 3 "" H 1250 3225 50  0001 C CNN
	1    1250 3225
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 3225 1400 3375
Connection ~ 1400 3375
Wire Wire Line
	1400 4425 1400 4575
Connection ~ 1400 4575
Wire Wire Line
	1400 2025 1400 2175
Connection ~ 1400 2175
Wire Wire Line
	1400 800  1400 950 
Connection ~ 1400 950 
$Comp
L Conn_01x08_Male JARDU1
U 1 1 5A11D7E6
P 8375 3125
F 0 "JARDU1" H 8375 3525 50  0000 C CNN
F 1 "Conn_01x08_Male" H 8375 2625 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 8375 3125 50  0001 C CNN
F 3 "" H 8375 3125 50  0001 C CNN
	1    8375 3125
	-1   0    0    1   
$EndComp
Wire Wire Line
	8175 3125 7350 3125
Wire Wire Line
	8175 3225 7350 3225
Wire Wire Line
	8175 3325 7350 3325
NoConn ~ 8175 3425
$Comp
L Conn_01x20 J5V1
U 1 1 5A1204FA
P 4400 2100
F 0 "J5V1" H 4400 3100 50  0000 C CNN
F 1 "Conn_01x20" H 4400 1000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x20_Pitch2.54mm" H 4400 2100 50  0001 C CNN
F 3 "" H 4400 2100 50  0001 C CNN
	1    4400 2100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x20 JGND1
U 1 1 5A120717
P 4900 2100
F 0 "JGND1" H 4900 3100 50  0000 C CNN
F 1 "Conn_01x20" H 4900 1000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x20_Pitch2.54mm" H 4900 2100 50  0001 C CNN
F 3 "" H 4900 2100 50  0001 C CNN
	1    4900 2100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x20 JMAXA1
U 1 1 5A1207EE
P 5600 2100
F 0 "JMAXA1" H 5600 3100 50  0000 C CNN
F 1 "Conn_01x20" H 5600 1000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x20_Pitch2.54mm" H 5600 2100 50  0001 C CNN
F 3 "" H 5600 2100 50  0001 C CNN
	1    5600 2100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x20 JMAXB1
U 1 1 5A1209F2
P 6100 2100
F 0 "JMAXB1" H 6100 3100 50  0000 C CNN
F 1 "Conn_01x20" H 6100 1000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x20_Pitch2.54mm" H 6100 2100 50  0001 C CNN
F 3 "" H 6100 2100 50  0001 C CNN
	1    6100 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1025 4200 3100
Wire Wire Line
	4200 1025 4100 1025
Wire Wire Line
	4700 1025 4700 3100
Wire Wire Line
	4700 1025 4600 1025
Wire Wire Line
	5400 925  5400 3100
Wire Wire Line
	5900 1025 5900 3100
Wire Wire Line
	5900 1025 5775 1025
$Comp
L +5V #PWR027
U 1 1 5A1221EB
P 4100 1025
F 0 "#PWR027" H 4100 875 50  0001 C CNN
F 1 "+5V" H 4100 1165 50  0000 C CNN
F 2 "" H 4100 1025 50  0001 C CNN
F 3 "" H 4100 1025 50  0001 C CNN
	1    4100 1025
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 5A122308
P 4600 1025
F 0 "#PWR028" H 4600 775 50  0001 C CNN
F 1 "GND" H 4600 875 50  0000 C CNN
F 2 "" H 4600 1025 50  0001 C CNN
F 3 "" H 4600 1025 50  0001 C CNN
	1    4600 1025
	1    0    0    -1  
$EndComp
Text Label 5775 1025 0    60   ~ 0
MAX485_B
Text Label 5275 925  0    60   ~ 0
MAX485_A
Wire Wire Line
	5400 925  5275 925 
Connection ~ 4200 3000
Connection ~ 4200 2900
Connection ~ 4200 2800
Connection ~ 4200 2700
Connection ~ 4200 2600
Connection ~ 4200 2500
Connection ~ 4200 2400
Connection ~ 4200 2300
Connection ~ 4200 2200
Connection ~ 4200 2100
Connection ~ 4200 2000
Connection ~ 4200 1900
Connection ~ 4200 1800
Connection ~ 4200 1700
Connection ~ 4200 1600
Connection ~ 4200 1500
Connection ~ 4200 1400
Connection ~ 4200 1300
Connection ~ 4200 1200
Connection ~ 4700 1200
Connection ~ 4700 1300
Connection ~ 4700 1400
Connection ~ 4700 1500
Connection ~ 4700 1600
Connection ~ 4700 1700
Connection ~ 4700 1800
Connection ~ 4700 1900
Connection ~ 4700 2000
Connection ~ 4700 2100
Connection ~ 5400 2100
Connection ~ 5400 2000
Connection ~ 5400 1900
Connection ~ 5400 1800
Connection ~ 5400 1700
Connection ~ 5400 1600
Connection ~ 5400 1500
Connection ~ 5400 1400
Connection ~ 5400 1300
Connection ~ 5400 1200
Connection ~ 5900 1200
Connection ~ 5900 1300
Connection ~ 5900 1400
Connection ~ 5900 1500
Connection ~ 5900 1600
Connection ~ 5900 1700
Connection ~ 5900 1800
Connection ~ 5900 1900
Connection ~ 5900 2000
Connection ~ 5900 2100
Connection ~ 5400 2200
Connection ~ 5400 2300
Connection ~ 5400 2400
Connection ~ 5400 2500
Connection ~ 5400 2600
Connection ~ 5400 2700
Connection ~ 5400 2800
Connection ~ 5400 2900
Connection ~ 5400 3000
Connection ~ 5900 3000
Connection ~ 5900 2900
Connection ~ 5900 2800
Connection ~ 5900 2700
Connection ~ 5900 2600
Connection ~ 5900 2500
Connection ~ 5900 2400
Connection ~ 5900 2300
Connection ~ 5900 2200
Connection ~ 4700 2200
Connection ~ 4700 2300
Connection ~ 4700 2400
Connection ~ 4700 2500
Connection ~ 4700 2600
Connection ~ 4700 2700
Connection ~ 4700 2800
Connection ~ 4700 2900
Connection ~ 4700 3000
Wire Wire Line
	8175 2825 7350 2825
Wire Wire Line
	8175 2725 7350 2725
$EndSCHEMATC