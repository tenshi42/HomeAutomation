import Constants


class Client:
    def __init__(self, uid, connectionType, socket, ip, port, thread):
        self.name = None
        self.uid = uid
        self.ip = ip
        self.port = port
        self.connectionType = connectionType
        self.socket = socket
        self.thread = thread

