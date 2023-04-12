import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "./Style.js" as Style

Button {
    id: control

    property bool active: false;
    property string iconSource: '';

    contentItem: RowLayout {
        Item {
            Layout.alignment: Qt.AlignVCenter
            width: 20
            height: 20

            Image {
                id: icon
                anchors.fill: parent
                source: iconSource
            }
            ColorOverlay {
                anchors.fill: parent
                source: icon
                color: Style.textColor
            }
        }

        Text {
            Layout.alignment: Qt.AlignVCenter
            text: control.text
            font.family: bFont
            font.pixelSize: 18
            color: Style.textColor
            elide: Text.ElideRight
        }
    }


    background: Rectangle {
        color: "transparent"
        border.color: Style.highlightColor
        border.width: active ? Style.highlightWidth : 0
        radius: Style.baseRadius
    }

}
