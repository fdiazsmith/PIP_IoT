
void handleRoot() {

    server.send(200, "text/plain", "hello from esp8266!");

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
// TODO:
// get static IP working

// setup the server
void setupServer(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

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

    if (MDNS.begin("esp32")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.on("/shape", shapeHandler);

    server.on("/inline", []() {
            server.send(200, "text/plain", "this works as well");
            });

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

/// I still fucking hate this language
