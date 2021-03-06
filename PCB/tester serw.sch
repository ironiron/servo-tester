EESchema Schematic File Version 2
LIBS:tester serw-rescue
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
LIBS:tester serw-cache
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
L ATTINY13A-SS IC1
U 1 1 598F306D
P 5110 2820
F 0 "IC1" H 4310 3220 50  0000 C CNN
F 1 "ATTINY13A-SS" H 5760 2420 50  0000 C CNN
F 2 "Housings_SOIC:SOIJ-8_5.3x5.3mm_Pitch1.27mm" H 5710 2820 50  0001 C CIN
F 3 "" H 4310 3170 50  0000 C CNN
	1    5110 2820
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 598F35AC
P 6110 2800
F 0 "C1" H 6135 2900 50  0000 L CNN
F 1 "100n" H 6135 2700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6148 2650 50  0001 C CNN
F 3 "" H 6110 2800 50  0000 C CNN
	1    6110 2800
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 598F3653
P 3950 3300
F 0 "R1" V 4030 3300 50  0000 C CNN
F 1 "10k" V 3950 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3880 3300 50  0001 C CNN
F 3 "" H 3950 3300 50  0000 C CNN
	1    3950 3300
	-1   0    0    1   
$EndComp
$Comp
L POT-RESCUE-tester_serw RV1
U 1 1 598F3946
P 3650 2970
F 0 "RV1" H 3650 2890 50  0000 C CNN
F 1 "10K" H 3650 2970 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Alps-RK16-single" H 3650 2970 50  0001 C CNN
F 3 "" H 3650 2970 50  0000 C CNN
	1    3650 2970
	0    1    1    0   
$EndComp
$Comp
L CONN_01X03 P3
U 1 1 598F3E1E
P 3125 2650
F 0 "P3" H 3125 2850 50  0000 C CNN
F 1 "servo" V 3225 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 3125 2650 50  0001 C CNN
F 3 "" H 3125 2650 50  0000 C CNN
	1    3125 2650
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 598F3FE9
P 6950 2700
F 0 "P4" H 6950 2850 50  0000 C CNN
F 1 "power" V 7050 2700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6950 2700 50  0001 C CNN
F 3 "" H 6950 2700 50  0000 C CNN
	1    6950 2700
	1    0    0    -1  
$EndComp
$Comp
L AVR-ISP-10 CON1
U 1 1 598F4267
P 4900 1975
F 0 "CON1" H 4730 2305 50  0000 C CNN
F 1 "AVR-ISP-10" H 4560 1645 50  0000 L BNN
F 2 "Connectors:IDC_Header_Straight_10pins" V 4150 2025 50  0001 C CNN
F 3 "" H 4900 1975 50  0000 C CNN
	1    4900 1975
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH_SMALL_H SW1
U 1 1 598F4472
P 3800 2670
F 0 "SW1" H 3880 2780 50  0000 C CNN
F 1 "button" H 4160 2610 50  0001 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_REED_CT05-XXXX-G1" H 3800 2870 50  0001 C CNN
F 3 "" H 3800 2870 50  0000 C CNN
	1    3800 2670
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 598F48F0
P 2775 2650
F 0 "P2" H 2775 2850 50  0000 C CNN
F 1 "servo" V 2875 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 2775 2650 50  0001 C CNN
F 3 "" H 2775 2650 50  0000 C CNN
	1    2775 2650
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P1
U 1 1 598F4929
P 2400 2650
F 0 "P1" H 2400 2850 50  0000 C CNN
F 1 "servo" V 2500 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 2400 2650 50  0001 C CNN
F 3 "" H 2400 2650 50  0000 C CNN
	1    2400 2650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR01
