EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:kuro
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "FET push-pull driver"
Date "2017-02-01"
Rev "1.0"
Comp "KEIO"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BSS84 Q1
U 1 1 588FBBAA
P 4450 2100
F 0 "Q1" H 4650 2175 50  0000 L CNN
F 1 "BSS84" H 4650 2100 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4650 2025 50  0001 L CIN
F 3 "" H 4650 2175 50  0000 L CNN
	1    4450 2100
	1    0    0    1   
$EndComp
$Comp
L BSS138 Q2
U 1 1 588FBC23
P 3400 2800
F 0 "Q2" H 3600 2875 50  0000 L CNN
F 1 "BSS138" H 3600 2800 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3600 2725 50  0001 L CIN
F 3 "" H 3400 2800 50  0000 L CNN
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 588FBD14
P 4550 3100
F 0 "#PWR01" H 4550 2850 50  0001 C CNN
F 1 "GND" H 4550 2950 50  0000 C CNN
F 2 "" H 4550 3100 50  0000 C CNN
F 3 "" H 4550 3100 50  0000 C CNN
	1    4550 3100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 588FBD2C
P 4550 1700
F 0 "#PWR02" H 4550 1550 50  0001 C CNN
F 1 "VCC" H 4550 1850 50  0000 C CNN
F 2 "" H 4550 1700 50  0000 C CNN
F 3 "" H 4550 1700 50  0000 C CNN
	1    4550 1700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 588FBD46
P 3500 2150
F 0 "R1" V 3580 2150 50  0000 C CNN
F 1 "R" V 3500 2150 50  0000 C CNN
F 2 "" V 3430 2150 50  0001 C CNN
F 3 "" H 3500 2150 50  0000 C CNN
	1    3500 2150
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P W4
U 1 1 588FBD89
P 3000 2800
F 0 "W4" H 3000 3070 50  0000 C CNN
F 1 "IN1" H 3000 3000 50  0000 C CNN
F 2 "" H 3200 2800 50  0001 C CNN
F 3 "" H 3200 2800 50  0000 C CNN
	1    3000 2800
	1    0    0    -1  
$EndComp
$Comp
L BSS138 Q3
U 1 1 588FC012
P 4450 2800
F 0 "Q3" H 4650 2875 50  0000 L CNN
F 1 "BSS138" H 4650 2800 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4650 2725 50  0001 L CIN
F 3 "" H 4450 2800 50  0000 L CNN
	1    4450 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2300 3500 2600
Wire Wire Line
	3500 2450 4050 2450
Wire Wire Line
	4050 2050 4050 2850
Wire Wire Line
	4050 2850 4250 2850
Wire Wire Line
	4250 2050 4050 2050
Connection ~ 4050 2450
Connection ~ 3500 2450
Wire Wire Line
	4550 2450 5150 2450
Connection ~ 4550 2450
Wire Wire Line
	4550 3100 4550 3000
$Comp
L VCC #PWR03
U 1 1 588FC3B7
P 4550 3750
F 0 "#PWR03" H 4550 3600 50  0001 C CNN
F 1 "VCC" H 4550 3900 50  0000 C CNN
F 2 "" H 4550 3750 50  0000 C CNN
F 3 "" H 4550 3750 50  0000 C CNN
	1    4550 3750
	1    0    0    -1  
$EndComp
$Comp
L BSS84 Q4
U 1 1 588FC42B
P 4450 4150
F 0 "Q4" H 4650 4225 50  0000 L CNN
F 1 "BSS84" H 4650 4150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4650 4075 50  0001 L CIN
F 3 "" H 4650 4225 50  0000 L CNN
	1    4450 4150
	1    0    0    1   
$EndComp
Wire Wire Line
	4550 4500 5150 4500
Connection ~ 4550 4500
$Comp
L BSS138 Q6
U 1 1 588FC62C
P 4450 4850
F 0 "Q6" H 4650 4925 50  0000 L CNN
F 1 "BSS138" H 4650 4850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4650 4775 50  0001 L CIN
F 3 "" H 4450 4850 50  0000 L CNN
	1    4450 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 588FC66D
P 4550 5150
F 0 "#PWR04" H 4550 4900 50  0001 C CNN
F 1 "GND" H 4550 5000 50  0000 C CNN
F 2 "" H 4550 5150 50  0000 C CNN
F 3 "" H 4550 5150 50  0000 C CNN
	1    4550 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5150 4550 5050
Wire Wire Line
	4250 4100 4050 4100
Wire Wire Line
	4050 4100 4050 4900
Wire Wire Line
	4050 4900 4250 4900
Connection ~ 4050 4500
$Comp
L BSS138 Q5
U 1 1 588FC9C8
P 3400 4850
F 0 "Q5" H 3600 4925 50  0000 L CNN
F 1 "BSS138" H 3600 4850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3600 4775 50  0001 L CIN
F 3 "" H 3400 4850 50  0000 L CNN
	1    3400 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4350 3500 4650
Wire Wire Line
	3500 4500 4050 4500
Connection ~ 3500 4500
$Comp
L R R2
U 1 1 588FCB0A
P 3500 4200
F 0 "R2" V 3580 4200 50  0000 C CNN
F 1 "R" V 3500 4200 50  0000 C CNN
F 2 "" V 3430 4200 50  0001 C CNN
F 3 "" H 3500 4200 50  0000 C CNN
	1    3500 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2850 3000 2850
Wire Wire Line
	3000 2850 3000 2800
