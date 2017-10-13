import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"

Dialog {
    id: dialog

    allowedOrientations: Orientation.All
    canNavigateForward: false
    canAccept: model.api.email

    property var model

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
            title: dialog.canAccept ? qsTr("Hello, ")+model.api.firstName : qsTr("Application registration")
            cancelText: qsTr("Reject")
            acceptText: qsTr("Approve")
        }

        Column {
            visible: !dialog.canAccept
            anchors.top: header.bottom
            width: parent.width-2*Theme.horizontalPageMargin
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height-header.height
            spacing: Theme.paddingMedium
            Label {
                text: model.api.email
            }
            // TODO: image
        }

        Column {
            visible: !dialog.canAccept
            anchors.top: header.bottom
            width: parent.width-2*Theme.horizontalPageMargin
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height-header.height
            spacing: Theme.paddingMedium

            Item {
                width: parent.width
                height: Theme.itemSizeMedium
                TextField {
                    id: phoneNumberInputTextField
                    anchors.left: parent.left
                    width: parent.width-requestSmsButton.width-Theme.paddingSmall
                    height: Theme.itemSizeMedium
                    placeholderText: qsTr("Phone number")
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDialableCharactersOnly
                    validator: RegExpValidator { regExp: /\+?[\d]{1,12}/ }
                    label: placeholderText
                }
                Button {
                    anchors.right: parent.right
                    id: requestSmsButton
                    enabled: phoneNumberInputTextField.acceptableInput
                    height: Theme.itemSizeMedium
                    text: qsTr("Request SMS code")
                    onClicked: {
                        model.api.requestSMS(phoneNumberInputTextField.text)
                    }
                }
            }

            TextField {
                echoMode: TextInput.Password
                id: smsInputTextField
                width: parent.width
                height: Theme.itemSizeMedium
                placeholderText: qsTr("SMS code")
                inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly | Qt.ImhHiddenText
                validator: IntValidator { bottom: 0; top: 9999 }
                label: placeholderText
            }

            Button {
                enabled: phoneNumberInputTextField.acceptableInput && smsInputTextField.acceptableInput
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Verify SMS code")
                onClicked: {
                    coolFeedModel.api.verifySMSCode(smsInputTextField.text)
                }
            }
        }
    }
    onDone: {
        if (result == DialogResult.Accepted) {
            model.api.saveRegistation()
        }
        else {
            Qt.quit()
        }
    }
}
