# Config needs to be declared locally in order to assign new values.
# You can only change stuff in your own namespace
# Otherwise you'll try to modify a module, which is not allowed.

import config as default_config
config = default_config
from mqtt_as import MQTTClient, config

# micropython version of asyncio
import uasyncio as asyncio


SERVER = '192.168.178.36'  # Change to suit e.g. 'iot.eclipse.org'

def callback(topic, msg, retained):
    print((topic, msg, retained))

async def conn_han(client):
    await client.subscribe('hello/world', 1)

async def main(client):
    await client.connect()
    n = 0
    while True:
        await asyncio.sleep(5)
        print('publish', n)
        # If WiFi is down the following will pause for the duration.
        await client.publish('hello/world', 'hellooooo'.format(n), qos = 1)
        n += 1

config['subs_cb'] = callback
config['connect_coro'] = conn_han
config['server'] = SERVER
config['port'] = 1883

MQTTClient.DEBUG = True  # Optional: print diagnostic messages
client = MQTTClient(config)
try:
    asyncio.run(main(client))
finally:
    client.close()  # Prevent LmacRxBlk:1 errors