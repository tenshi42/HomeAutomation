from enum import Enum


##### Classes #####

class ConnectionType(Enum):
    TCP = 0
    WS = 1

class MsgType(Enum):
    Default = "0"
    Server = "1"

##### Variables #####

BUFFER_SIZE = 1024
PORT = 4242

PROJECTOR_UID = "ProRm"
AUDIO_SWITCH_UID = "AudSw"
CHRISTMAS_TREE_UID = "GuiNo"