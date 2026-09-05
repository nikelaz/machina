import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
  id: window
  title: "System Information"
  visible: true
  width: 500
  height: 600

  Column {
    anchors.fill: parent
    anchors.margins: 13 

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
      height: parent.height - bar.height - 26 
      currentIndex: bar.currentIndex
      Item {
        id: infoTab 
        Rectangle {
          anchors.fill: parent
          color: window.palette.base
          border.width: 1
          border.color: window.palette.base.lighter(1.8)

          Column {
            anchors.fill: parent
            anchors.margins: 8

            InfoView {}
          }
        }
      }
      Item {
        id: processesTab 

        Rectangle {
          anchors.fill: parent
          color: window.palette.base
          border.width: 1
          border.color: window.palette.base.lighter(1.8)

          Column {
            anchors.fill: parent
            anchors.margins: 8 

            ProcessList {
              width: parent.width
              height: parent.height
            }
          }
        }
      }
    }
  }
}
