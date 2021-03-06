﻿import QtQuick 2.11
import QtQuick.Dialogs 1.3
import myqml.qmlsigleton 1.0

Rectangle {
    id : _id_root
    color: Qt.rgba(0.2,0.35,0.35,1)
    visible: true
    width: 512
    height: 640

    ColorDialog {
        id: _id_colorDialog
        title: qsTr( "Please choose a color" )
        onAccepted: {
            QmlSigleton.myColor = _id_colorDialog.color ;
            _id_colorDialog.visible = false ;
        }
        onRejected: {
            _id_colorDialog.visible = false ;
        }
        Component.onCompleted: {
            _id_colorDialog.color = QmlSigleton.myColor ;
        }
    }

    Text{
        z : 12 ;
        text : qsTr( "点我变色！" )
        font.pixelSize: 64 ;
        anchors.centerIn: parent
    }

    MouseArea{
        anchors.fill: parent ;
        acceptedButtons: Qt.AllButtons;
        onClicked: {
            _id_colorDialog.visible = true ;
        }
    }

    Rectangle{
        color: QmlSigleton.myColor ;
        anchors.left : parent.left ;
        anchors.right : parent.horizontalCenter;
        anchors.top : parent.top ;
        anchors.bottom: parent.verticalCenter;
        anchors.margins: 10 ;
    }

    Rectangle{
        color: QmlSigleton.myColor ;
        anchors.left: parent.horizontalCenter;
        anchors.right:parent.right ;
        anchors.top : parent.top ;
        anchors.bottom: parent.verticalCenter;
        anchors.margins: 10 ;
    }

    Rectangle{
        color: QmlSigleton.myColor ;
        anchors.left : parent.left ;
        anchors.right : parent.horizontalCenter ;
        anchors.top : parent.verticalCenter;
        anchors.bottom: parent.bottom ;
        anchors.margins: 10 ;
    }

    Rectangle{
        color: QmlSigleton.myColor ;
        anchors.left: parent.horizontalCenter ;
        anchors.right:parent.right ;
        anchors.top : parent.verticalCenter;
        anchors.bottom: parent.bottom ;
        anchors.margins: 10 ;
    }

}/*Window*/














