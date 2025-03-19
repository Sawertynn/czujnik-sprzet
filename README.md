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
(todo)

HTTP stuff


SMS:
(classic init)
- CSCS -> set to IRA
- CSCA -> set to plus's number
- CGMF -> set to TEXT
- CGMS -> send SMS