# Server Controlled LED_STRIP

## Hardware
- ESP32 - firebeetle
- LED_STRIP - APA102

## description
Assume we have a method we are going to call dashMover
We want to be able to control the dashMover from a web page.
can change the size of the dash, the color, the speed, etc.
by going to the endpoint that would look like this. `/dashMover?size=10&color=purple&speed=10` 

we would get this. 

![LED_STRIP](./LED_STRIP.dashMover.1.gif)

or . `/dashMover?size=50&color=red&speed=10` 
![LED_STRIP](./LED_STRIP.dashMover.2.gif)

Now the trick is we should be able to send multiple commands to the server and have them all add of like so:

![LED_STRIP](./LED_STRIP.dashMover.3.gif)

The mover should also be able to bounce or go in one direction.


## TODO
- [ ] Add static IP
- [ ] develop the struct that will hold the data for the dashMover
- [ ] develop the endpoint that will take the data and update the struct
- [ ] develop the function that will take the data from the struct and move the dash on the LED_STRIP
 