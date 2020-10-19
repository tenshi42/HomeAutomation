import socket
import threading
from Constants import ConnectionType, BUFFER_SIZE, PORT

class ClientThread(threading.Thread):
    def __init__(self, receiveCallback):
        threading.Thread.__init__(self)
        self.client = None
        self.receiveCallback = receiveCallback
        self._run = True

    def run(self):
        while self._run:
            data = self.client.recv(BUFFER_SIZE)
            self.receiveCallback(data)

    def stop(self):
        self._run = False
        self.client.socket.close()


class ServerListener(threading.Thread):
    def __init__(self, server, connectionCallBack, receiveCallback):
        threading.Thread.__init__(self)
        self.connectionCallback = connectionCallBack
        self.receiveCallback = receiveCallback
        self.server = server
        self._run = True

    def run(self):
        while self._run:
            self.server.listen(10)
            (clientsocket, (ip, port)) = self.server.accept()
            clientThread = ClientThread(self.receiveCallback)
            client = self.connectionCallback(ConnectionType.TCP, clientsocket, ip, port, clientThread)
            clientThread.client = client
            clientThread.start()

    def stop(self):
        self._run = False
        self.server.close()


class TcpServer:
    def __init__(self):
        self.server = None
        self.listeningThread = None

    def InitServer(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(("", PORT))

    def StartListening(self, connectionCallBack, receiveCallback):
        self.listeningThread = ServerListener(self.server, connectionCallBack, receiveCallback)

    def StopListening(self):
        self.listeningThread.stop()

