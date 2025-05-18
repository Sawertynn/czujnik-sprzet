/*!
 * @file DFRobot_SIM7000.h
 * @brief Define the basic structure of DFRobot_SIM7000 class
 * @details This is a stable low-power communication module, and it supports multiple frequency bands of LTE- tdd / LTE- fdd / GSM / GPRS / EDGE. The upload and download data flow peak at 375kbps.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM7000
 */
#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include "DFRobot_SIMcore.h"

#include "Arduino.h"
#include "string.h"

#define ON 0
#define OFF 1

constexpr int BASE_DELAY = 100;

#if 0
#define DBG(...)                 \
  {                              \
    Serial.print("[");           \
    Serial.print(__FUNCTION__);  \
    Serial.print("(): ");        \
    Serial.print(__LINE__);      \
    Serial.print(" ] ");         \
    Serial.println(__VA_ARGS__); \
  }
#else
#define DBG(...)
#endif

class DFRobot_SIM7000 : public DFRobot_SIMcore
{
public:
  /**
   * @enum eProtocol
   * @brief Select Network communication protocol
   */
  typedef enum
  {
    eCLOSED = 0,
    eTCP = 1,
    eUDP = 2,
  } eProtocol;

  /**
   * @enum eNet
   * @brief Select data communication mode
   */
  typedef enum
  {
    eGPRS,
    eNB,
  } eNet;

public:
  /**
   * @fn DFRobot_SIM7000
   * @brief DFRobot_SIMcore constructor of abstract class. Construct serial ports.
   * @param s The pointer to abstract class, where you can fill in the pointer to serial object.
   * @return None
   */
  DFRobot_SIM7000(Stream *s);
  ~DFRobot_SIM7000() {};

  // send command to SIM module
  bool atSend(char *command);

  // wait for needle to appear in buffer, or maximally for maxWait seconds
  bool waitFor(char *needle, int maxWait);

  bool changeBaudRate(int new_baud_rate);

  /**
   * @fn recv
   * @brief Receive
   * @param buf Receive data content
   * @param maxlen Receive data length
   * @return Get data length
   */
  int recv(char *buf, int maxlen);

  /**
   * @fn checkSignalQuality
   * @brief Check signal quality
   * @return 0-30:Signal quality
   */
  int checkSignalQuality(void);

  /**
   * @fn batteryPower
   * @brief Battery power
   * @return Battery power
   */
  int batteryPower(void);

  /**
   * @fn setNetMode
   * @brief Set net mode
   * @param net The net mode
   * @n    GPRS: GPRS mode
   * @n    NB:   NB-IOT mode
   * @return bool type, indicating the status of setting
   * @retval ture Success
   * @retval false Failed
   */
  bool setNetMode(eNet net);

  /**
   * @fn attacthService
   * @brief Open the connection
   * @return bool type, indicating the status of opening the connection
   * @retval true Success
   * @retval false Failed
   */
  bool attacthService(char *APN);

  /**
   * @fn setBaudRate
   * @brief Set baud rate to avoid garbled
   * @param rate Baud rate value
   * @n    Possible values:1200 2400 4800 9600 19200 38400
   * @note SIM7000 default baud rate is 115200, reduce the baud rate to avoid distortion
   * @return bool type, indicating the status of setting
   * @retval true Success
   * @retval false Failed
   */
  bool setBaudRate(long rate);

  /**
   * @fn checkSIMStatus
   * @brief Check SIM card
   * @return bool type, indicating the status of checking SIM card
   * @retval true Success
   * @retval false Failed
   */
  bool checkSIMStatus(void);

  /**
   * @fn openNetwork
   * @brief Start up connection
   * @param ptl  Choose connection protocol
   * @n    TCP  Choose TCP
   * @n    UDP  Choose UDP
   * @param host Host domain name
   * @param port  Contented port
   * @return bool type, indicating the status of opening Network
   * @retval true Success
   * @retval false Failed
   */
  bool openNetwork(eProtocol ptl, const char *host, int port);

