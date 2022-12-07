/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <Servo.h>

static const int servoPin = 15;

Servo servo1;

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "ServoTest";
const char *password = "12345678";

WiFiServer server(80);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
   servo1.attach(servoPin);
}
int minPos = 0;
int maxPos = 180;
int delayTime = 20;

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("set range to  <a href=\"/r150\">150</a> <br><br>");
            client.print("min <a href=\"/r120\">120 </a> <br><br>");
            client.print("min <a href=\"/r90\">90</a> <br><br>");
            client.print("min <a href=\"/r60\">60</a> <br><br>");
            client.print("min <a href=\"/r30\">30</a> <br><br>");
            client.print("delay <a href=\"/d20\">20</a> <br><br>");
            client.print("delay <a href=\"/d10\">10</a> <br><br>");
            client.print("delay <a href=\"/d5\">50</a> <br><br>");
            client.print("delay <a href=\"/d0\">0</a> <br><br>");
           

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /r150")) {
          minPos = 15;
          maxPos = 165;
        }
        if (currentLine.endsWith("GET /r120")) {
          minPos = 30;
          maxPos = 150;
        }
        if (currentLine.endsWith("GET /r90")) {
          minPos = 45;
          maxPos = 135;
        }
        if (currentLine.endsWith("GET /r60")) {
          minPos = 60;
          maxPos = 120;
        }
       if (currentLine.endsWith("GET /r30")) {
          client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("set range to  <a href=\"/r150\">150</a> <br><br>");
            // The HTTP response ends with another blank line:
            client.println();
          minPos = 75;
          maxPos = 105;
        }
         if (currentLine.endsWith("GET /d20")) {
          delayTime = 20;
        }
          if (currentLine.endsWith("GET /d10")) {
          delayTime = 10;
        }
          if (currentLine.endsWith("GET /d5")) {
          delayTime = 5;
        }
          if (currentLine.endsWith("GET /d0")) {
          delayTime = 0;
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
      for(int posDegrees = minPos; posDegrees <= maxPos; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(delayTime);
    }

    for(int posDegrees = maxPos; posDegrees >= minPos; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(delayTime);
    }
}
