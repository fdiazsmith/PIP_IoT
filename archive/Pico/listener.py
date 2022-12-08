import network
import socket
import time
import json

from machine import Pin

led = Pin(15, Pin.OUT)

ssid = 'Tellart'
password = '1SimsAve'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

max_wait = 10
while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print('waiting for connection...')
    time.sleep(1)

if wlan.status() != 3:
    raise RuntimeError('network connection failed')
else:
    print('connected')
    status = wlan.ifconfig()
    print( 'ip = ' + status[0] )

addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]

s = socket.socket()
s.bind(addr)
s.listen(1)

print('listening on', addr)

# Listen for connections
while True:
    try:
        cl, addr = s.accept()
        print('client connected from', addr)
        request = cl.recv(1024)
        print(request)
        #json.loads(request.decode('UTF-8'))

        decoded = request.decode('UTF-8')
        result = decoded.split("\r\n\r\n")[1]
        led_command = json.loads(result)['led']
        print( 'led request = ' + led_command)
        

        if led_command == "on":
            print("led is turning on")
            led.value(1)
            payload = "on"
            
        if led_command == "off":
            print("led is turning off")
            led.value(0)
            payload = "off"
    
        encoded = json.dumps({"led": payload})

        cl.send('HTTP/1.0 200 OK\r\nContent-type: application/json\r\n\r\n')
        cl.send(encoded.encode())
        cl.close()

    except OSError as e:
        cl.close()
        print('connection closed')
