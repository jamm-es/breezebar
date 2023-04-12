import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQml.Models
import Qt5Compat.GraphicalEffects
import Qt.labs.qmlmodels
import "bgui/Style.js" as Style

ApplicationWindow {
    id: window

    property alias bFont: fontLoader.font.family

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
            bar.focus = false;
            searchEngineModel_.queryChanged("");
        }
    }
    onActiveChanged: function() {
        if(!active) {
            visible = false;
            lower();
        }
    }
    Component.onCompleted: function() {
        requestActivate();
        bar.focus = true;
        show();
//        if(!active) {
//            visible = false;
//        }
    }

    FontLoader {
        id: fontLoader
        source: "qrc:/breezebar/resources/fonts/Inter-Regular.ttf"
    }
    Connections {
        target: hotkey_

        function onActivated() {
            show();
//            visible = true;
        }
    }

    Rectangle {
        id: root
        x: 0
        y: 0
        width: window.width
        height: childrenRect.height+2*Style.externalPadding
        color: Style.bgColor
        radius: Style.outerRadius
        border.color: Style.windowBorderColor
        border.width: Style.windowBorderWidth
        Keys.onUpPressed: function() {
            searchEngineModel_.decrementHighlight();
        }

        Keys.onDownPressed: function() {
            searchEngineModel_.incrementHighlight();
        }
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
                margins: Style.externalPadding
            }
            height: 42
            verticalAlignment: TextInput.AlignVCenter
            color: Style.textColor
            placeholderTextColor: Style.textMutedColor
            background: Rectangle {
                color: Style.bgColor
                radius: Style.baseRadius
                border.color: Style.borderColor
                border.width: Style.borderWidth

                Item {
                    width: 24
                    height: 24
                    anchors.left: parent.left
                    anchors.leftMargin: 14
                    anchors.verticalCenter: parent.verticalCenter

                    Image {
                        id: icon
                        anchors.fill: parent
                        source: "qrc:/breezebar/resources/icons/search.svg"
                    }

                    ColorOverlay {
                        anchors.fill: parent
                        source: icon
                        color: Style.textColor
                    }
                }
            }
            leftPadding: Style.borderWidth+14+24+10
            font.family: bFont
            font.pixelSize: 20
            focus: true
            placeholderText: qsTr("Search for apps, files, anything...")
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
                margins: searchEngineModel_.rowCount !== 0 ? Style.externalPadding : 0
            }
            height: contentHeight
            spacing: 15
            interactive: false
            model: searchEngineModel_

//            delegate: DelegateChooser {
//                id: delegateChooser
//                role: 'delegate'

//                DelegateChoice {
//                    roleValue: "application"
//                    delegate: ApplicationResult {

//                    }
//                }
//                DelegateChoice {
//                    roleValue: "setting"
//                    delegate: SettingResult {

//                    }
//                }
//                DelegateChoice {
//                    roleValue: "default"
//                    delegate: Item {
//                        id: defaultResult

//                        height: 48
//                        width: listView.width

//                        RowLayout {
//                            anchors.fill: parent
//                            spacing: 10

//                            Image {
//                                id: image
//                                source: result.imagePath
//                                Layout.preferredWidth: 48
//                                Layout.preferredHeight: 48
//                                Layout.alignment: Qt.AlignTop
//                                fillMode: Image.Stretch
//                            }
//                            ColumnLayout {
//                                Layout.fillWidth: true
//                                Layout.fillHeight: true
//                                Layout.alignment: Qt.AlignTop

//                                Text {
//                                    Layout.fillWidth: true
//                                    color: Style.textColor
//                                    font.family: bFont
//                                    elide: Text.ElideRight
//                                    text: result.title
//                                }
//                                Text {
//                                    Layout.fillWidth: true
//                                    color: Style.textColor
//                                    font.family: bFont
//                                    elide: Text.ElideRight
//                                    text: result.context
//                                }
//                            }
//                        }
//                    }
//                }
//            }

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
                    height: 40
                    width: listView.width

                    RowLayout {
                        anchors.fill: parent
                        spacing: 10

                        Image {
                            id: image
                            source: result.imagePath
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 40
                            Layout.alignment: Qt.AlignTop
                            fillMode: Image.Stretch
                        }
                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignTop
                            spacing: 2

                            Text {
                                Layout.fillWidth: true
                                color: Style.textColor
                                font.family: bFont
                                font.pixelSize: 18
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
                        case "setting":
                            return "./setting/SettingResult.qml";
                    }
                }
            }
        }
    }
}
