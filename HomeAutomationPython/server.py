from NetCom import NetCom
from serial import Serial
from flask import Flask
from flask_cors import CORS
import json
from Constants import PROJECTOR_UID, AUDIO_SWITCH_UID, CHRISTMAS_TREE_UID


netCom = None
ser = None
app = Flask(__name__)
CORS(app)

christmasTreeState = False
projectorState = False
projectorVolume = 100
projectorAudioState = True
bluetoothState = True
alexaAudioState = False


def receive(client, data):
    ser.write(data)


def main():
    global ser
    global netCom

    ser = Serial("/dev/ttyUSB0", 115200)

    netCom = NetCom(receive)
    netCom.StartTcpServer()
    app.run(host='0.0.0.0', port=8042)

def sendCMD(uid, cmd, data):
    global ser

    msg = uid + ":" + cmd + ":" + data
    ser.write(msg.encode())
    return json.dumps({'state': 'ok', 'msg': msg})

@app.route('/')
def homepage():
    return 'This is the homepage'

#region projector
@app.route('/Projector/State')
def ProjectorState():
    return "1" if projectorState else "0"

@app.route('/Projector/Power/<state>')
def ProjectorPower(state):
    global projectorState
    projectorState = state == "1"
    return sendCMD(PROJECTOR_UID, "POW", state)

@app.route('/Projector/Volume/<val>')
def ProjectorVolume(val):
    global projectorVolume
    val = int(val)
    if val >= 100:
        val = 99
    elif val <= 0:
        val = 0
    offset = val - projectorVolume
    projectorVolume = val
    if offset > 0:
        return sendCMD(PROJECTOR_UID, "SO+", str(abs(offset)))
    else:
        return sendCMD(PROJECTOR_UID, "SO-", str(abs(offset)))
#endregion

#region audio switch
@app.route('/AudioSwitch/ProjectorState')
def AudioSwitchProjectorState():
    return "1" if projectorAudioState else "0"

@app.route('/AudioSwitch/AlexaState')
def AudioSwitchAlexaState():
    return "1" if alexaAudioState else "0"

@app.route('/AudioSwitch/SetChannels/<channels>')
def AudioSwitchSetChannels(channels):
    global projectorAudioState
    global alexaAudioState

    projectorAudioState = ("1" in channels)
    alexaAudioState = ("2" in channels)
    return sendCMD(AUDIO_SWITCH_UID, "SET", channels)
	
@app.route('/AudioSwitch/BluetoothState')
def AudioSwitchBluetoothState():
    return "1" if bluetoothState else "0"
	
@app.route('/AudioSwitch/SwitchBluetoothState')
def AudioSwitchSwitchBluetoothState():
    global bluetoothState
    bluetoothState = not bluetoothState
    return sendCMD(AUDIO_SWITCH_UID, "SBT", "")
#endregion

#region christmas tree
@app.route('/ChristmasTree/State')
def ChristmasTreeState():
    return "1" if christmasTreeState else "0"

@app.route('/ChristmasTree/Power/<state>')
def ChristmasTreePower(state):
    global christmasTreeState
    christmasTreeState = state == "1"
    return sendCMD(CHRISTMAS_TREE_UID, "POW", state)

@app.route('/ChristmasTree/SetSpeed/<speed>')
def ChristmasTreeSpeed(speed):
    return sendCMD(CHRISTMAS_TREE_UID, "SPD", speed)

@app.route('/ChristmasTree/SetPattern/<pattern>')
def ChristmasTreePattern(pattern):
    return sendCMD(CHRISTMAS_TREE_UID, "PAT", pattern)
#endregion



if __name__ == "__main__":
    main()


