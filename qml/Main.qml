import QtQuick
import QtQuick.Controls

ApplicationWindow {
  title: "System Information"
  visible: true
  width: 400
  height: 300

  Row {
    spacing: 20;
    padding: 20;

    Column {
      spacing: 20;

      Label {
        text: "OS:"
      }

      Label {
        text: "Hostname:"
      }

      Label {
        text: "Kernel:" 
      }

      Label {
        text: "Architecture:" 
      }
    }

    Column {
      spacing: 20;

      Label {
        text: os
      }

      Label {
        text: hostname
      }

      Label {
        text: kernel
      }

      Label {
        text: arch
      }
    }
  }
}
