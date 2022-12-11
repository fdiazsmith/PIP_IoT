
void handleRoot() {

  server.send(200, "text/plain", "Led Server is up and running: " + WiFi.localIP().toString());

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}
void shapeHandler() {
    String message = "Shape\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    // check if the characters in server.argName(i) == "id" and server.arg(i) == "1"
    /*
    cleaner way to check if the URL contains parameters still need be tested and implelmented
    // Check if the URL contains parameters
    if (server.hasArg("param1") && server.hasArg("param2")) {
      // Get the value of the parameters
      String param1 = server.arg("param1");
      String param2 = server.arg("param2");
      Serial.print("param1 = ");
      Serial.println(param1);
      Serial.print("param2 = ");
      Serial.println(param2);
    }
    */
        for (uint8_t i = 0; i < server.args(); i++) {
            message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
            if(server.argName(i) == "id"){
                String shapeID = server.arg(i);
                //switch on the id
                int si = shapeID.toInt();
                switch(si){
                    case 1:
                        // do something
                        allDashes[0]->color = CRGB::Green;
                        Serial.println("Shape: S");
                        // triggerShape();
                        break;
                    case 2:
                        // b.color = CRGB::Orange;
                        allDashes[1]->pos = 0;
                        allDashes[1]->delay_ms = 50;
                        break;
                    finally:
                        break;
                        
            }
        }

    server.send(200, "text/plain", message);

    }
}

void storeIP() {
// read the new IP address from the request body
    String ipBody = server.arg("ip");
    // create a char array to hold the string
    char ipCharArray[ipBody.length() + 1];

    // copy the string into the char array
    ipBody.toCharArray(ipCharArray, ipBody.length() + 1);

    // split the string into tokens using '.' as the delimiter
    char* token = strtok(ipCharArray, ".");

    // convert each token into an integer
    int ipInt[4];
    int i = 0;
    while (token != NULL && i < 4) {
      ipInt[i] = atoi(token);
      token = strtok(NULL, ".");
      i++;
    }
    // create a new IPAddress object using the integers
    IPAddress newIP = IPAddress(ipInt[0], ipInt[1], ipInt[2], ipInt[3]);


    Serial.print("new to be stored IP ");
    Serial.print(ipInt[0]);
    Serial.print(".");
    Serial.print(ipInt[1]);
    Serial.print(".");
    Serial.print(ipInt[2]);
    Serial.print(".");
    Serial.println(ipInt[3]);

    EEPROM.begin(EEPROM_SIZE);
    // store the new IP address in the EEPROM memory
    EEPROM.write(eepromStartAddress, newIP[0]);
    EEPROM.write(eepromStartAddress + 1, newIP[1]);
    EEPROM.write(eepromStartAddress + 2, newIP[2]);
    EEPROM.write(eepromStartAddress + 3, newIP[3]);
    EEPROM.commit();

    // send a response to the client
    server.send(200, "text/plain", "IP address updated successfully");
}
void storeID() {
// read the new IP address from the request body
    String idBody = server.arg("id");
    // create a char array to hold the string
    char idCharArray[idBody.length() + 1];

    // copy the string into the char array
    idBody.toCharArray(idCharArray, idBody.length() + 1);

    // convert the string into an integer
    int idByte = atoi(idCharArray);
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.write(eepromStartAddress + 4, idByte);
    EEPROM.commit();

    // send a response to the client
    server.send(200, "text/plain", "IP address updated successfully");
}
// create a function to parse URL parameters

// // TODO: add all the options to 
// void triggerShape(int id, CRGB color, int len, int delay_ms, bool wrap){
//   // interpret this as pseudo code to be implemented
//   /*
//   allShapes[id].color = color;
//   allShapes[id].len = len;
//   allShapes[id].delay_ms = delay_ms;
//   allShapes[id].wrap = wrap;
//   allShapes[id].pos = 0;
//   */
  
// }

void setupServer() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // initialize the EEPROM memory
  EEPROM.begin(EEPROM_SIZE);
  // read the stored IP address from the EEPROM memory
  byte ip1 = EEPROM.read(eepromStartAddress);
  byte ip2 = EEPROM.read(eepromStartAddress + 1);
  byte ip3 = EEPROM.read(eepromStartAddress + 2);
  byte ip4 = EEPROM.read(eepromStartAddress + 3);
  
  // if there is no stored IP address, use the default IP address
  if (ip1 == 255 && ip2 == 255 && ip3 == 255 && ip4 == 255) {
    WiFi.config(defaultIP, gateway, subnet);
  }
  // otherwise, use the stored IP address
  else {
    IPAddress storedIP(ip1, ip2, ip3, ip4);
    WiFi.config(storedIP, gateway, subnet);
  }
  Serial.print("Stored IP ");
  Serial.print(ip1);
  Serial.print(".");
  Serial.print(ip2);
  Serial.print(".");
  Serial.print(ip3);
  Serial.print(".");
  Serial.println(ip4);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  setupMDNS();
  setupHTTPHandlers();
  server.begin();
  Serial.println("HTTP server started");
}

void setupMDNS() {
  // initialize the EEPROM memory
  EEPROM.begin(EEPROM_SIZE);
  byte stripID = EEPROM.read(eepromStartAddress + 5);
  if (stripID == 255) {
    stripID = 0;
  }
  else{
    stripID = stripID;
  }
  const char* hostname = ("ledstrip" + String(stripID)).c_str();
  if (MDNS.begin(hostname)) {
    Serial.println("MDNS responder started");
  }
}

void setupHTTPHandlers() {
  server.on("/", handleRoot);
  server.on("/shape", shapeHandler);
  server.on("/updateIP", storeIP);
  server.on("/updateID", storeID);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
}

/// I still fucking hate this language