U 1 1 598F84B4
P 3325 2840
F 0 "#PWR01" H 3325 2590 50  0001 C CNN
F 1 "GND" H 3325 2690 50  0000 C CNN
F 2 "" H 3325 2840 50  0000 C CNN
F 3 "" H 3325 2840 50  0000 C CNN
	1    3325 2840
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR02
U 1 1 598F8733
P 4215 3450
F 0 "#PWR02" H 4215 3300 50  0001 C CNN
F 1 "+BATT" H 4215 3590 50  0000 C CNN
F 2 "" H 4215 3450 50  0000 C CNN
F 3 "" H 4215 3450 50  0000 C CNN
	1    4215 3450
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR03
U 1 1 598F8AFC
P 6750 2575
F 0 "#PWR03" H 6750 2425 50  0001 C CNN
F 1 "+BATT" H 6750 2715 50  0000 C CNN
F 2 "" H 6750 2575 50  0000 C CNN
F 3 "" H 6750 2575 50  0000 C CNN
	1    6750 2575
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 598F8BF7
P 6750 2800
F 0 "#PWR04" H 6750 2550 50  0001 C CNN
F 1 "GND" H 6750 2650 50  0000 C CNN
F 2 "" H 6750 2800 50  0000 C CNN
F 3 "" H 6750 2800 50  0000 C CNN
	1    6750 2800
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR05
U 1 1 598F9888
P 3530 2650
F 0 "#PWR05" H 3530 2500 50  0001 C CNN
F 1 "+BATT" H 3530 2790 50  0000 C CNN
F 2 "" H 3530 2650 50  0000 C CNN
F 3 "" H 3530 2650 50  0000 C CNN
	1    3530 2650
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR06
U 1 1 598FA5DC
P 5290 1745
F 0 "#PWR06" H 5290 1595 50  0001 C CNN
F 1 "+BATT" H 5290 1885 50  0000 C CNN
F 2 "" H 5290 1745 50  0000 C CNN
F 3 "" H 5290 1745 50  0000 C CNN
	1    5290 1745
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 598FA740
P 5325 2105
F 0 "#PWR07" H 5325 1855 50  0001 C CNN
F 1 "GND" H 5325 1955 50  0000 C CNN
F 2 "" H 5325 2105 50  0000 C CNN
F 3 "" H 5325 2105 50  0000 C CNN
	1    5325 2105
	1    0    0    -1  
$EndComp
Wire Wire Line
	6110 2570 6110 2650
Wire Wire Line
	6110 2950 6110 3070
Wire Wire Line
	3800 2970 4110 2970
Wire Wire Line
	3650 3120 3650 3450
Wire Wire Line
	3650 3450 4215 3450
Wire Wire Line
	2600 2550 3325 2550
Connection ~ 2975 2550
Wire Wire Line
	2600 2650 3530 2650
Connection ~ 2975 2650
Wire Wire Line
	2600 2750 3650 2750
Connection ~ 2975 2750
Wire Wire Line
	4950 1875 4950 2175
Connection ~ 4950 2075
Connection ~ 4950 1975
Wire Wire Line
	3950 2670 4110 2670
Wire Wire Line
	3650 2670 3650 2820
Connection ~ 3950 3450
Wire Wire Line
	6750 2800 6750 2750
Wire Wire Line
	6750 2650 6750 2575
Wire Wire Line
	6750 2650 6365 2650
Wire Wire Line
	6365 2650 6365 2570
Wire Wire Line
	6365 2570 6110 2570
Wire Wire Line
	6750 2750 6435 2750
Wire Wire Line
	6435 2750 6435 3070
Wire Wire Line
	6435 3070 6110 3070
Wire Wire Line
	3325 2750 3325 2840
Connection ~ 3650 2750
Connection ~ 3325 2750
Connection ~ 3325 2650
Wire Wire Line
	4110 1775 4110 2570
Wire Wire Line
	4110 2450 3325 2450
Wire Wire Line
	3325 2450 3325 2550
Wire Wire Line
	5290 1745 5290 1775
Wire Wire Line
	5290 1775 4950 1775
Wire Wire Line
	4950 2075 5325 2075
Wire Wire Line
	5325 2075 5325 2105
Connection ~ 4110 2450
Wire Wire Line
	4700 2075 4070 2075
Wire Wire Line
	4070 2075 4070 2770
Wire Wire Line
	4070 2770 4110 2770
Wire Wire Line
	4700 1975 3950 1975
Wire Wire Line
	3950 1975 3950 3150
Wire Wire Line
	3950 3070 4110 3070
Wire Wire Line
	4010 2175 4705 2175
Wire Wire Line
	4010 2175 4010 2670
Connection ~ 4010 2670
Wire Wire Line
	4700 1775 4110 1775
Connection ~ 3950 3070
Connection ~ 4700 2175
$EndSCHEMATC
