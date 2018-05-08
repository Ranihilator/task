import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

ApplicationWindow
{
    title: qsTr("Hello World")

    signal test_crash(string text)

        visible: true
        width: 640
        height: 480

        Component.onCompleted:
        {
            setX(Screen.width / 2 - width / 2);
            setY(Screen.height / 2 - height / 2);
        }

        TextArea
        {
            id: chat
            anchors.fill: parent
            textFormat: TextEdit.RichText
            readOnly: true

            text: "to initiate the crash, typed in chat crash"
        }

        onClosing:
        {
            Qt.quit()
        }

    Window
    {
        id: input
        visible: true
        width: 640
        height: 80
        maximumWidth: 640
        maximumHeight: 80

        Component.onCompleted:
        {
            setX(Screen.width / 2 - width / 2);
            setY(Screen.height / 1.25);
        }

        Rectangle
        {
            id: emoji
            x: 10; y: 10
            width: 80; height: 80
            color: "white"
            state: "EMOJI_HIDDEN"
            states:
            [
                State
                {
                    name: "EMOJI_HIDDEN"
                    PropertyChanges
                    {
                        target: emoji
                        visible: false
                    }
                },
                State
                {
                    name: "EMOJI_SHOWN"
                    PropertyChanges
                    {
                        target: emoji
                        visible: true
                    }
                }
            ]

            GridLayout
            {
                id: grid
                anchors.fill: parent

                rows: 4
                columns: 18

                property var list:
                [
                    "emoji/grin.png",
                    "emoji/beam.png",
                    "emoji/expr_face.png",
                    "emoji/frowning.png",
                    "emoji/grinning.png",
                    "emoji/grinning_s.png",
                    "emoji/grinning_squint.png",
                    "emoji/grinning_sw.png",
                    "emoji/heart_smile.png",
                    "emoji/kiss.png",
                    "emoji/kiss_face.png",
                    "emoji/neutral.png",
                    "emoji/raised_eye.png",
                    "emoji/rolling.png",
                    "emoji/savor.png",
                    "emoji/sloghtly.png",
                    "emoji/smile.png",
                    "emoji/smile_face.png",
                    "emoji/sunglass.png",
                    "emoji/tears.png",
                    "emoji/think.png",
                    "emoji/wink.png"
                ]

                Repeater
                {
                    model: parent.list
                    Image
                    {
                        width: 10
                        height: 10

                        sourceSize.width: 30
                        sourceSize.height: 30
                        source: modelData
                        MouseArea
                        {
                            width: parent.width
                            height: parent.height
                            onClicked:
                            {
                                chat_input.insert(chat_input.cursorPosition, "<img src=" + parent.source + " height=20 width=20>")
                            }
                        }
                    }
                }
            }
        }

        TextArea
        {
            id: chat_input
            x: 10
            width: parent.width - 50 - 10
            height: 60
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            font.bold: true
            font.pointSize:20

            text: ""
            textFormat: TextEdit.RichText

            Keys.onReturnPressed:
            {
                chat.text += chat_input.text
                test_crash(chat_input.getText(0,chat_input.length))

                chat_input.text += " "
                chat_input.cursorPosition = chat_input.length

                chat_input.text = ""
            }
        }

        Button
        {
            width: 40
            height: 35
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 10
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            style: ButtonStyle {

                label: Image {
                    source: "emoji/grin.png"
                    fillMode: Image.PreserveAspectFit  // ensure it fits
                }
            }

            onClicked:
            {
                if (emoji.state == "EMOJI_HIDDEN")
                {
                    emoji.state = "EMOJI_SHOWN"
                    input.maximumHeight += 200;
                    input.height += 200

                }
                else
                {
                    emoji.state = "EMOJI_HIDDEN"
                    input.maximumHeight -= 200;
                    input.height -= 200
                }
            }
        }

        onClosing:
        {
            Qt.quit()
        }
    }
}
