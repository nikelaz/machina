import QtQuick
import QtQuick.Controls

Column {
  id: root
  spacing: 20

  Rectangle {
    width: parent.width
    height: 25
    color: palette.window

    Row {
      anchors.fill: parent
      anchors.margins: 5

      Label {
        width: 80
        text: "PID"
        font.bold: true
      }

      Label {
        width: parent.width - 80
        text: "Name"
        font.bold: true
      }
    }
  }

  ListView {
    width: parent.width
    height: parent.height - 45
    clip: true
    boundsBehavior: Flickable.StopAtBounds
    model: processModel

    delegate: Row {
      width: ListView.view.width
      height: 25

      Label {
        width: 80
        text: model.pid
        elide: Text.ElideRight
      }

      Label {
        width: parent.width - 80
        text: model.name
        elide: Text.ElideRight
      }
    }
  }
}
