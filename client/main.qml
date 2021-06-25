import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 320
    height: 480
    title: qsTr("Hello drifter")

    Rectangle {
        width: parent.width
        height: parent.height - button_bar.height
        anchors.horizontalCenter: parent.horizontalCenter


        Text {
            text: chat_app._messages;
//            text: "test text"
            anchors.fill: parent;
            color: "black";

            Connections {
                target: chat_app
                onMessagesChanged:{
                    console.log("data has beed changed!");
                }
            }
        }

//        ListView {
//                id: view
//                anchors.fill: parent
//                model: message_model

//                delegate: Rectangle {
//                    width: view.width
//                    height: message_text.contentHeight * 1.5
//                    color: "transparent"
//                    border.color: "black"
//                    border.width: 1

//                    Rectangle {
//                        id: message_text
//                        width: parent.width * 0.8 >= message_text.contentWidth
//                               ? message_text.contentWidth
//                               : parent.width * 0.8

//                        anchors.right: parent.right
//                        Text {
//                            text: message_text
//                            verticalAlignment: Text.AlignVCenter
//                            anchors.verticalCenter: parent.verticalCenter
//                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                        }
//                    }
//                }

//                ListModel {
//                    id: message_model
//                }
//            }
    }

    Rectangle {
        id: button_bar
        width: parent.width
        height: 60
        color: "#E8E8E8"
        border.color: "#CFCFCF"
        border.width: 1
        anchors.bottom: parent.bottom

        Rectangle {
            id: button_send
            color: "white"
            width: 50
            height: 50
            radius: 10
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: "send"
                color: "black"
                font.family: "Helvetica"
                font.pointSize: 10
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var ret = chat_app.send_msg("drifter_b", 1, false, "hello drifter")
                }
            }
        }

        Rectangle {
            id: button_pull
            color: "white"
            width: 50
            height: 50
            radius: 10
            anchors.left: button_send.right
            anchors.leftMargin: 25
            anchors.verticalCenter: button_send.verticalCenter

            Text {
                text: "pull"
                color: "black"
                font.family: "Helvetica"
                font.pointSize: 10
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var ret = chat_app.pull_message();
                }
            }
        }

        Rectangle {
            id: button_settings
            color: "white"
            width: 50
            height: 50
            radius: 10
            anchors.left: button_pull.right
            anchors.leftMargin: 25
            anchors.verticalCenter: button_pull.verticalCenter

            Text {
                text: "settings"
                color: "black"
                font.family: "Helvetica"
                font.pointSize: 10
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var ret = chat_app.account_load();
                }
            }
        }

        Rectangle {
            id: button_update_account
            color: "white"
            width: 50
            height: 50
            radius: 10
            anchors.left: button_settings.right
            anchors.leftMargin: 25
            anchors.verticalCenter: button_settings.verticalCenter

            Text {
                text: "update"
                color: "black"
                font.family: "Helvetica"
                font.pointSize: 10
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var ret = chat_app.account_update();
                }
            }
        }
    }


}
