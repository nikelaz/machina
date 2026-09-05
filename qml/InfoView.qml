import QtQuick
import QtQuick.Controls

Row {
  spacing: 13

  Column {
    spacing: 13

    Label { text: qsTr("OS:") }
    Label { text: qsTr("Hostname:") }
    Label { text: qsTr("Kernel:") }
    Label { text: qsTr("Architecture:") }
  }

  Column {
    spacing: 13

    Label { text: os }
    Label { text: hostname }
    Label { text: kernel }
    Label { text: arch }
  }
}

