
void handleRoot() {

  server.send(200, "text/plain", "Led Server is up and running: " + WiFi.localIP().toString() + " <br> end poits are: <br> /dash?size=<int>&wrap=<bool>&bounce=<bool>&life=<int>&color=<int>,<int>,<int> <br> / ipdateIP?ip=192.168.86.xx");
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
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  int len_ = 10;
  bool wrap_ = true;
  bool bounce_ = false;
  int direction_ = 1;
  float domainStart_ = 0.0;
  float domainEnd_ = 1.0;
  float life_ = 7.0;
  CRGB color_ = CRGB(255, 132, 60);
  int delay_ms_ = 100;
  if (server.hasArg("color")) {
    //  read the new IP address from the request body
    String rgbBody = server.arg("color");
    // create a char array to hold the string
    char rgbCharArray[rgbBody.length() + 1];
    // copy the string into the char array
    rgbBody.toCharArray(rgbCharArray, rgbBody.length() + 1);
    // split the string into tokens using '.' as the delimiter
    char* token = strtok(rgbCharArray, ",");

    // convert each token into an integer
    int rgb[3];
    int i = 0;
    while (token != NULL && i < 3) {
      rgb[i] = atoi(token);
      token = strtok(NULL, ",");
      i++;
    }
    // create a new IPAddress object using the integers
    color_ = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  if (server.hasArg("size")) {
    // Get the value of the parameters
    len_ = server.arg("size").toInt();
  }
  if (server.hasArg("wrap")) {
    // Get the value of the parameters
    wrap_ = server.arg("wrap").toInt();
  }
  if (server.hasArg("bounce")) {
    // Get the value of the parameters
    bounce_ = server.arg("bounce").toInt();
  }
  if (server.hasArg("delay_ms")) {
    delay_ms_ = server.arg("delay_ms").toInt();
  }
  if (server.hasArg("direction")) {
    // Get the value of the parameters
    direction_ = server.arg("direction").toInt();
  }
  if (server.hasArg("domainStart")) {
    // Get the value of the parameters
    domainStart_ = server.arg("domainStart").toFloat();
  }
  if (server.hasArg("domainEnd")) {
    // Get the value of the parameters
    domainEnd_ = server.arg("domainEnd").toFloat();
  }
  if (server.hasArg("life")) {
    // Get the value of the parameters
    life_ = server.arg("life").toFloat();
  }
  Dash dash(NUM_LEDS);
  dash.len = len_;

  dash.life = life_;
  dash.color = color_;
  dash.delay_ms = delay_ms_;
  dash.wrap = wrap_;
  dash.bounce = bounce_;
  // techincally not implemented yet but will leave for future use
  dash.direction = direction_;
  dash.domainStart = domainStart_;
  dash.domainEnd = domainEnd_;


  // Push the Dash object to the end of the vector
  dashes.push_back(dash);
  server.send(200, "text/plain", message);
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
  } else {
    stripID = stripID;
  }
  const char* hostname = ("ledstrip" + String(stripID)).c_str();
  if (MDNS.begin(hostname)) {
    Serial.println("MDNS responder started");
  }
}

void restartHandler() {
  ESP.restart();
}

void setupHTTPHandlers() {
  server.on("/", handleRoot);
  server.on("/dash", shapeHandler);
  server.on("/updateIP", storeIP);
  server.on("/updateID", storeID);
  server.on("/restart", restartHandler);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
}

/// I still fucking hate this language
