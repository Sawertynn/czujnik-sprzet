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

#define PIN_TX     7
#define PIN_RX     8

//Login website (https://www.tlink.io/) to register an account ,fill the following information based on your account
#define deviceNo  "DEVICE NO" //Device serial number
#define sensorsId "SENSOR ID" //sensor ID
#define value     "VALUE"

#define HOST      "https://172.205.129.224"
#define NTP_SERVER "pool.ntp.org"
#define TIME_ZONE 1

// #define APN "iot.truphone.com"
#define APN "plus"

SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000         sim7000(&mySerial);
  

void setup(){
  int signalStrength;
  bool ret;
  Serial.begin(9600);
  mySerial.begin(115200);

  // Serial.println("Turn ON SIM7000......");
  // if(sim7000.turnON()){                                    //Turn ON SIM7000
  //   Serial.println("Turn ON !");
  // }


  // Serial.println("Set baud rate......");
  // while(1){
  //   if(sim7000.setBaudRate(9600)){                      //Set SIM7000 baud rate from 115200 to 19200, reduce the baud rate to avoid distortion
  //     Serial.println("Set baud rate:9600");
  //     break;
  //   }else{
  //     Serial.println("Failed to set baud rate");
  //     delay(1100);
  //   }
  // }
  for (int i = 0; i < 3; i++) {
    sim7000.xsend("AT+IPR=9600\r\n");
    delay(100);
  }
  mySerial.end();
  mySerial.begin(9600);
  Serial.println("start write");
return;
  Serial.println("Check SIM card......");
  if(sim7000.checkSIMStatus()){                            //Check SIM card
    Serial.println("SIM card READY");
  }else{
    Serial.println("SIM card ERROR");
    while(1);
  }



  

  Serial.println("Set net mode......");
  while(1){
    if(sim7000.setNetMode(sim7000.eGPRS)){                        //Set net mod GPRS
      Serial.println("Set GPRS mode");
      break;
    }else{
      Serial.println("Fail to set mode");
      delay(1000);
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  signalStrength=sim7000.checkSignalQuality();             //C  heck signal quality from (0-30)
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

  Serial.println("=== SET SSL ===");
  if (sim7000.setSSL(NTP_SERVER, TIME_ZONE))
  {
    Serial.println("Success: set SSL");
  }
  else 
  {
    Serial.println("Fail: set SSL");
  }



  Serial.println("=== HTTP INIT ===");

  if (sim7000.myHttpInit(HOST))
  {
    Serial.println("Success: http init");
  }
  else
  {
    Serial.println("Fail: http init");
  }


  Serial.println("=== HTTP CONN POST ===");

  // String httpbuff;
  // httpbuff += "{\"deviceNo\":\"";                          //{
  // httpbuff += deviceNo;                                    //   "dueviceNo" : "DEVICE NO",
  // httpbuff += "\",\"sensorDatas\":[{\"sensorsId\":";       //      "sensorDatas":[{
  // httpbuff += sensorsId;                                   //          "sensorsId" :  SENSOR ID,
  // httpbuff += ",\"value\":\"";                             //          "value"     : "  VALUE  "
  // httpbuff += value;                                       //       }]
  // httpbuff += "\"}]}";                                     //}

  // ret = sim7000.myPostRequest(HOST, httpbuff);
  ret = sim7000.myPostRequest(HOST, "A=3456789_B=3456789_C=3456789_D=3456789_E=3456789_F=34567890");
  if (ret) {
    Serial.println("Success: request sent");
  }
  else
  {
    Serial.println("Fail: post");
  }

  Serial.println("### end of setup, start typing ###");

  // MICHAŁOWY POST
  // Serial.print("POST to ");
  // Serial.println(POSTURL);
  // String httpbuff;
  // httpbuff += "{\"deviceNo\":\"";                          //{
  // httpbuff += deviceNo;                                    //   "dueviceNo" : "DEVICE NO",
  // httpbuff += "\",\"sensorDatas\":[{\"sensorsId\":";       //      "sensorDatas":[{
  // httpbuff += sensorsId;                                   //          "sensorsId" :  SENSOR ID,
  // httpbuff += ",\"value\":\"";                             //          "value"     : "  VALUE  "
  // httpbuff += value;                                       //       }]
  // httpbuff += "\"}]}";                                     //}
  // while(1){
  //   if(sim7000.httpPost(POSTURL,httpbuff)){              //HTTP POST
  //     Serial.println("Post successed");
  //     break;
  //   }else{
  //     Serial.println("Fail to post");
  //   }
  // }

  // Serial.print("GET from ");
  // Serial.println(GETURL);
  // sim7000.httpGet(GETURL);                                 //HTTP GET
  // Serial.println("Disconnect");
  // sim7000.httpDisconnect();                                //Disconnect
  // Serial.println("Close net work");
  // sim7000.closeNetwork();                                  //Close network
  // Serial.println("Turn off SIM7000");
  // sim7000.turnOFF();                                       //Turn OFF SIM7000
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); // Odczytaj do nowej linii
        mySerial.println(command); // Wyślij do SIM7070G
    }

        if (mySerial.available()) {
        while (mySerial.available()) {
            Serial.write(mySerial.read()); // Przekazuj dane znak po znaku
        }
    }
}
