import QtQuick
import QtQuick.Controls

ApplicationWindow {
  title: "System Information"
  visible: true
  width: 400
  height: 300

  Column {
    spacing: 20;
    padding: 20;

    Label {
      text: "OS: " + os
    }

    Label {
      text: "Hostname: " + hostname
    }

    Label {
      text: "Kernel: " + kernel
    }

    Label {
      text: "Architecture: " + arch
    }
  }
}
