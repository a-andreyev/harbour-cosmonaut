import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"

Dialog {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }
        PushUpMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        DialogHeader {
            id: header
            title: qsTr("Enter Rocketbank card PIN code")
        }

        TextField {
            echoMode: TextInput.Password
            anchors.fill: parent
            id: tfphonenumber
            anchors.topMargin: header.height
            width: parent.width
            height: parent.height-header.height
            placeholderText: qsTr("PIN code")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly | Qt.ImhHiddenText
            validator: IntValidator { bottom: 0; top: 9999 }
        }
    }
    onDone: {
        if (result == DialogResult.Accepted) {
            console.log("accepted")
        }
        else {
            Qt.quit()
        }
    }
    onRejected: {
        Qt.quit()
    }
}
