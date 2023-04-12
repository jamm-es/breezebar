import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import "qrc:/breezebar/bgui/Style.js" as Style
import "../bgui"

Rectangle {
    id: settingResult

    property int actionIndex: 0;
    readonly property int numActions: 1;

    width: listView.width
    height: childrenRect.height+2*10
    color: Style.fgColor
    radius: Style.baseRadius

    // actionLeft and actionRight return false when focus should be returned to bar
    function actionLeft() {
        if(actionIndex === 0) {
            return false;
        }
        --actionIndex;
        if(actionIndex === 0) {
            return false;
        }
        return true;
    }
    function actionRight() {
        if(actionIndex < numActions-1) {
            ++actionIndex;
        }
        return true;
    }
    function act() {
        result.open();
    }

    RowLayout {
        x: 10
        y: 10
        width: listView.width-2*10
        spacing: 10

        Image {
            Layout.preferredWidth: 80
            Layout.preferredHeight: 80
            Layout.alignment: Qt.AlignTop
            width: 80
            height: 80
            source: result.imagePath
        }
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignVCenter
            spacing: 2

            Text {
                Layout.fillWidth: true
                color: Style.textColor
                font.family: bFont
                font.pixelSize: 24
                elide: Text.ElideRight
                text: result.title
            }
            Text {
                Layout.fillWidth: true
                color: Style.textMutedColor
                font.family: bFont
                font.pixelSize: 12
                elide: Text.ElideRight
                text: result.context
            }
            RowLayout {
                Layout.fillWidth: true

                BButton {
                    flat: true
                    active: settingResult.actionIndex === 0
                    text: "Open"
                    iconSource: "qrc:/breezebar/resources/icons/player-play.svg"
                }
            }
        }
    }
}
