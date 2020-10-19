from Constants import ConnectionType
from Client import Client
from TcpServer import TcpServer


class NetCom:
    def __init__(self, receiveCallback):
        self.tcpServer = None
        self.wsServer = None

        self.clients = []
        self.clientUID = 0

        self.receiveCallback = receiveCallback

    def StartTcpServer(self):
        self.tcpServer = TcpServer()
        self.tcpServer.StartListening(self.newConnection, self.Receive)
        print("ready to socket !")

    def StopTcpServer(self):
        pass

    def SendToClient(self, client, msgType, data):
        if client.connectionType == ConnectionType.TCP:
            client.socket.send(msgType + ":" + data)
        elif client.connectionType == ConnectionType.WS:
            pass

    def SendToAll(self, msgType, data):
        for client in self.clients:
            self.SendToClient(client, msgType, data)

    def Receive(self, client, data):
        self.receiveCallback(client, data)

    def newConnection(self, connectionType, socket, ip, port, thread):
        client = Client(self.clientUID, connectionType, socket, ip, port, thread)
        self.clientUID += 1
        self.clients.append(client)
        return client

