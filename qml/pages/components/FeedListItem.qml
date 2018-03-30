import QtQuick 2.1
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

ListItem {
    id: root

    width: parent.width
    contentHeight: content.height

    property alias text: label.text
    property alias description: descriptionLabel.text
    property alias extraText: extraLabel.text
    property string iconSource
    property alias font: label.font
    property real padding: Theme.paddingMedium

    // TODO: move to utils

    function stringToHue(str) {
        var hash = 0;
        if ((str).length === 0) return hash;
        for (var i = 0; i < (str).length; i++) {
            hash = (str).charCodeAt(i) + ((hash << 5) - hash);
            hash = hash & hash;
        }
        return Math.abs(360/(hash % 360)%1);
    }

    function getSymbolFromCurrency(currencyCode) {
        const currencySymbolMap = {
          'AED': 'د.إ',
          'AFN': '؋',
          'ALL': 'L',
          'AMD': '֏',
          'ANG': 'ƒ',
          'AOA': 'Kz',
          'ARS': '$',
          'AUD': '$',
          'AWG': 'ƒ',
          'AZN': '₼',
          'BAM': 'KM',
          'BBD': '$',
          'BDT': '৳',
          'BGN': 'лв',
          'BHD': '.د.ب',
          'BIF': 'FBu',
          'BMD': '$',
          'BND': '$',
          'BOB': '$b',
          'BRL': 'R$',
          'BSD': '$',
          'BTC': '฿',
          'BTN': 'Nu.',
          'BWP': 'P',
          'BYR': 'Br',
          'BYN': 'Br',
          'BZD': 'BZ$',
          'CAD': '$',
          'CDF': 'FC',
          'CHF': 'CHF',
          'CLP': '$',
          'CNY': '¥',
          'COP': '$',
          'CRC': '₡',
          'CUC': '$',
          'CUP': '₱',
          'CVE': '$',
          'CZK': 'Kč',
          'DJF': 'Fdj',
          'DKK': 'kr',
          'DOP': 'RD$',
          'DZD': 'دج',
          'EEK': 'kr',
          'EGP': '£',
          'ERN': 'Nfk',
          'ETB': 'Br',
          'ETH': 'Ξ',
          'EUR': '€',
          'FJD': '$',
          'FKP': '£',
          'GBP': '£',
          'GEL': '₾',
          'GGP': '£',
          'GHC': '₵',
          'GHS': 'GH₵',
          'GIP': '£',
          'GMD': 'D',
          'GNF': 'FG',
          'GTQ': 'Q',
          'GYD': '$',
          'HKD': '$',
          'HNL': 'L',
          'HRK': 'kn',
          'HTG': 'G',
          'HUF': 'Ft',
          'IDR': 'Rp',
          'ILS': '₪',
          'IMP': '£',
          'INR': '₹',
          'IQD': 'ع.د',
          'IRR': '﷼',
          'ISK': 'kr',
          'JEP': '£',
          'JMD': 'J$',
          'JOD': 'JD',
          'JPY': '¥',
          'KES': 'KSh',
          'KGS': 'лв',
          'KHR': '៛',
          'KMF': 'CF',
          'KPW': '₩',
          'KRW': '₩',
          'KWD': 'KD',
          'KYD': '$',
          'KZT': 'лв',
          'LAK': '₭',
          'LBP': '£',
          'LKR': '₨',
          'LRD': '$',
          'LSL': 'M',
          'LTC': 'Ł',
          'LTL': 'Lt',
          'LVL': 'Ls',
          'LYD': 'LD',
          'MAD': 'MAD',
          'MDL': 'lei',
          'MGA': 'Ar',
          'MKD': 'ден',
          'MMK': 'K',
          'MNT': '₮',
          'MOP': 'MOP$',
          'MRO': 'UM',
          'MRU': 'UM',
          'MUR': '₨',
          'MVR': 'Rf',
          'MWK': 'MK',
          'MXN': '$',
          'MYR': 'RM',
          'MZN': 'MT',
          'NAD': '$',
          'NGN': '₦',
          'NIO': 'C$',
          'NOK': 'kr',
          'NPR': '₨',
          'NZD': '$',
          'OMR': '﷼',
          'PAB': 'B/.',
          'PEN': 'S/.',
          'PGK': 'K',
          'PHP': '₱',
          'PKR': '₨',
          'PLN': 'zł',
          'PYG': 'Gs',
          'QAR': '﷼',
          'RMB': '￥',
          'RON': 'lei',
          'RSD': 'Дин.',
          'RUB': '₽',
          'RWF': 'R₣',
          'SAR': '﷼',
          'SBD': '$',
          'SCR': '₨',
          'SDG': 'ج.س.',
          'SEK': 'kr',
          'SGD': '$',
          'SHP': '£',
          'SLL': 'Le',
          'SOS': 'S',
          'SRD': '$',
          'SSP': '£',
          'STD': 'Db',
          'STN': 'Db',
          'SVC': '$',
          'SYP': '£',
          'SZL': 'E',
          'THB': '฿',
          'TJS': 'SM',
          'TMT': 'T',
          'TND': 'د.ت',
          'TOP': 'T$',
          'TRL': '₤',
          'TRY': '₺',
          'TTD': 'TT$',
          'TVD': '$',
          'TWD': 'NT$',
          'TZS': 'TSh',
          'UAH': '₴',
          'UGX': 'USh',
          'USD': '$',
          'UYU': '$U',
          'UZS': 'лв',
          'VEF': 'Bs',
          'VND': '₫',
          'VUV': 'VT',
          'WST': 'WS$',
          'XAF': 'FCFA',
          'XBT': 'Ƀ',
          'XCD': '$',
          'XOF': 'CFA',
          'XPF': '₣',
          'YER': '﷼',
          'ZAR': 'R',
          'ZWD': 'Z$'
        }
        if (typeof currencyCode !== 'string') return undefined
        var code = currencyCode.toUpperCase()
        if (!currencySymbolMap.hasOwnProperty(code)) return undefined
        return currencySymbolMap[code]
    }

    Item {
        id: content
        anchors {
            left: parent.left
            right: parent.right
            margins: Theme.horizontalPageMargin
        }
        height: Math.max(image.height,col.height) + 2*Theme.paddingMedium

        Item {
            anchors.left: parent.left
            id: image
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.itemSizeExtraSmall
            height: width
            Rectangle {
                id: dummy
                anchors.fill: parent
                visible: (img.status !== Image.Ready)
                radius: width
                color: Qt.hsla(stringToHue(root.description),0.5, 0.4,1);
                Label {
                    anchors.centerIn: parent
                    text: root.description.charAt(0).toUpperCase();
                    font.bold: true
                    font.pixelSize: Theme.fontSizeLarge
                }
            }
            Image {
                visible: false
                id: img
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: root.iconSource
                smooth: true
            }
            ColorOverlay {
                anchors.fill: parent
                source: dummy.visible ? dummy : img
                color: root.down ? Theme.rgba(Theme.highlightColor,0.6) : Qt.hsla(0,0,0,0)
                property bool rounded: true
                property bool adapt: true
                layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: img.width
                        height: img.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: img.adapt ? img.width : Math.min(img.width, img.height)
                            height: img.adapt ? img.height : width
                            radius: Math.min(width, height)
                        }
                    }
                }
            }
        }

        Column {
            id: col
            anchors {
                verticalCenter: parent.verticalCenter
                left: image.right
                right: label.left
                margins: root.padding
            }
            Label {
                width: parent.width
                id: descriptionLabel
                verticalAlignment: Text.AlignVCenter
                color: root.down ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
            }
            Label {
                width: parent.width
                id: extraLabel
                visible: text
                verticalAlignment: Text.AlignVCenter
                color: root.down ? Theme.secondaryHighlightColor : Theme.secondaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
            }
        }


        Label {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            id: label
            verticalAlignment: Text.AlignVCenter
            color: root.down ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeMedium
            wrapMode: Text.WordWrap
            textFormat: Text.AutoText
        }
    }
}
