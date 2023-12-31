import QtQuick

//import QtQuick.Controls
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQml.Models 2.12

Window {
    width: 1280
    height: 720
    visible: true
    maximumWidth: 1280
    maximumHeight: 720
    title: qsTr("EVTX CONVERTER")

    Timer {
        id: clockTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered:{
            clockText.text =  Qt.formatTime(new Date(),"hh:mm:ss")
        }
    }

    Timer {
        id: dateTimer
        interval: 1000
        repeat: true
        running: true
        property var locale: Qt.locale()
        property date currentDate: new Date()
        property string dateString
        onTriggered:{
            curDateTxt.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }

    //TO DO: Fix depercated syntax
    Connections {
        target: mainController

        onProcessingStatus2Qml:{
            summaryText.text = processingStatus;
        }
        //Display the file path
        onFilePathToQml:{
            cew_SelectFileTxt.text = filePath
        }
        //Display the dir path
        onDirPathToQml:{
            cew_SelectDirTxt.text = dirPath
        }
        //Display the save to path
        onSaveToPathToQml:{
            cew_SaveToTxt.text = saveToPath
        }
        onFileConvertEvtxStatus:{
            cew_logTxtArea.text += curStatus + "\n"
        }
        onFileNameToQml:{
            cew_fileSaveAsNameTxt.text = fileName
        }
        onDirPathSepToQml:{
            selectDirSeparateTxt.text = sDirPath
        }

        //function onSecurityEventCount2Qml(secEventCountX) {
        //secEventCountTxt.text = 11;
        //console.log("Signal Detected")
        // }
        // function onSecurityEventCount2Qml() {
        // secEventCountTxt.text = secEventCountX
        //console.log("Signal javascript function Detected")
        // }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1280
        height: 720
        //maximumHeight: 1280
        //maximumWidth: 720
        color: "#000000"

        Image {
            id: bgImg
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/EvtxConverter/images/bg.png"

            fillMode: Image.PreserveAspectFit

            Button {
                id: evtxWinSelectFileBtn
                x: 169
                y: 449
                width: 120
                height: 25
                text: qsTr("Select FIle")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
                onClicked: {
                    mainController.ce_SelectFile()
                }
            }

            Rectangle {
                id: ecw_SelectFileRect
                x: 304
                y: 449
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SelectFileTxt
                    x: 2
                    y: 2
                    width: 834
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Button {
                id: ce_SaveToBtn
                x: 169
                y: 577
                width: 120
                height: 25
                text: qsTr("Save To")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
                onClicked: {
                    mainController.ce_SaveToPath()
                }
            }

            Rectangle {
                id: ecw_SaveToRect
                x: 304
                y: 577
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SaveToTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Rectangle {
                id: ecw_TxtDataRect
                x: 169
                y: 64
                width: 974
                height: 360
                color: "#000000"
                border.color: "#ffffff"

                ScrollView {
                    id: ecw_scrollview
                    x: 3
                    y: 3
                    width: 968
                    height: 353

                    TextArea {
                        id: cew_logTxtArea
                        x: -7
                        y: -3
                        color: "#ffffff"
                        placeholderText: qsTr("Text Area")
                        background: Rectangle {color: "black"}
                    }
                }
            }

            Button {
                id: cew_selectDirBtn
                x: 169
                y: 492
                width: 120
                height: 25
                text: qsTr("Select Dir - Combine")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {
                    mainController.ce_SelectDir()
                }
            }

            Rectangle {
                id: ecw_SelectDirRect
                x: 304
                y: 492
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SelectDirTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Button {
                id: cew_StartBtn
                x: 448
                y: 667
                width: 125
                height: 27
                text: qsTr("Start")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {

                    if(control1.currentText === "Convert To"){
                        cew_logTxtArea.text += "Please select a conversion type..."+ "\n"
                        //console.log("Please select a conversion type...")
                        return;
                    }
                    else if(cew_SelectFileTxt.text === "" && cew_SelectDirTxt.text === "" && selectDirSeparateTxt.text === ""){
                        cew_logTxtArea.text += "Select a file or directory..." + "\n"
                        //console.log("Select file and both select dir felds are empty...")
                        return;
                    }
                    else if(cew_SaveToTxt.text === ""){
                        cew_logTxtArea.text += "Select a location to save the converted files" + "\n"
                        //console.log("Select a location to save the converted files...")
                        cew_logTxtArea.text += "Select a location to save the converted files.....\n"

                        return;
                    }
                    else if(cew_SelectFileTxt.text !== "" && cew_SelectDirTxt.text === "" && selectDirSeparateTxt.text === ""){
                        //console.log("Select file has text and selct dirs does not...")
                        if(cew_fileSaveAsNameTxt.text === ""){
                            //console.log("Please enter a file name...")
                            cew_logTxtArea.text += "Please enter a file name.....\n"
                            return;
                        }
                        else{
                            mainController.fileConvertEvtx(control1.currentText, cew_SelectFileTxt.text, cew_SaveToTxt.text, cew_fileSaveAsNameTxt.text)
                        }
                    }
                    else if(cew_SelectDirTxt.text !== "" && cew_SelectFileTxt.text === "" && selectDirSeparateTxt.text === ""){
                        //console.log("Select dir combine has text. select file and select dir separate does not...")
                        if(cew_fileSaveAsNameTxt.text !== ""){
                            //console.log("Error: File name must be blank for directory conversion.....")
                            cew_logTxtArea.text += "Error: File name must be blank for directory conversion.....\n"
                            return;
                        }
                        else{
                            mainController.dirConvertEvtx(control1.currentText, cew_SelectDirTxt.text, cew_SaveToTxt.text)
                            //console.log("SENDING Dir DATA TO C++...")
                        }
                    }
                    else if(selectDirSeparateTxt.text !== "" && cew_SelectDirTxt.text === "" &&  cew_SelectFileTxt.text === ""){
                        if(cew_fileSaveAsNameTxt.text !== ""){
                            //console.log("Error: File name must be blank for directory conversion.....")
                            cew_logTxtArea.text += "Error: File name must be blank for directory conversion.....\n"
                            return;
                        }
                        else{
                            mainController.dirConvertEachEvtx(control1.currentText, cew_SaveToTxt.text)
                           //console.log("SENDING Dir S DATA TO C++...")
                        }
                    }
                }
            }

            Rectangle {
                id: ecw_FIleNameRect
                x: 304
                y: 619
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                TextEdit {
                    id: cew_fileSaveAsNameTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 16
                }
            }

            Text {
                id: fileNameLabel
                x: 218
                y: 621
                color: "#ffffff"
                text: qsTr("File name:")
                font.pixelSize: 16
            }

            Button {
                id: cew_ClearBtn
                x: 845
                y: 667
                width: 125
                height: 27
                text: qsTr("Clear")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {
                    cew_logTxtArea.clear()
                    cew_SelectFileTxt.text = ""
                    cew_SelectDirTxt.text = ""
                    cew_SaveToTxt.text = ""
                    cew_fileSaveAsNameTxt.text = ""
                }
            }

            Image {
                id: image1
                x: 510
                y: 8
                width: 260
                height: 27
                source: "file:C:/EvtxConverter/images/logo.png"
                fillMode: Image.PreserveAspectFit
            }

            Button {
                id: cew_selectDirBtnSeparate
                x: 169
                y: 535
                width: 120
                height: 25
                text: qsTr("Select Dir - Separate")
                palette.buttonText: "#ffffff"
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    horizontalOffset: 2
                    verticalOffset: 2
                    spread: 0
                    transparentBorder: true
                }
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                onClicked: {
                    mainController.selectDirConvertEachEvtx()
                    //selectDirSeparateTxt.text = ""
                }
            }

            Rectangle {
                id: ecw_SelectDirRect1
                x: 304
                y: 535
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"
                Text {
                    id: selectDirSeparateTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Image {
                id: q1
                x: 1232
                y: 674
                width: 40
                height: 38
                source: "file:C:/EvtxConverter/images/qmarkBtnRound.png"
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: mouseArea
                    x: 0
                    y: 0
                    width: 40
                    height: 38
                    onClicked: {
                        cew_logTxtArea.text += "Select file: will convert a single EVTX file to JSON, XML, or CSV.\n\n" +
                                               "Select Dir Combine: will convert all EVTX files in the directory to a single JSON, XML, or CSV file.\n\n" +
                                               "Select Dir Separate: will convert and create a JSON, XML, or CSV file for each EVTX file in the directory.\n\n"
                    }
                }
            }
        }

        ComboBox {
            id: control1
            x: 169
            y: 37
            width: 116
            height: 21
            popup: Popup {
                y: control1.height - 1
                width: control1.width
                padding: 1
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#ffffff"
                }
                contentItem: ListView {
                    ScrollIndicator.vertical: ScrollIndicator {
                    }
                    currentIndex: control1.highlightedIndex
                    clip: true
                    model: control1.popup.visible ? control1.delegateModel : null
                    implicitHeight: contentHeight
                }
                implicitHeight: contentItem.implicitHeight
            }
            background: Rectangle {
                color: "#000000"
                radius: 2
                border.color: control1.pressed ? "#ffffff" : "#ffffff"
                border.width: control1.visualFocus ? 2 : 1
                implicitWidth: 120
                implicitHeight: 40
            }
            contentItem: Text {
                color: control1.pressed ? "#000000" : "#ffffff"
                text: control1.displayText
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                rightPadding: control1.indicator.width + control1.spacing
                font: control1.font
                leftPadding: 0
            }
            indicator: Canvas {
                x: control1.width - width - control1.rightPadding
                y: control1.topPadding + (control1.availableHeight - height) / 2
                width: 12
                height: 8
                Connections {
                    target: control1
                }
                contextType: "2d"
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control1.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
            }
            delegate: ItemDelegate {
                width: control1.width
                contentItem: Text {
                    color: "#000000"
                    text: control1.textRole
                          ? (Array.isArray(control1.model) ? modelData[control1.textRole] : model[control1.textRole])
                          : modelData
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    font: control1.font
                }
                highlighted: control1.highlightedIndex === index
            }
            model: ["Convert To", "JSON", "Full JSON", "XML", "CSV"]
        }
    }

    Text {
        id: curDateTxt
        x: 1200
        y: 8
        width: 74
        height: 20
        color: "#ffffff"
        text: qsTr("")
        font.pixelSize: 16
    }
    Text {
        id: clockText
        x: 1210
        y: 28
        width: 74
        height: 20
        color: "#ffffff"
        text: qsTr("")
        font.pixelSize: 16
    }
}
