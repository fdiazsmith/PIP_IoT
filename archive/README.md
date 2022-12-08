# Archive

## Contents

- MQTT_test: script for publishing an subscribing to a mqtt topic
- listener.py: listener for http request
- html-webserver.py: webserver in micropython
- node-red: example flows for http calls to esp32

## Installing MQTT client on the Pico W
1. Upload the library mgtt_as to the pico with thonny.
This should be the config.py and the mqtt_as.py files. Place them under the /lib directory

2. Configure the wifi access credentials in config.py
3. Configure the ip of the broker in the 'SERVER' variable
4. Upload/run the main.py file to start the client

## Running the broker on Ubuntu (without security)
1. run ```sudo apt install mosquitto mosquitto-clients```
2. create a default config file in 
```/etc/mosquitto/conf.d/default.conf```

(currently not picked up automatically)

3. add the setting: 
```
listener 1883
allow_anonymous true
```
Run the broker with the following command:
```
mosquitto -c /etc/mosquitto/conf.d/default.conf
```

Broker is now running with anonymous access for everyone

Authentication should ideally be configured after testing
