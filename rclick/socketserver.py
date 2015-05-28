import socket, threading
import api
from pginterface import Rooftops
import psycopg2

HOST = ''
PORT = 23222

class MyServer(threading.Thread):
    def __init__(self, sa):
        threading.Thread.__init__(self)
        self.socket, self.address = sa

    def run(self):
        print("Client connected!")
        api.getresponse(db, self.socket, self.socket)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(4)

    db = Rooftops(psycopg2.connect(database='test', user='samtheman'))

    while True:
        MyServer(s.accept()).start()
