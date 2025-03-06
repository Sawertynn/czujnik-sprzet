2 files are important here:
1. czujnik-sprzet/sketch_mar03b/sketch_mar03b
- that's the main part

2. libraries/DFRobot_SIM700/DFRobot_SIM700.cpp
- the 'AT+' commands are incompatible, so we had to rewrite them a bit


TODO list:
- tidy up
    - move code from `attachService` to appropriate functions
    - modify those functions to fit the new AT commands
    - 
- SMS stuff
- LTE stuff
- MQTT stuff