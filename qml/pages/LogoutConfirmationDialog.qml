import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    DialogHeader {
        title: qsTr("Really logout?")
        acceptText: qsTr("Logout")
        cancelText: qsTr("Back")
    }
    onAccepted: {
        coolFeedModel.api.clearSettings()
        Qt.quit()
    }
}
