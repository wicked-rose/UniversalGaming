

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.3
import QtQuick.Controls 6.3
import UniversalGaming

Rectangle {
    id: rectangle
    width: Constants.width
    height: 800
    color: "#ffffff"
    border.color: "#ffffff"

    Rectangle {
        id: menu
        width: 250
        height: 800
        color: "#e1fff9"
        border.color: "#aab2bd"
        border.width: 0

        Button {
            id: home
            height: 50
            text: qsTr("Home")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.capitalization: Font.AllUppercase
            font.pointSize: 18
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.topMargin: 20
        }

        Button {
            id: presets
            height: 50
            text: qsTr("Presets")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.capitalization: Font.AllUppercase
            font.pointSize: 18
            anchors.topMargin: 80
            anchors.leftMargin: 10
            anchors.rightMargin: 10
        }

        Button {
            id: custom
            height: 50
            text: qsTr("Custom")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.bold: false
            font.capitalization: Font.AllUppercase
            font.pointSize: 18
            anchors.topMargin: 140
            anchors.leftMargin: 10
            anchors.rightMargin: 10
        }

        Button {
            id: options
            height: 50
            text: qsTr("On-Screen Options")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            font.capitalization: Font.AllUppercase
            font.pointSize: 18
            anchors.topMargin: 200
            anchors.leftMargin: 12
            anchors.rightMargin: 8
        }
    }

    Rectangle {
        id: rectangle1
        width: 750
        color: "#ffffff"
        border.color: "#aab2bd"
        border.width: 0
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        Image {
            id: image
            y: 140
            height: 500
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            source: "../../../../../../Documents/Fall 22/CpE Design 1/controllerDiagram.png"
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            fillMode: Image.PreserveAspectFit
            anchors.rightMargin: 20
        }

        Text {
            id: text1
            height: 106
            text: "Custom Controller Layout"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Courier"
            anchors.leftMargin: 10
            anchors.topMargin: 10
            font.capitalization: Font.AllUppercase
            textFormat: Text.RichText
            font.pointSize: 42
            anchors.rightMargin: 10
            font.weight: Font.DemiBold
        }
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
    }

    states: [
        State {
            name: "clicked"
            when: home.checked
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:6}
}
##^##*/
