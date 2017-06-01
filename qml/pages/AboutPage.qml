import QtQuick 2.1
import Sailfish.Silica 1.0
import "./components"

Page {
    SilicaFlickable {
        contentHeight: column.height+Theme.paddingLarge
        anchors.fill: parent

        VerticalScrollDecorator {}

        Column {
            spacing: Theme.paddingLarge
            id: column
            width: parent.width
            PageHeader {
                title: qsTr("About")
                id: header
            }
            SectionHeader {
                text: qsTr("Licence information")
            }
            Label {
                textFormat: Text.StyledText
                font.pixelSize: Theme.fontSizeSmall
                horizontalAlignment: Text.AlignJustify
                wrapMode: Text.Wrap
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.paddingLarge
                }
                text: qsTr("This application is made by Alexey Andreyev
                    as non-commertial work without Rocketbank.
                    Application cover is made by Alexey
                    with help from Ancelad (thanks!).
                    This application is developed with Sailfish IDE
                    in GNU/Linux/Archlinux/KDE operating system.
                    Licence: GPLv3")
            }
            SectionHeader {
                text: qsTr("Donate")
            }
            IconTextButton {
                text: "Paypal: paypal.me/aa13q"
                iconSource: "../../assets/images/paypal.svg"
                onClicked: {
                    Qt.openUrlExternally("https://paypal.me/aa13q");
                }
            }

            IconTextButton {
                text: "Flattr: flattr.com/profile/aa13q"
                iconSource: "../../assets/images/flattr.svg"
                onClicked: {
                    Qt.openUrlExternally("https://flattr.com/profile/aa13q");
                }
            }

            IconTextButton {
                text: qsTr("Rocketbank")+": rocketbank.ru/aa13q-alexey-andreyev"
                iconSource: "../../assets/images/rocketbank.svg"
                onClicked: {
                    Qt.openUrlExternally("https://rocketbank.ru/aa13q-alexey-andreyev");
                }
            }

            SectionHeader {
                text: qsTr("Sources")
            }
            IconTextButton {
                text: "Github: github.com/a-andreyev/harbour-cosmonaut"
                iconSource: "../../assets/images/git.svg"
                onClicked: {
                    Qt.openUrlExternally("https://github.com/a-andreyev/harbour-cosmonaut");
                }
            }

            SectionHeader {
                text: qsTr("Contacts")
            }
            Label {
                font.pixelSize: Theme.fontSizeMedium
                horizontalAlignment: Text.AlignJustify
                wrapMode: Text.Wrap
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.paddingLarge
                }
                text: qsTr("My name is Alexey Andreyev. I'm PhD student from Saint Petersburg, Russia. Donations are welcome.")
            }
            IconTextButton {
                text: qsTr("My website")+": aa13q.ru"
                iconSource: "../../assets/images/aa13q.jpeg"
                onClicked: {
                    Qt.openUrlExternally("http://aa13q.ru/");
                }
            }
            Image {
                source: "../assets/images/le_me.jpeg"
                fillMode: Image.PreserveAspectFit
                anchors {
                            left: parent.left
                            right: parent.right
                            margins: Theme.paddingLarge
                        }
                height: width
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.paddingLarge
                }
            }
        }
    }
}
