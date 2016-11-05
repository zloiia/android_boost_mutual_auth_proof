import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {

    width: 360
    height: 360
    property alias result: result
    property alias portInput: portInput
    property alias hostInput: hostInput
    property alias fireButton: fireButton

    Button {
        id: fireButton
        x: 130
        y: 52
        text: qsTr("Fire")
    }

    TextInput {
        id: hostInput
        x: 29
        y: 15
        width: 80
        height: 20
        text: qsTr("192.168.88.2")
        font.pixelSize: 12
    }

    TextInput {
        id: portInput
        x: 242
        y: 15
        width: 80
        height: 20
        text: qsTr("4444")
        font.pixelSize: 12
    }

    Text {
        id: result
        x: 37
        y: 128
        width: 275
        height: 14
        text: qsTr("Text")
        font.pixelSize: 12
    }
}
