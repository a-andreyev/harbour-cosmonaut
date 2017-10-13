import QtQuick 2.1
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    width: parent.width

    property alias text: label.text
    property alias description: descriptionLabel.text
    property alias extraText: extraLabel.text
    property string iconSource
    property bool contentHighlighted
    property alias font: label.font
    property real padding: Theme.paddingLarge

    implicitHeight: content.height + padding
    Item {
        id: content
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width-Theme.horizontalPageMargin*2
        height: col.height
        Column {
            id: col
            anchors.left: parent.left
            width: parent.width-image.width-padding
            spacing: Theme.paddingSmall
            Label {
                width: parent.width
                id: label
                verticalAlignment: Text.AlignVCenter
                color: root.down || root.contentHighlighted ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
            }
            Label {
                width: parent.width
                id: descriptionLabel
                verticalAlignment: Text.AlignVCenter
                color: root.down || root.contentHighlighted ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
            }
            Label {
                width: parent.width
                id: extraLabel
                verticalAlignment: Text.AlignVCenter
                color: root.down || root.contentHighlighted ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
            }
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
