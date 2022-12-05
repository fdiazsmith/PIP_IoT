# TODO:
- [ ] get the server to start automatically on boot. I have the `pipSpeaker.sh` script that starts the server but I need to figure out how to get it to run on boot.
- [ ] clean the server a bit, change the endpoint to `/play` and add a `/connect` endpoint and make them work with arguments. so we can play multiple tracks. e.g. `/play?track=1` and `/connect?speaker=D8:37:3B:85:B1:42`
- [ ] add static IP address to the PI
- [ ] if we want to get fancy split the server into separte files and import them into the main file. 


# From scratch
but hopefully we will not do this twice, instead we just clone the pi we already have.


# Rasberry Pi
## Setup
Use the Raspberry Pi Imager to install the latest version of Raspberry Pi OS on the SD card. 
[here is  the link](https://www.raspberrypi.org/software/)

for user name I used  `pip` and password `pip123`

for the network name I used `pip` as well and we can increment the number for each one: `pip1`, `pip2`, `pip3`, etc.

## Bluetooth audio set up 
### bluetooth connection vis terminal : 
[This article is pretty complete](https://wiretuts.com/connecting-bluetooth-audio-device-to-raspberry-pi) though we should not need to do it anymore because we can clone the pi that is already set up.

## download a sample audio file:
```bash
# use curl to download this wav file: https://www.kozco.com/tech/piano2.wav
curl https://www.kozco.com/tech/piano2.wav -o piano2.wav

```