$Comp
L TEST_1P W6
U 1 1 588FCDEE
P 3000 4850
F 0 "W6" H 3000 5120 50  0000 C CNN
F 1 "IN2" H 3000 5050 50  0000 C CNN
F 2 "" H 3200 4850 50  0001 C CNN
F 3 "" H 3200 4850 50  0000 C CNN
	1    3000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4900 3000 4900
Wire Wire Line
	3000 4900 3000 4850
$Comp
L TEST_1P W5
U 1 1 588FD19C
P 5150 4450
F 0 "W5" H 5150 4720 50  0000 C CNN
F 1 "OUT2" H 5150 4650 50  0000 C CNN
F 2 "" H 5350 4450 50  0001 C CNN
F 3 "" H 5350 4450 50  0000 C CNN
	1    5150 4450
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P W3
U 1 1 588FD262
P 5150 2400
F 0 "W3" H 5150 2670 50  0000 C CNN
F 1 "OUT1" H 5150 2600 50  0000 C CNN
F 2 "" H 5350 2400 50  0001 C CNN
F 3 "" H 5350 2400 50  0000 C CNN
	1    5150 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2450 5150 2400
Wire Wire Line
	5150 4500 5150 4450
Wire Wire Line
	4550 2300 4550 2600
Wire Wire Line
	4550 1700 4550 1900
Wire Wire Line
	4550 1800 3500 1800
Wire Wire Line
	3500 1800 3500 2000
Connection ~ 4550 1800
Wire Wire Line
	4550 4350 4550 4650
Wire Wire Line
	4550 3750 4550 3950
Wire Wire Line
	4550 3850 3500 3850
Wire Wire Line
	3500 3850 3500 4050
Connection ~ 4550 3850
$Comp
L GND #PWR05
U 1 1 5890FAB7
P 3500 3100
F 0 "#PWR05" H 3500 2850 50  0001 C CNN
F 1 "GND" H 3500 2950 50  0000 C CNN
F 2 "" H 3500 3100 50  0000 C CNN
F 3 "" H 3500 3100 50  0000 C CNN
	1    3500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3100 3500 3000
$Comp
L GND #PWR06
U 1 1 5890FD28
P 3500 5150
F 0 "#PWR06" H 3500 4900 50  0001 C CNN
F 1 "GND" H 3500 5000 50  0000 C CNN
F 2 "" H 3500 5150 50  0000 C CNN
F 3 "" H 3500 5150 50  0000 C CNN
	1    3500 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5150 3500 5050
$Comp
L TEST_1P W1
U 1 1 58910040
P 6300 1550
F 0 "W1" H 6300 1820 50  0000 C CNN
F 1 "MOUNT1" H 6300 1750 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.5mm_Pad" H 6500 1550 50  0001 C CNN
F 3 "" H 6500 1550 50  0000 C CNN
	1    6300 1550
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P W2
U 1 1 58910461
P 7050 1550
F 0 "W2" H 7050 1820 50  0000 C CNN
F 1 "GND" H 7050 1750 50  0000 C CNN
F 2 "" H 7250 1550 50  0001 C CNN
F 3 "" H 7250 1550 50  0000 C CNN
	1    7050 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5891056F
P 6300 1600
F 0 "#PWR07" H 6300 1350 50  0001 C CNN
F 1 "GND" H 6300 1450 50  0000 C CNN
F 2 "" H 6300 1600 50  0000 C CNN
F 3 "" H 6300 1600 50  0000 C CNN
	1    6300 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 589105A4
P 7050 1650
F 0 "#PWR08" H 7050 1400 50  0001 C CNN
F 1 "GND" H 7050 1500 50  0000 C CNN
F 2 "" H 7050 1650 50  0000 C CNN
F 3 "" H 7050 1650 50  0000 C CNN
	1    7050 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1550 7050 1650
Wire Wire Line
	6300 1550 6300 1600
$Comp
L TEST_1P W7
U 1 1 58922E12
P 8000 1550
F 0 "W7" H 8000 1820 50  0000 C CNN
F 1 "VCC" H 8000 1750 50  0000 C CNN
F 2 "" H 8200 1550 50  0001 C CNN
F 3 "" H 8200 1550 50  0000 C CNN
	1    8000 1550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 58922E63
P 8300 1550
F 0 "#PWR09" H 8300 1400 50  0001 C CNN
F 1 "VCC" H 8300 1700 50  0000 C CNN
F 2 "" H 8300 1550 50  0000 C CNN
F 3 "" H 8300 1550 50  0000 C CNN
	1    8300 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1550 8000 1600
Wire Wire Line
	8000 1600 8650 1600
Wire Wire Line
	8300 1600 8300 1550
$Comp
L PWR_FLAG #FLG010
U 1 1 5892349D
P 8650 1550
F 0 "#FLG010" H 8650 1645 50  0001 C CNN
F 1 "PWR_FLAG" H 8650 1730 50  0000 C CNN
F 2 "" H 8650 1550 50  0000 C CNN
F 3 "" H 8650 1550 50  0000 C CNN
	1    8650 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1600 8650 1550
Connection ~ 8300 1600
$Comp
L PWR_FLAG #FLG011
U 1 1 589242AB
P 7450 1550
F 0 "#FLG011" H 7450 1645 50  0001 C CNN
F 1 "PWR_FLAG" H 7450 1730 50  0000 C CNN
F 2 "" H 7450 1550 50  0000 C CNN
F 3 "" H 7450 1550 50  0000 C CNN
	1    7450 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1600 7450 1600
Wire Wire Line
	7450 1600 7450 1550
Connection ~ 7050 1600
$EndSCHEMATC
