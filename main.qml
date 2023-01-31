import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQml.Models
import Qt.labs.qmlmodels
import "bgui/Style.js" as Style
import "application"

ApplicationWindow {
    id: window
    width: 640
    height: root.height
    x: Screen.width/2 - width/2
    y: Screen.height/4
    title: qsTr("Breeze Bar")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    color: "transparent"
    visible: true
    onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)
    onVisibleChanged: function() {
        if(visible) {
            requestActivate();
            bar.focus = true;
        }
        else {
            bar.text = "";
            bar.focus = true;
            searchEngineModel_.queryChanged("");
        }
    }
    onActiveChanged: function() {
        if(!active) {
            visible = false;
        }
    }

    Connections {
        target: hotkey_

        function onActivated() {
            visible = true;
        }
    }

    Rectangle {
        id: root
        x: 0
        y: 0
        width: window.width
        height: childrenRect.height+2*Style.borderWidth
        color: Style.bgColor
        radius: Style.baseRadius+Style.borderWidth
        Keys.onUpPressed: searchEngineModel_.decrementHighlight()
        Keys.onDownPressed: searchEngineModel_.incrementHighlight()
        Keys.onLeftPressed: function() {
            if(bar.cursorPosition === 0) {
                return;
            }
            var highlightedItem = listView.itemAtIndex(searchEngineModel_.highlightIndex).highlightedItem();
            if(!highlightedItem.actionLeft()) {
                bar.focus = true;
            }
        }
        Keys.onRightPressed: function() {
            root.focus = true;
            var highlightedItem = listView.itemAtIndex(searchEngineModel_.highlightIndex).highlightedItem();
            highlightedItem.actionRight();
        }
        Keys.onReturnPressed: function() {
            var highlightedItem = listView.itemAtIndex(searchEngineModel_.highlightIndex).highlightedItem();
            highlightedItem.act();
        }
        // hide window when escape pressed
        Keys.onEscapePressed: function() {
            if(window.visible) {
                window.visible = false;
            }
        }

        TextField {
            id: bar
            anchors {
                left: root.left
                right: root.right
                top: root.top
                margins: Style.borderWidth
            }
            color: Style.mainColor
            placeholderTextColor: Style.mutedColor
            background: Rectangle {
                color: Style.fgColor
                radius: Style.baseRadius
            }
            focus: true
            placeholderText: qsTr("Search for apps, files, anything...")
            font.pixelSize: 24
            font.family: "sans-serif"
            onTextEdited: function() {
                searchEngineModel_.queryChanged(text);
            }
        }

        ListView {
            id: listView

            anchors {
                left: root.left
                right: root.right
                top: bar.bottom
                margins: contentHeight !== 0 ? Style.borderWidth : 0
            }
            height: contentHeight
            spacing: Style.borderWidth
            interactive: false
            model: searchEngineModel_
            delegate: Item {
                required property var result;
                required property bool focused;

                width: listView.width
                height: focused ? focusedResult.height : defaultResult.height

                function highlightedItem() {
                    return focusedResult.item;
                }

                Item {
                    id: defaultResult

                    visible: !focused
                    height: 48
                    width: listView.width

                    RowLayout {
                        anchors.fill: parent
                        spacing: 10

                        Image {
                            id: image
                            source: result.imagePath
                            Layout.preferredWidth: 48
                            Layout.preferredHeight: 48
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
                                font.family: "sans-serif"
                                elide: Text.ElideRight
                                text: result.title
                            }
                            Text {
                                Layout.fillWidth: true
                                color: Style.mainColor
                                font.family: "sans-serif"
                                elide: Text.ElideRight
                                text: result.context
                            }
                        }
                    }
                }
                Loader {
                    id: focusedResult

                    visible: focused
                    asynchronous: !focused
                    source: switch(result.delegate) {
                        case "application":
                            return "./application/ApplicationResult.qml";
                    }
                }
            }
        }
    }
}
