import QtQuick 2.7
import QtQuick.Window 2.2
import testclient 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Socket {
        id: socket
        onSuccessAnswerSignal: {
            mainW.result.text = serverAnswer;
        }
    }

    MainForm {
        id: mainW
        fireButton.onClicked: {
            result.text = "";
            socket.fire(hostInput.text, portInput.text*1);
        }
        anchors.fill: parent

    }
}
