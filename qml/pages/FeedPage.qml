import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"


Page {
    id: page

    property alias model: feedView.model

    allowedOrientations: Orientation.All

    onStatusChanged: {
        if (page.status === PageStatus.Active && pageStack.depth === 1) {
            pageStack.pushAttached(Qt.resolvedUrl("AboutPage.qml"), {});
            if (!model.api.email) {
                model.api.registrationRequested()
            }
            else {
                coolFeedModel.reload()
            }
        }
    }

    Connections {
        target: model.api

        onRegistrationRequested: {
            pageStack.completeAnimation()
            pageStack.push(Qt.resolvedUrl("AuthPage.qml"), {"model": model});
        }

        onRegistered: {
            coolFeedModel.reload()
        }

        onRocketCodeRequested: {
            pageStack.completeAnimation()
            pageStack.push(Qt.resolvedUrl("LoginPage.qml"), {"model": coolFeedModel});
        }

        onLoggedIn: {
            coolFeedModel.reload()
        }
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: coolFeedModel.loadingStatus
    }

    SilicaFlickable {
        anchors.fill: parent

        PageHeader {
            title: model.balanceAmount + " " + model.balanceCurrencyCode
            id: header
            description: model.miles + " " +qsTr("rocketrubles") //+ ";\n"+qsTr("Free cash outs") + " " + "TODO"
        }
        SilicaListView {
            clip: true
            id: feedView
            anchors.topMargin: header.height
            anchors.fill: parent
            VerticalScrollDecorator {}
            delegate: FeedListItem {
                description: details ? details : ""
                text: money ? money.amount ? money.amount : "" : ""
                extraText: {
                    if (model.happened_at) {
                        // console.log(happened_at)
                        return Qt.formatDateTime(new Date(happened_at),"hh:mm dd.MM.yyyy")
                    }
                    return ""
                }
                iconSource: {
                    if (model.friend) {
                        if (model.friend.userpic_url) {
                            return model.friend.userpic_url
                        }
                    }
                    if (model.merchant) {
                        if (model.merchant.feed_icon) {
                            return model.merchant.feed_icon
                        }
                    }
                    return ""
                }
                onClicked: {
                    Qt.openUrlExternally(receipt_url)
                }
            }
        }
    }
}

