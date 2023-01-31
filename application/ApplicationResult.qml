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
    height: childrenRect.height+2*Style.borderWidth
    color: Style.resultColor
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
        x: Style.borderWidth
        y: Style.borderWidth
        width: listView.width-2*Style.borderWidth
        spacing: 10

        Image {
            id: image
            source: result.imagePath
            Layout.preferredWidth: 96
            Layout.preferredHeight: 96
            Layout.alignment: Qt.AlignTop
            fillMode: Image.Stretch
        }
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop

            Text {
                Layout.fillWidth: true
                color: Style.mainColor
                font.pixelSize: 30
                font.family: "sans-serif"
                elide: Text.ElideRight
                text: result.title
            }
            Text {
                Layout.fillWidth: true
                color: Style.mutedColor
                font.family: "sans-serif"
                elide: Text.ElideRight
                text: result.context
            }
            RowLayout {
                Layout.fillWidth: true

                BButton {
                    id: first
                    flat: true
                    active: applicationResult.actionIndex === 0
                    font.pixelSize: 24
                    font.family: "sans-serif"
                    text: "▶ Run"
                }
                BButton {
                    flat: true
                    active: applicationResult.actionIndex === 1
                    text: "▶ Run as administrator"
                }
            }
        }
    }
}
