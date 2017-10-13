import QtQuick 2.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property alias text: label.text
    property string iconSource
    property bool contentHighlighted
    property alias font: label.font
    property real padding: Theme.paddingLarge
    property real itemSize: Theme.itemSizeSmall

    // implicitWidth: text.implicitWidth + image.implicitWidth + content.spacing + 2*padding
    implicitHeight: itemSize + padding
    Item {
        id: content
        anchors.verticalCenter: parent.verticalCenter
        anchors.fill: parent
        anchors.margins: padding
        //spacing: Theme.paddingLarge

        Label {
            anchors.left: parent.left
            id: label
            width: parent.width-image.width-padding
            verticalAlignment: Text.AlignVCenter
            color: root.down || root.contentHighlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            truncationMode: TruncationMode.Fade
            wrapMode: Text.WordWrap
            textFormat: Text.AutoText
            // height: parent.height
            anchors.verticalCenter: parent.verticalCenter
        }

        Image {
            anchors.right: parent.right
            id: image
            width: Theme.itemSizeExtraSmall
            height: width
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
            source: root.iconSource // + "?" + (root.down || root.contentHighlighted ? Theme.highlightColor
                                    //                                              : Theme.primaryColor)
        }
    }
}
