import QtQuick 2.0
import Sailfish.Silica 1.0

import "./components"


Page {
    id: page

    property alias model: feedView.model

    allowedOrientations: Orientation.All

    onStatusChanged: {
        if (page.status === PageStatus.Active && pageStack.depth === 1) {
            if (!model.api.email) {
                model.api.registrationRequested()
            }
            else if (!model.api.token) {
                 coolFeedModel.reload()
            }
            else {
                pageStack.pushAttached(Qt.resolvedUrl("AboutPage.qml"), {});
            }
        }
    }

    Connections {
        target: model.api

        onRegistrationRequested: {
            if (page.status === PageStatus.Active && pageStack.depth === 1) {
                // pageStack.completeAnimation()
                pageStack.push(Qt.resolvedUrl("AuthPage.qml"), {"model": model});
            }
        }

        onRegistered: {
            coolFeedModel.reload()
        }

        onRocketCodeRequested: {
            pageStack.completeAnimation()
            if (pageStack.currentPage.objectName!=="LoginPage") {
                pageStack.push(Qt.resolvedUrl("LoginPage.qml"), {"model": coolFeedModel});
            }
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

        PullDownMenu {
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    coolFeedModel.reload()
                }
            }
        }

        PageHeader {
            title: model.balanceAmount + " " + model.balanceCurrencyCode
            id: header
            description: model.miles + " " +qsTr("rocketrubles") + "\n"
                         +(coolFeedModel.api.freeCashOutLimit-coolFeedModel.api.cashOutCount)
                         +" of "+coolFeedModel.api.freeCashOutLimit+qsTr(" free cash outs")
        }
        SilicaListView {
            clip: true
            id: feedView
            anchors.topMargin: header.height
            anchors.fill: parent
            VerticalScrollDecorator {}
            section.labelPositioning: ViewSection.InlineLabels
            section.property: "happened_at_date_string"
            section.criteria: ViewSection.FullString
            section.delegate: SectionHeader {
                horizontalAlignment: Text.AlignHCenter
                text: section
            }

            delegate: FeedListItem {
                width: feedView.width
                description: details ? details : ""
                text: money ? (money.amount && money.currency_code) ? money.amount + " " + getSymbolFromCurrency(money.currency_code) : "" : ""
                extraText: comment ? comment : ""
                iconSource: {
                    if (model.merchant) {
                        if (model.merchant.feed_icon) {
                            return model.merchant.feed_icon
                        }
                    }
                    if (model.friend) {
                        if (model.friend.userpic_url) {
                            return model.friend.userpic_url
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

