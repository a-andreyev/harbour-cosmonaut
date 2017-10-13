import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"

Dialog {
    id: pages

    property var model

    allowedOrientations: Orientation.All
    canAccept: false
    Connections {
        target: model.api
        onLoggedIn: {
            canAccept = true
            accept()
        }
    }

    // TODO: 18E4

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
            acceptText: ""
        }

        TextField {
            echoMode: TextInput.Password
            anchors.fill: parent
            id: pinInputTextField
            anchors.topMargin: header.height
            width: parent.width
            height: parent.height-header.height
            placeholderText: qsTr("PIN code")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly | Qt.ImhHiddenText
            validator: IntValidator { bottom: 0; top: 9999 }
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                model.api.login(text)
            }
        }
    }
    onRejected: {
        Qt.quit()
    }
}