  /**
   * @fn closeNetwork
   * @brief End the connection
   * @return bool type, indicating the status of closing Network
   * @retval true Success
   * @retval false Failed
   */
  bool closeNetwork(void);

  /**
   * @fn turnON
   * @brief Turn ON SIM7000
   * @return bool type, indicating the status of turning on
   * @retval true Success
   * @retval false Failed
   */
  bool turnON(void);

  /**
   * @fn initPos
   * @brief Init SIM7000 positioning module
   * @return bool type, indicating the initialization status
   * @retval true Success
   * @retval false Failed
   */
  bool initPos(void);
  
 /**
  * @fn mqttInit
  * @brief Initialize MQTT with client id, turn ssl on or off
  * @param String client_id
  * @param bool use_ssl, true by default
  * @return  bool type, indicates success
  */
  bool mqttInit(String client_id, bool use_ssl = true);

 /**
  * @fn mqttConnect
  * @brief Connect with MQTT broker
  * @param String broker_addr - must start with "tcp://" and end with port
  * @param String login
  * @param String password - if not provied, will not use authorization
  * @return bool type, indicates success
  */
  bool mqttConnect(String broker_addr, String login = "", String password = "");
  
  bool mqttPublish(String topic, String payload);
  
  bool mqttDisconnect();

  /**
   * @fn httpInit
   * @brief Initialize HTTP service
   * @param net The net mode
   * @n    eGPRS: GPRS mode
   * @n    eNB:   NB-IOT mode
   * @return bool type, indicating initialization status
   * @retval true Success
   * @retval false Failed
   */
  bool httpInit(eNet net);

  /**
   * @fn httpConnect
   * @brief Connect to server
   * @param host Server IP
   * @return bool type, indicating connection status
   * @retval true Success
   * @retval false Failed
   */
  bool httpConnect(const char *host);

  /**
   * @fn httpPost
   * @brief HTTP POST
   * @param host URL
   * @param data POST data
   * @param readLen size of response data to read, by default -1 (do not read response)
   * @return bool type, indicating request status
   * @retval true Success
   * @retval false Failed
   */
  bool httpPost(const char *host, String data, int readLen = -1);

  /**
   * @fn httpGet
   * @brief HTTP GET This function print the get data
   * @param host URL
   */
  void httpGet(const char *host);

  /**
   * @fn httpDisconnect
   * @brief Disconnect from server and cancel initialization
   */
  void httpDisconnect(void);

  /**
   * @fn send
   * @brief Send data with specify the length
   * @param buf The buffer for data to be send
   * @param len The length of data to be send
   * @return bool type, indicating status of sending
   * @retval true Success
   * @retval false Failed
   */
  bool send(char *buf, size_t len);

  /**
   * @fn send
   * @brief Send data
   * @param data The data to send
   * @return bool type, indicating status of sending
   * @retval true Success
   * @retval false Failed
   */
  bool send(char *data);

  /**
   * @fn getPosition
   * @brief Get the current position
   * @return bool type, indicating the status of getting position
   * @retval true Success
   * @retval false Failed
   */
  bool getPosition(void);

  /**
   * @fn getLatitude
   * @brief Get latitude
   * @return Latitude value
   */
  const char *getLatitude(void);

  /**
   * @fn getLongitude
   * @brief Get longitude
   * @return Longitude value
   */
  const char *getLongitude(void);

  /**
   * @fn setupSSL
   * @brief Configure and set up SSL
   * @param ntp_server NTP server's URL
   * @param time_zone_full_hours time zone, in full hours offset from UTC
   * @return bool type, indicating status
   * @retval true Success
   * @retval false Failed
   */
  bool setupSSL(char *ntp_server, int time_zone);

  bool setupSMS(char *serviceCentral);

  bool sendSMS(char *target, String data);

  bool mySendCmd(char *cmd, char *check_str = "OK", int read_count = 10, int try_count = 3, int delay_ms = BASE_DELAY);

private:
  char _latitude[8];
  char _longitude[8];
  int _mode_t = 0;
  long _baudrate = 19200;
  int _mqtt_ssl = 0;
  Stream *_s;
};

#endif
