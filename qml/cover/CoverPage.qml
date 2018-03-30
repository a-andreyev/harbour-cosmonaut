import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    property string balanceAmount: coolFeedModel.balanceAmount
    property string balanceCurrencyCode: coolFeedModel.balanceCurrencyCode
    property string miles: coolFeedModel.miles

    Image {
        anchors.fill: parent
        id: bgLogo
        // TODO: fix draft rendering
        smooth: true
        source: "../assets/images/rocket.svg"
        opacity: 0.63
        sourceSize: Qt.size(parent.width,parent.height)
        fillMode: Image.PreserveAspectCrop
    }
    Column {
        anchors.fill: parent
        anchors.margins: Theme.paddingMedium
        Label {
            width: parent.width
            id: labelRubles
            text: balanceAmount + " " + balanceCurrencyCode
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
        Label {
            width: parent.width
            id: labelRocketRubles
            text: miles + " " + qsTr("rocketrubles")
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }

        Label {
            width: parent.width
            id: labelFreeCashOut
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: (coolFeedModel.api.freeCashOutLimit-coolFeedModel.api.cashOutCount)+" of "+coolFeedModel.api.freeCashOutLimit+qsTr(" free cash outs")
        }
    }

    CoverActionList {
        id: coverAction
        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: coolFeedModel.reload()
        }
    }
}

