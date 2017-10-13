import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.notifications 1.0
import "pages"

import harbour.cosmonaut.qtrestrocketapi 1.0
import harbour.cosmonaut.coolfeed 1.0
import com.github.qtrest.pagination 1.0 // FIXME: harbour restricts this kind of names

ApplicationWindow
{
    id: appWindow
    initialPage: Component { FeedPage { model: coolFeedModel } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    QtRestRocketAPI {
        id: rocketAPI
        baseUrl: "https://rocketbank.ru/api/v5"
        authTokenHeader: "Authorization"
        onServerError: {
            console.log(description)
            notification.showPopup(
                        qsTr("Server Error"),
                        description,
                        "image://theme/icon-lock-warning")
        }
        onServerMessage: {
            console.log(description)
            notification.showPopup(
                        qsTr("Server Message"),
                        description,
                        "image://theme/icon-lock-information")
        }

        /*

        onRegistrationRequested: {
            console.log("onRegistrationRequested")
            pageStack.completeAnimation()
            pageStack.push(Qt.resolvedUrl("pages/AuthPage.qml"), {"model": coolFeedModel});
        }

        onRegistered: {
            coolFeedModel.reload()
        }

        onRocketCodeRequested: {
            pageStack.completeAnimation()
            pageStack.push(Qt.resolvedUrl("pages/LoginPage.qml"), {"model": coolFeedModel});
        }

        onLoggedIn: {
            coolFeedModel.reload()
        }

        Component.onCompleted: {
            registrationRequested()
        }
        */
    }
    CoolFeedModel {
        id: coolFeedModel
        api: rocketAPI
        // Component.onCompleted: { reload(); }
        onLoadingStatusChanged: {
            //console.log(loadingStatus)
        }
        onLoadingErrorCodeChanged: {
            //console.log("error code", loadingErrorCode)
        }

        onLoadingErrorStringChanged: {
           //console.log(loadingErrorString)
        }
        onDataChanged: {
            //console.log(data)
        }
    }

    Notification {
        id: notification
        appIcon: "image://theme/icon-lock-warning"
        function showPopup(title, message, icn) {
            replacesId = 0
            previewSummary = title
            previewBody = message
            icon = icn
            publish()
        }
        expireTimeout: 3000
    }
}

