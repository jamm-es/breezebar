import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "./Style.js" as Style

Button {
    id: control

    property bool active: false;

    contentItem: Text {
        text: control.text
        font.family: Style.font
        font.pixelSize: 18
        color: Style.mainColor
        elide: Text.ElideRight
        anchors.verticalCenter: parent.verticalCenter
    }

    background: Rectangle {
        color: "transparent"
        border.color: Style.highlightColor
        border.width: active ? 5 : 0
        radius: 10
    }

}
