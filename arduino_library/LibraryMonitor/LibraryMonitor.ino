#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "NETGEAR97"           // cannot be longer than 32 characters!
#define WLAN_PASS       "wittylotus627"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "10.131.8.115:8000" //"www.adafruit.com"
#define WEBPAGE      "/sendor"//"/testwifi/index.html"
//------------------------------------------------------------------
// variables for the the sensor program
// Constants
const int analogInPinIR = A0; // Analog input pin that the sensor is attached to --> can use A2 through A5 on UNO
const int analogInPinIR2 = A5;
int THRESHOLD = 60; // any value below THRESHOLD someone stands in front of the sensor
const int IGNORETHRESHOLD = 200; // ignore readings from sensor that doesn't change at least this amount
const int TIMEOUT = 2000; // reset sensor memories after TIMEOUT
int INTERVAL = 100; // delay INTERVAL in miliseconds
// sensor memory values
int IRSensorVal = 0;
int IRSensorVal2 = 0;
int previous = 0;
int previous2 = 0;
int time1 = 0;
int time2 = 0;
boolean passed1 = false;
boolean passed2 = false;
// oprtional. Counter's used in a loop to stop collecting values after a certain amount of time

/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;
Adafruit_CC3000_Client www;

void setup(void)
{
  wifi_connect();
  ip = cc3000.IP2U32(10,132,4,108); //IMPORTANT! CHANGE TO THE IP ADDRESS YOU WANNA CONNECT TO
  www = cc3000.connectTCP(ip, 8000);
  if (www.connected()) {
    Serial.println(F("Connection succedded. Sending data now."));  
  } else {
    Serial.println(F("Connection failed"));    
    return;
  }
  connectHomePage();
}

void loop(void)
{
    IRSensorVal = analogRead(analogInPinIR);
    IRSensorVal2 = analogRead(analogInPinIR2);
    Serial.print("sensor 1: ");
    Serial.println(IRSensorVal);
    Serial.print("sensor 2: ");
    Serial.println(IRSensorVal2);

    if (IRSensorVal > THRESHOLD && (IRSensorVal - IGNORETHRESHOLD > previous)) {
      time1 = millis();
      if (passed2 && !passed1 && time1 - time2 < 2000) {
        Serial.println("Coming towards sensor1");
        sendWalkOutData();
        passed2 = false;
        passed1 = false;
      } else {
        passed1 = true;
        passed2 = false;
      }
      
    } else if (IRSensorVal2 > THRESHOLD && (IRSensorVal2 - IGNORETHRESHOLD > previous2)) {
      time2 = millis();
      if (passed1 && !passed2 && time2 - time1 < 2000) {
        Serial.println("Coming towards sensor2");
        sendWalkInData();
        passed2 = false;
        passed1 = false;
      } else {
        passed2 = true;
        passed1 = false;
      }  
    }
    
    delay(INTERVAL);
    previous = IRSensorVal;
    previous2 = IRSensorVal2;
}

void connectHomePage() {
  cc3000.connectTCP(ip, 8000);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint("/");
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint("10.132.4.108:8000"); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
    Serial.println(F("Connected to home page!")); 
  } else {
    Serial.println(F("Some probalem with the connection to home page!"));    
    return;
  }
}

void sendWalkInData() {
  cc3000.connectTCP(ip, 8000);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint("/sensor?data=in");
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint("10.132.4.108:8000"); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
    Serial.println(F("Data sent!"));   
  } else {
    Serial.println(F("Some probalem with the connection!"));    
    return;
  }
}

void sendWalkOutData() {
  cc3000.connectTCP(ip, 8000);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint("/sensor?data=out");
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); www.fastrprint("10.132.4.108:8000"); www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
    Serial.println(F("Data sent!"));   
  } else {
    Serial.println(F("Some probalem with the connection!"));    
    return;
  }
//      /* Read data until either the connection is closed, or the idle timeout is reached. */ 
//  unsigned long lastRead = millis();
//  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
//    while (www.available()) {
//      char c = www.read();
//      Serial.print(c);
//      lastRead = millis();
//    }
//  }
//  www.close();
}

void wifi_connect() {
    Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }
}

/**************************************************************************/
/*!
    @brief  Begins an SSID scan and prints out all the visible networks
*/
/**************************************************************************/

void listSSIDResults(void)
{
  uint32_t index;
  uint8_t valid, rssi, sec;
  char ssidname[33]; 

  if (!cc3000.startSSIDscan(&index)) {
    Serial.println(F("SSID scan failed!"));
    return;
  }

  Serial.print(F("Networks found: ")); Serial.println(index);
  Serial.println(F("================================================"));

  while (index) {
    index--;

    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
    
    Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
    Serial.println();
    Serial.print(F("RSSI         : "));
    Serial.println(rssi);
    Serial.print(F("Security Mode: "));
    Serial.println(sec);
    Serial.println();
  }
  Serial.println(F("================================================"));

  cc3000.stopSSIDscan();
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}


