PIP IoT
====

## Setup 
Please follow, this article to install [node-red](https://nodered.org/docs/getting-started/local)

And this [article](https://nodered.org/docs/user-guide/projects/) to install the project( aka git enabled version )



## Using micropython on an ESP 32

1. Download the latest micropython firmware. You'll need a .bin file for the esp32, so search the list for the matching precompiled firmware. It will have a nmae such as **v.1.19.1(2022-06-18).bin**
```
https://micropython.org/download/#esp32
```

2. Use pip to download the esp32 communication tool which will allow you to flash the bootloader
```
pip install esptool

```

3. Erase the entire flash
```
esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
```

4. Program the new firmware:
```
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 write_flash -z 0x1000 <your-firmware-file>
```

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

### links to not loose
[data logger](https://www.youtube.com/watch?v=E2aBIqssQLM)
[google spread sheet data logger](https://flows.nodered.org/flow/a36ccbcfc43c264cda892383fe034fe3)
