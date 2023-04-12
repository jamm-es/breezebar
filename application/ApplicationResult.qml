import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "qrc:/breezebar/bgui/Style.js" as Style
import "../bgui"

Rectangle {
    id: applicationResult

    property int actionIndex: 0;
    readonly property int numActions: 2;

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
        switch(applicationResult.actionIndex) {
        case 0:
            result.run();
            break;
        case 1:
            result.runPrivileged();
            break;
        }
    }

    RowLayout {
        x: 10
        y: 10
        width: listView.width-2*10
        spacing: 10

        Image {
            id: image
            source: result.imagePath
            Layout.preferredWidth: 80
            Layout.preferredHeight: 80
            Layout.alignment: Qt.AlignTop
            fillMode: Image.Stretch
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
                    active: applicationResult.actionIndex === 0
                    text: "Run"
                    iconSource: 'qrc:/breezebar/resources/icons/player-play.svg'
                }
                BButton {
                    flat: true
                    active: applicationResult.actionIndex === 1
                    text: "Run as administrator"
                    iconSource: 'qrc:/breezebar/resources/icons/shield.svg'

                }
            }
        }
    }
}
