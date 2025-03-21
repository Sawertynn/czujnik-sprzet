# !TODO
- ssl
- mqtt
- checksignal
- clean up code


# Overview
Now we do it the other way:

we use A7670E

Serial Communication:
- init communication in 115200
- send IPR=9600 to change speed
- end communication in arduino and start with speed 9600

Service attach
- CREG=1
- CXX
- CXX

SSL stuff
- #!TODO

HTTP stuff
- HTTPINIT
- HTTPPARA ("URL")
- HTTPDATA
- HTTPACTION
- HTTPTERM

SMS:
(classic init)
- CSCS -> set to IRA
- CSCA -> set to plus's number
- CGMF -> set to TEXT
- CGMS -> send SMS


# Manual/Instrukcja programowania w Arduino IDE
Przed setup()
- ustawić stałe

setup()
- włączyć komunikację szeregową
- turn_on
- change_baud_rate()
- waitFor("PB DONE", 10)
- check sim card()
- check signal 
- attachService()

setup() for SMS
- setupSMS()
- sendSMS()

setup() for HTTP(S) POST
- httpConnect()
- httpPost()
- httpDisconnect()
