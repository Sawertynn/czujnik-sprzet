/*!
 * @file   DFRobot_SIM7000_HTTP.ino
 * @n      SIM7000 needs 7-12V DC power supply
 * @brief  This example will verify HTTP connection over a HTTP request
 * @n      With initialization completed, we connect to server POST data and GET data
 * @n      Thus we finished the HTTP POST and GET verification
 * @n      If you use NB-IOT please confirm that the IOT is in the whitelist of your NB card
 * @n      If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
 * 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [TangJie](jie.tang@dfrobot.com)
 * @version     V1.0.1
 * @date        2021-09-16
 * @url         https://github.com/DFRobot/DFRobot_SIM7000
 */

#include <DFRobot_SIM7000.h>

// #### SETMODE ####

#define MODE_SSL  true
#define MODE_HTTP true
#define MODE_MQTT false
#define MODE_SMS  false

#define PIN_TX     7
#define PIN_RX     8

//Login website (https://www.tlink.io/) to register an account ,fill the following information based on your account
#define deviceNo  "DEVICE NO" //Device serial number
#define sensorsId "SENSOR ID" //sensor ID
#define value     "VALUE"

// #define HOST "https://httpbin.org/post"
#define HOST "https://srv84554.seohost.com.pl"
// #define HOST "https://eo87jvr1yccmec5.m.pipedream.net"

#define APN "plus"
#define NTP_SERVER "pool.ntp.org"
#define TIME_ZONE 2 // CEST+2:00

#define MQTT_URL "1901da8e0be84355ae4f4294569f45e3.s1.eu.hivemq.cloud"
#define MQTT_TLS_URL "1901da8e0be84355ae4f4294569f45e3.s1.eu.hivemq.cloud:8883"
#define MQTT_PORT 8883
#define MQTT_LOGIN "hivemq.remote"
#define MQTT_PASS "Password123"

#define MQTT_FULL "tcp://9877acae137043d6ba8adea50ce969a9.s1.eu.hivemq.cloud:8883"


#define SMS_CENTRAL_SERVICE "+48601100601" // for plus
#define SMS_TARGET "provide_number"

SoftwareSerial     simSerial(PIN_RX,PIN_TX);
DFRobot_SIM7000         sim7000(&simSerial);
  

void setup(){
  int signalStrength;
  bool ret;

  Serial.begin(9600);
  simSerial.begin(115200);

  Serial.println("Turn ON SIM7000......");
  if(sim7000.turnON()){                                    //Turn ON SIM7000
    Serial.println("Turn ON !");
  }

  // switch baud raute from high to low
  sim7000.changeBaudRate(9600);

  Serial.println("Check SIM card......");
  for (int i = 0; i < 3; i++) {
    if (sim7000.checkSIMStatus()){
      Serial.println("SIM card READY");
      break;
    }else{
      Serial.println("SIM card ERROR");
    }
    if (i == 2) {
      Serial.println("SIM card 3 tries ERROR");
      return;
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  signalStrength=sim7000.checkSignalQuality();             //Check signal quality from (0-30)
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);


  Serial.println("Attaching service......");
  if (sim7000.attacthService(APN))
  {
    Serial.println("Service attached");
  }
  else 
  {
    Serial.println("Fail: Attaching service");
  }
  
  if (MODE_SMS) {
    Serial.println("=== SMS ===");
    sim7000.setupSMS(SMS_CENTRAL_SERVICE);

    String text = "sms from arduino";
    sim7000.sendSMS(SMS_TARGET, text);
  } // SMS

  if (MODE_SSL) {
    Serial.println("=== SET SSL ===");
    if (sim7000.setupSSL(NTP_SERVER, TIME_ZONE))
    {
      Serial.println("Success: set SSL");
    }
    else 
    {
      Serial.println("Fail: set SSL");
    }
  } // SSL

  if (MODE_MQTT)
  {
    Serial.println("=== MQTT ===");
   
  }

  if (MODE_HTTP)
  {
    Serial.println("=== http connect ====");
    if (sim7000.httpConnect(HOST)) {
      Serial.println("Connected to host");
    }
    else
    {
      Serial.println("Failed to connect");
      return;
    }

    Serial.println("=== http POST request ===");
    
    // String postData = "{"name": "czujnik", "message":"wiadomosc"}";
    String postData = "{\"name\": \"czujnik\", \"message\":\"wiadomosc\"}";
    if (sim7000.httpPost(HOST, postData, 1000)) {
      Serial.println("message sent!");
    }
    else
    {
      Serial.println("failed to send");
    }
    sim7000.httpDisconnect();

  } // HTTPS


  Serial.println(">> Interactive mode <<");
}

void loop() {
  if (Serial.available()) {
      String command = Serial.readStringUntil('\n');
      simSerial.println(command);
  }

  if (simSerial.available()) {
    while (simSerial.available()) {
        Serial.write(simSerial.read());
    }
  }
}
