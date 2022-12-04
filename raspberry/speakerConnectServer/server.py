import socket
import threading
import pygame

HOST = 'localhost'
PORT = 8000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print(f'Listening on {HOST}:{PORT}...')

def play_sound():
  pygame.mixer.init()
  pygame.mixer.music.load('sound.wav')
  pygame.mixer.music.play()

while True:
  conn, addr = server_socket.accept()
  with conn:
    print(f'Connected by {addr}')

    data = conn.recv(1024)
    if not data:
      break

    request_method = data.decode().split(' ')[0]
    if request_method == 'GET':
      if data.decode().split(' ')[1] == '/':
        # Home page
        response = b''
        response += b'HTTP/1.1 200 OK\n'
        response += b'Content-Type: text/html\n'
        response += b'\n'
        response += b'<html>\n'
        response += b'<body>\n'
        response += b'<h1>Welcome to the Home Page!</h1>\n'
        response += b'<p>Choose an endpoint:</p>\n'
        response += b'<ul>\n'
        response += b'<li><a href="/endpoint1">Endpoint 1</a></li>\n'
        response += b'<li><a href="/endpoint2">Endpoint 2</a></li>\n'
        response += b'</ul>\n'
        response += b'</body>\n'
        response += b'</html>\n'
        conn.sendall(response)
      elif data.decode().split(' ')[1] == '/endpoint1':
        # Endpoint 1
        output = subprocess.check_output(['ls', '-l']).decode()
        response = b''
        response += b'HTTP/1.1 200 OK\n'
        response += b'Content-Type: text/plain\n'
        response += b'\n'
        response += output.encode()
        conn.sendall(response)
      elif data.decode().split(' ')[1] == '/endpoint2':
        # Endpoint 2
        thread = threading.Thread(target=play_sound)
        thread.start()
        response = b''
        response += b'HTTP/1.1 200 OK\n'
        response += b'Content-Type: text/plain\n'
        response += b'\n'
        response += b'This is Endpoint 2\n'
        conn.sendall(response)
      else:
        # Not found
        response = b''
        response += b'HTTP/1.1 404 Not Found\n'
        response += b'Content-Type: text/plain\n'
        response += b'\n'
        response += b'404 Not Found\n'
        conn.sendall(response)