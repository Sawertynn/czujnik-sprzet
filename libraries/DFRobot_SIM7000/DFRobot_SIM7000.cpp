#include <DFRobot_SIM7000.h>

DFRobot_SIM7000::DFRobot_SIM7000(Stream *s):DFRobot_SIMcore(s)
{
	_s = s;
}

bool DFRobot_SIM7000::setBaudRate(long rate)
{
  int  count = 0;
  while(count <3){
    if( rate  ==  1200){
      if(checkSendCmd("AT+IPR=1200\r\n","OK")){
        _baudrate = 1200;
        break;
      }else{
        count++;
        delay(200);
      }
    }else if(rate == 2400){
      if(checkSendCmd("AT+IPR=2400\r\n","OK")){
        _baudrate = 2400;
        break;
      }else{
        count++;
        delay(200);
      }
    }else if(rate == 4800){
      if(checkSendCmd("AT+IPR=4800\r\n","OK")){
        _baudrate = 4800;
        break;
      }else{
        count++;
        delay(200);
      }
    }else if(rate == 9600){
      if(checkSendCmd("AT+IPR=9600\r\n","OK")){
        _baudrate = 9600;
        break;
      }else{
        count++;
        delay(200);
      }
    }else if(rate == 19200){
      if(checkSendCmd("AT+IPR=19200\r\n","OK")){
        _baudrate = 19200;
        break;
      }else{
        count++;
        delay(200);
      }
    }else if(rate == 38400){
      if(checkSendCmd("AT+IPR=38400\r\n","OK")){
        _baudrate = 38400;
        break;
      }else{
        count++;
        delay(200);
      }
    }else{
      Serial.println("No such rate");
      return false;
    }
  }
  if(count == 3)
    return false;
  return true;
}

