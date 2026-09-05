import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
  title: "System Information"
  visible: true
  width: 500
  height: 600

  Column {
    anchors.fill: parent
    anchors.margins: 13 
    spacing: 13

    TabBar {
      id: bar
      width: parent.width
      TabButton {
        text: qsTr("Info")
      }
      TabButton {
        text: qsTr("Processes")
      }
    }

    StackLayout {
      width: parent.width
      height: 40
      currentIndex: bar.currentIndex
      Item {
        id: infoTab 
        Label { text: "Info tab" }
      }
      Item {
        id: processesTab 
        Label { text: "Processes tab" }
      }
    }

    Row {
      spacing: 20

      Column {
        spacing: 10

        Label { text: "OS:" }
        Label { text: "Hostname:" }
        Label { text: "Kernel:" }
        Label { text: "Architecture:" }
      }

      Column {
        spacing: 10

        Label { text: os }
        Label { text: hostname }
        Label { text: kernel }
        Label { text: arch }
      }
    }

    ProcessList {
      width: parent.width
      height: parent.height - 120
    }
  }
}
