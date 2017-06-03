import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"


Page {
    id: page

    property alias feedViewModel: feedView.model

    allowedOrientations: Orientation.All

    onStatusChanged: {
        if (status === PageStatus.Active && pageStack.depth === 1) {
            pageStack.pushAttached("AboutPage.qml", {});
        }
    }

    SilicaFlickable {
        anchors.fill: parent

//        PullDownMenu {
//            MenuItem {
//                text: qsTr("Show Page 2")
//                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
//            }
//        }

        PageHeader {
            title: feedViewModel.balanceAmount + " " + feedViewModel.balanceCurrencyCode
            id: header
            description: feedViewModel.miles + " " +qsTr("rocketrubles")+ ";\n"+qsTr("Free cash outs") + " " + "TODO"
        }
        SilicaListView {
            clip: true
            id: feedView
            anchors.topMargin: header.height
            anchors.fill: parent
            VerticalScrollDecorator {}
            delegate: IconTextButton {
                text: details + ": " +money.amount
                iconSource: merchant.feed_icon
            }
        }
    }
}