bool DFRobot_SIM7000::checkSIMStatus(void)
{
  int count = 0;
  while(count < 3){
    if(checkSendCmd("AT\r\n","OK")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3){
    return false;
  }
  count = 0;
  while(count < 3){
    if(checkSendCmd("AT+CPIN?\r\n","READY")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3)
    return false;
  return true;
}

bool DFRobot_SIM7000::setNetMode(eNet net)
{
  if(net == eNB){
    _mode_t=0;
  	if(checkSendCmd("AT+CNMP=38\r\n","OK")){
      delay(300);
      if(checkSendCmd("AT+CMNB=3\r\n","OK")){ // 2 for NB-only, 3 for both
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
  }else if(net == eGPRS){
    _mode_t=1;
    if(checkSendCmd("AT+CNMP=13\r\n","OK")){
      delay(300);
      if(checkSendCmd("AT+CMNB=1\r\n","OK")){
        return true;
      }else{
        return false;
      }
    }
  }else{
    Serial.println("No such mode!");
  }
  return false;
}

bool DFRobot_SIM7000::attacthService(void)
{
  char gprsBuffer[32];
  char Buffer[200];
  
         sendCmd("AT+CGATT=1\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(2500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  


  
  // cleanBuffer(gprsBuffer,32);
  // sendCmd("AT+CGATT=1\r\n");
  // while(1){
  //   readBuffer(gprsBuffer, 320);
  //   if(NULL != strstr(gprsBuffer, "OK")){
  //     delay(100);
  //     break;
  //   }
  //   if(NULL != strstr(gprsBuffer, "ERROR")){
  //     return false;
  //   }
  // } 
  
  /*
   sendCmd("AT+CNMP=38\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");
   
  */
  //if(checkSendCmd("AT+CIPSHUT\r\n","OK",2000)) //dodane
 /* 
  cleanBuffer(gprsBuffer,32); //by�o 32
  if(_mode_t){
    sendCmd("AT+CSTT=\"plus\"\r\n");//sendCmd("AT+CSTT=\"plus\",\"\",\"\"\r\n");//sendCmd("AT+CSTT=\"plus\"\r\n"); //by�o cmnet
  }else{
    sendCmd("AT+CSTT=\"plus\"\r\n");//sendCmd("AT+CSTT=\"plus\",\"\",\"\"\r\n");//sendCmd("AT+CSTT=\"plus\"\r\n");   //by�o cntb
  } 
  */
  
   // define PDP context
   sendCmd("AT+CGDCONT=1,\"IP\",\"plus\"\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  
  
  
   /*
  while(1){
    readBuffer(gprsBuffer, 32); //by�o 32
    if(NULL != strstr(gprsBuffer, "OK")){
      delay(200);
      break;
    }else if(NULL != strstr(gprsBuffer,"ERROR")){
      return false;
    }
  }
  */
  /*
  sendCmd("AT+CIICR\r\n");
  while(1){
    readBuffer(gprsBuffer, 32, 4000);
    if(NULL != strstr(gprsBuffer, "OK")){
      delay(200);
      break;
    }else if(NULL != strstr(gprsBuffer,"ERROR")){
      return false;
    }
  }
  */

  // PDP configure
   sendCmd("AT+CNCFG=0,1,\"plus\"\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  
   
 
  //if(checkSendCmd("AT+CIFSR\r\n","ERROR",4000)){
  //if(checkSendCmd("AT+CGATT?\r\n","ERROR",4000)){
  //  return false;
  //}

      sendCmd("AT+CGREG=1\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  
  
  // PDP INFO
      sendCmd("AT+CGREG?\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(210);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  

      sendCmd("AT+CGDCONT?\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(210);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  
  
     sendCmd("AT+CGATT?\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(210);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  

   
    sendCmd("AT+SNPDPID=0\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");    

    sendCmd("AT+CNACT=0,1\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");   

  // // PING GOOGLE
  //   sendCmd("AT+SNPING4=\"www.google.com\",5,1,20000\r\n");
  //  cleanBuffer(Buffer,200); //by�o 32
  //  delay(5000);
  //  readBuffer(Buffer, 200); //by�o 32
  //  Serial.println(Buffer);
  //  Serial.println("\r\n");   
  //     delay(5000);
  //  readBuffer(Buffer, 200); //by�o 32
  //  Serial.println(Buffer);
  //  Serial.println("\r\n");  
  //  delay(5000);

  
  //ustalenie czasu 
   sendCmd("AT+CNTPCID=0\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");   
   
   sendCmd("AT+CNTP=\"pool.ntp.org\",-12,0,0\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");   

   sendCmd("AT+CNTP\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n"); 

   //SSL
   sendCmd("AT+CACID=0\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n"); 
   
   sendCmd("AT+CSSLCFG=\"sslversion\",0,3\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n"); 
   
   sendCmd("AT+CASSLCFG=0,\"SSL\",1\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");
   
   sendCmd("AT+CASSLCFG=0,\"CRINDEX\",0\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");
  
     sendCmd("AT+CASSLCFG?\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");  


   // bezpośrednio w http (do komentarza TCP)
    // http conf
    sendCmd("AT+SHCONF=\"URL\",\"https://172.205.129.224\"\r\n");
    cleanBuffer(Buffer,200); //by�o 32
    delay(500);
    readBuffer(Buffer, 200); //by�o 32
    Serial.println("shconf url\r\n");
    Serial.println(Buffer);
    Serial.println("\r\n");

    sendCmd("AT+SHCONF=\"BODYLEN\", 1024\r\n");
    cleanBuffer(Buffer,200); //by�o 32
    delay(500);
    readBuffer(Buffer, 200); //by�o 32
    Serial.println("shconf bodylen");
    Serial.println(Buffer);
    Serial.println("\r\n"); 

    sendCmd("AT+SHCONF=\"HEADERLEN\", 256\r\n");
    cleanBuffer(Buffer,200); //by�o 32
    delay(500);
    readBuffer(Buffer, 200); //by�o 32
    Serial.println("shconf bodylen");
    Serial.println(Buffer);
    Serial.println("\r\n");


    // http info   
  //  sendCmd("AT+SHCONF?\r\n");
  //  cleanBuffer(Buffer,200); //by�o 32
  //  delay(500);
  //  readBuffer(Buffer, 200); //by�o 32
  //  Serial.println("shconf info 2\r\n");
  //  Serial.println(Buffer);
  //  Serial.println("\r\n");


   // http connection (test?)
   sendCmd("AT+SHCONN\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");


  //  set body for POST
   sendCmd("AT+SHBOD=11,2000\r\n");
   delay(200);
   sendString("czujnik-ssl");
   Serial.println("\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");

   
   sendCmd("AT+SHBOD?\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println(Buffer);
   Serial.println("\r\n");

  //  set request type (POST)
   sendCmd("AT+SHREQ=\"/\", 3\r\n");
   cleanBuffer(Buffer,200); //by�o 32
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println("shconf set req to POST\r\n");
   Serial.println(Buffer);
   Serial.println("\r\n");

   
   cleanBuffer(Buffer,200); //by�o 32
   sendCmd("AT+SHREAD=0,1000\r\n");
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println("shconn\r\n");
   Serial.println(Buffer);
   Serial.println("\r\n");

   cleanBuffer(Buffer,200); //by�o 32
   sendCmd("AT+SHCONN\r\n");
   delay(500);
   readBuffer(Buffer, 200); //by�o 32
   Serial.println("shconn\r\n");
   Serial.println(Buffer);
   Serial.println("\r\n");

   while (1) {}

  return true;
}

int DFRobot_SIM7000::checkSignalQuality(void)
{
  char  signalBuffer[26];
  int i = 0,j = 0,k = 0;
  char *signalQuality;
  cleanBuffer(signalBuffer,26);
  sendCmd("AT+CSQ\r\n");
  readBuffer(signalBuffer,26);
  if(NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
    i = *(signalQuality + 6) - 48;
    j = *(signalQuality + 7) - 48;
    k =  (i * 10) + j;
  }else{
    return 0;
  }
  if( k == 99){
    return 0;
  }else{
    return k;
  }
}

bool DFRobot_SIM7000::openNetwork(eProtocol ptl,const char *host, int port)
{
  char num[4];
  char resp[96];
  if(ptl == eTCP){
    sendCmd("AT+CIPSTART=\"TCP\",\"");
    sendCmd(host);
    sendCmd("\",");
    itoa(port, num, 10);
    sendCmd(num);
    sendCmd("\r\n");
  }else if(ptl == eUDP){
    sendCmd("AT+CIPSTART=\"UDP\",\"");
    sendCmd(host);
    sendCmd("\",");
    itoa(port, num, 10);
    sendCmd(num);
    sendCmd("\r\n");
  }else{
    Serial.println("No such mode!");
    return false;
  }
  while(1){
    while(checkReadable()){
      cleanBuffer(resp, 96);
      readBuffer(resp, 96);
      if(NULL != strstr(resp,"CONNECT OK")){
        return true;
      }
      if(NULL != strstr(resp,"ERROR")){//
        return false;
      }
    }
  }
}

bool DFRobot_SIM7000::turnON(void)
{
  pinMode(12,OUTPUT);
  if(checkSendCmd("AT\r\n", "OK", 100)){
    sendCmd("AT+CPOWD=1\r\n");
    delay(4000);
  }
  delay(100);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(7000);
  if(checkSendCmd("AT\r\n", "OK", 100)){
    return true;
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::initPos(void)
{
  if(checkSendCmd("AT+CGNSPWR=1\r\n","OK")){
    delay(50);
    return true;
  }else{
     return false;
  }
}

bool DFRobot_SIM7000::send(char *data)
{
  char num[4];
  char resp[20];
  int len = strlen(data);
  itoa(len, num, 10);
  sendCmd("AT+CIPSEND=");
  sendCmd(num);
  if(checkSendCmd("\r\n",">")){
    sendCmd(data);
    while(1){
      while(checkReadable()){
        readBuffer(resp,20);
        if(NULL != strstr(resp,"OK")){
          return true;
        }
        if(NULL != strstr(resp,"ERROR")){
          return false;
        }
      }
    }
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::send(char *buf, size_t len)
{
  char num[4];
  itoa(len, num, 10);
  sendCmd("AT+CIPSEND=");
  sendCmd(num);
  if(checkSendCmd("\r\n",">")){
    if(checkSendCmd(buf,"OK")){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::mqttConnect(const char* iot_client, const char* iot_username, const char* iot_key)
{
  if(checkSendCmd("AT+CIPSEND\r\n",">")){
    char MQTThead[10]={0x00,0x04,0x4d,0x51,0x54,0x54,0x04,(char)0xC2,0x0b,(char)0xb8};
    char MQTTbuff[50]={0};
    MQTTbuff[0] = 0x10;
    sendBuff(MQTTbuff,1);
    int leng = 10;
    leng += strlen(iot_client)+2;
    leng += strlen(iot_username)+2;
    leng += strlen(iot_key)+2;
    MQTTbuff[0] = leng ;
    sendBuff(MQTTbuff,1);
    sendBuff(MQTThead,10);
    sendBuff(MQTThead,1);
    MQTTbuff[0] = strlen(iot_client);
    sendBuff(MQTTbuff,1);
    sendCmd(iot_client);
    sendBuff(MQTThead,1);
    MQTTbuff[0] = strlen(iot_username);
    sendBuff(MQTTbuff,1);
    sendCmd(iot_username);
    sendBuff(MQTThead,1);
    MQTTbuff[0] = strlen(iot_key);
    sendBuff(MQTTbuff,1);
    sendCmd(iot_key);
    if(checkSendCmd("","CLOSED")){
      return false;
    }else{
      return true;
    }
  }
  return false;
}

bool DFRobot_SIM7000::mqttPublish(const char* iot_topic, String iot_data)
{
  if(checkSendCmd("AT+CIPSEND\r\n",">")){
    DBG("aa");
    char MQTTdata[2]={0x00,0x04};
    char MQTTbuff[50]={0};
    MQTTbuff[0] = 0x32;
    sendBuff(MQTTbuff,1);
    MQTTbuff[0] = strlen(iot_topic)+iot_data.length()+4;
    sendBuff(MQTTbuff,2);
    MQTTbuff[0] = strlen(iot_topic);
    sendBuff(MQTTbuff,1);
    sendCmd(iot_topic);
    sendBuff(MQTTdata,2);
    iot_data.toCharArray(MQTTbuff,iot_data.length());
    sendString(iot_data.c_str());
    if(checkSendCmd("","CLOSED")){
      return false;
    }else{
      return true;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::mqttSubscribe(const char* iot_topic)
{
  if(checkSendCmd("AT+CIPSEND\r\n",">")){
    char MQTTbuff[10]={0};
    MQTTbuff[0] = 0x82;
    MQTTbuff[1] = strlen(iot_topic)+5;
    MQTTbuff[3] = 0x0a;
    MQTTbuff[5] = strlen(iot_topic);
    sendBuff(MQTTbuff,6);
    sendCmd(iot_topic);
    MQTTbuff[0] = 0x01;
    sendBuff(MQTTbuff,1);
    if(checkSendCmd("","CLOSED")){
      return false;
    }else{
      return true;
    }
  }
  return false;
}

bool DFRobot_SIM7000::mqttUnsubscribe(const char* iot_topic)
{
  if(checkSendCmd("AT+CIPSEND\r\n",">")){
    char MQTTbuff[10]={0};
    MQTTbuff[0] = 0xa2;
    MQTTbuff[1] = strlen(iot_topic)+4;
    MQTTbuff[3] = 0x0a;
    MQTTbuff[5] = strlen(iot_topic);
    sendBuff(MQTTbuff,6);
    sendCmd(iot_topic);
    if(checkSendCmd("","CLOSED",1000)){
      return false;
    }else{
      return true;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::mqttRecv(char* iot_topic, char* buf, int maxlen)
{
  char MQTTbuff[maxlen+30];
  char *p; 
  cleanBuffer(MQTTbuff,maxlen+30);
  int i = readBuffer(MQTTbuff,maxlen+30);
  for(int j=0;j<i;j++){
    if(NULL != (p = strstr(MQTTbuff+j,iot_topic))){
      memcpy(buf,p+strlen(iot_topic),maxlen+30);
      return true;
    }
  }
  return false;
}

bool DFRobot_SIM7000::mqttDisconnect(void)
{
  if(checkSendCmd("AT+CIPSEND\r\n",">")){
    const char MQTTdata[2]={(char)0xe0,0x00};
    sendBuff(MQTTdata,2);
    if(checkSendCmd("","CLOSED")){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIM7000::httpInit(eNet net)
{
  if(net == eNB){
    if(!checkSendCmd("AT+SAPBR=3,1,\"APN\",\"www.plusgsm.pl\"\r\n","OK")){ //by�o cntb
      return false;
    }
  }else if(net == eGPRS){
    if(!checkSendCmd("AT+SAPBR=3,1,\"APN\",\"www.plusgsm.pl\"\r\n","OK")){ //by�o cmnet
      return false;
    }
  }
  if(!checkSendCmd("AT+SAPBR=1,1\r\n","OK")){
    return false;
  }
  if(!checkSendCmd("AT+SAPBR=2,1\r\n","OK")){
    return false;
  }
  return true;
}

bool DFRobot_SIM7000::httpConnect(const char *host)
{
  httpDisconnect();
  delay(1000);
  if(!checkSendCmd("AT+HTTPINIT\r\n","OK")){
    return false;
  }
  if(!checkSendCmd("AT+HTTPPARA=\"CID\",\"1\"\r\n","OK")){
    return false;
  }
  sendCmd("AT+HTTPPARA=\"URL\",\"");
  sendCmd(host);
  if(!checkSendCmd("\"\r\n","OK")){
    return false;
  }
  return true;
}

bool DFRobot_SIM7000::httpPost(const char *host , String data)
{
    
  if(!httpConnect(host)){
    return false;
  }
  char resp[40];
  sendCmd("AT+HTTPDATA=");
  itoa(data.length(), resp, 10);
  sendString(resp);
    
  if(!checkSendCmd(",4000\r\n","DOWNLOAD",5)){
    return false;
  }
  delay(500);
  DBG(data.c_str());
  sendString(data.c_str());
  
  while(1){
    readBuffer(resp,20);
    if(NULL != strstr(resp,"OK")){
      break;
    }
    if(NULL != strstr(resp,"ERROR")){
      return false;
    }
  }
  sendCmd("AT+HTTPACTION=1\r\n");
  while(1){
    readBuffer(resp,40);
    if(NULL != strstr(resp,"200")){
      break;
    }
    if(NULL != strstr(resp,"601")){
      return false;
    }
  }
  //delay(11000);
  sendCmd("AT+HTTPREAD\r\n");
	return true;
}

void DFRobot_SIM7000::httpGet(const char *host)
{
  char resp[40];
  if(!httpConnect(host)){
    return;
  }
  sendCmd("AT+HTTPACTION=0\r\n");
  while(1){
    readBuffer(resp,40);
    if(NULL != strstr(resp,"200")){
      break;
    }
    if(NULL != strstr(resp,"601")){
      Serial.println("ERROR !");
      return;
    }
  }
  //delay(11000);
  // if(checkSendCmd("AT+HTTPACTION=0\r\n","601")){
  
  // }
  sendCmd("AT+HTTPREAD\r\n");
  get_String();
}

void DFRobot_SIM7000::httpDisconnect(void)
{
  sendCmd("AT+HTTPTERM\r\n");
}

int DFRobot_SIM7000::recv(char* buf, int maxlen)
{
  char gprsBuffer[maxlen];
  cleanBuffer(gprsBuffer,maxlen);
  int i=readBuffer(gprsBuffer,maxlen,1000);
  Serial.print(i);
  memcpy(buf,gprsBuffer,i);
  return i;
}

bool DFRobot_SIM7000::getPosition(void)
{
  char posBuffer[150];
  char *position;
  cleanBuffer(posBuffer,150);
  sendCmd("AT+CGNSINF\r\n");
  readBuffer(posBuffer,150);
  DBG(posBuffer);
  if(NULL != strstr(posBuffer,"+CGNSINF: 1,1")){
    setCommandCounter(4);
  }else{
    return false;
  }
  if(getCommandCounter() == 4){
    position  = strstr(posBuffer,".000");
    memcpy(_latitude , position+5 , 7);
    memcpy(_longitude, position+15, 7);
    setCommandCounter(5);
    return true;
  }else{
    return false;
  }
}

const char* DFRobot_SIM7000::getLatitude(void)
{
  if(getCommandCounter() >= 5){
    setCommandCounter(6);
    return _latitude;
  }else{
    return "error";
  }
}

const char* DFRobot_SIM7000::getLongitude(void)
{
  if(getCommandCounter() >= 5){
    setCommandCounter(6);
    return _longitude;
  }else{
    return "error";
  }
}

bool DFRobot_SIM7000::closeNetwork(void)
{
  if(checkSendCmd("AT+CIPSHUT\r\n","OK",2000)){
    return true;
  }else{
    return false;
  }
}

int DFRobot_SIM7000::batteryPower(void)
{
  char batteryBuff[26];
  char *pBattery;
  int i=0,j=0,k=0;
  cleanBuffer(batteryBuff,26);
  sendCmd("AT+CBC\r\n");
  readBuffer(batteryBuff,26);
  pBattery = strstr(batteryBuff,"+CBC:");
  i = *(pBattery + 8) - 48;
  j = *(pBattery + 9) - 48;
  k =  (i * 10) + j;
  return  k;
}