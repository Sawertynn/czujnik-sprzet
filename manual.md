# Instrukcja programowania
## Załączony przykład
Na początku `#define MODE_XXX T` do ustawiania jaką komunikację chcemy T=1 włączamy, T=0 wyłączamy

Po przejściu przez kod w setup() włącza się tryb interaktywny do bezpośredniego wprowadzaia poleceń z klawiatury.

## Metody (funkcje) klasy DFRobot_SIM7000 (zmienna sim7000):

Wspólne dla wszystkich trybów, na start:
- turnOn()
- changeBaudRate(9600);
    - zmiana zegara do komunikacji między ardu i a76xx, lepiej zmieniać ale nie ma dużej różnicy
- checkSIMStatus()
    - czy jest SIM
- checkSignal()
    - zwraca siłę sygnału
- attachService(APN)
    - podłączenie się do APN

SMS:
- setupSMS(SMS_CENTRAL_SERVICE)
- sendSMS(telephone_number, datastring)

SSL:
- setupSSL(NTP_SERVER, TIME_ZONE)
    - serwer ntp, generalnie "pool.ntp.org"
    - time_zone - strefa czasowa w przesuniętych godzinach (-1, +2) - trzeba uwzględnić czas letni

HTTP(S):
- httpConnect(host)
    - host w postaci "protokół://nazwa.domena:port", np. "https://nazwa.domena", "http://nazwa.domena:1234"
- httpPost(host, data, {readlen})
    - host jak wyżej
    - readlen - opcjonalny - ile wypisać znaków odpowiedzi od serwera, domyślnie nie wypisuje odpowiedzi

MQTT:

- mqttInit(client_id, use_ssl = true)
    - client_id - id klienta
    - use_ssl - czy korzystać z ssl czy nie, domyślnie tak
- mqttConnect(broker_addr, login = "", password = "")
    - broker_addr - adres brokera MQTT, postaci "tcp://nazwa.domena:port" - tcp i port są konieczne
    - login, password - dane uwierz., bez podania łączy się bez uwierzytelnienia
- mqttPublish(String topic, String payload)
    - topic - temat
    - payload - dane
- mqttDisconnect()
    - odłączenie się od brokera MQTT
