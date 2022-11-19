

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import FlowView 1.0

FlowView {
    width: 1000
    height: 800
    flowTransitions: [
        FlowTransition {
            id: flowTransition
            to: presetsScreenItem
            from: homeScreenItem
        },
        FlowTransition {
            id: flowTransition1
            to: customScreenItem
            from: homeScreenItem
        },
        FlowTransition {
            id: flowTransition2
            to: homeScreenItem
            from: presetsScreenItem
        },
        FlowTransition {
            id: flowTransition3
            to: customScreenItem
            from: presetsScreenItem
        },
        FlowTransition {
            id: flowTransition4
            to: homeScreenItem
            from: customScreenItem
        },
        FlowTransition {
            id: flowTransition5
            to: presetsScreenItem
            from: customScreenItem
        },
        FlowTransition {
            id: flowTransition6
            to: homeScreenItem
            from: softwareScreenItem
        },
        FlowTransition {
            id: flowTransition7
            to: presetsScreenItem
            from: softwareScreenItem
        },
        FlowTransition {
            id: flowTransition8
            to: customScreenItem
            from: softwareScreenItem
        },
        FlowTransition {
            id: flowTransition9
            to: softwareScreenItem
            from: homeScreenItem
        },
        FlowTransition {
            id: flowTransition10
            to: softwareScreenItem
            from: presetsScreenItem
        },
        FlowTransition {
            id: flowTransition11
            to: softwareScreenItem
            from: customScreenItem
        }
    ]

    defaultTransition: FlowTransition {
        id: defaultTransition
    }

    HomeScreenItem {
        id: homeScreenItem

        FlowActionArea {
            target: flowTransition
            x: 8
            y: 80
            width: 232
            height: 50
        }

        FlowActionArea {
            target: flowTransition1
            x: 8
            y: 142
            width: 232
            height: 50
        }

        FlowActionArea {
            target: flowTransition9
            x: 8
            y: 198
            width: 232
            height: 52
        }
    }

    PresetsScreenItem {
        id: presetsScreenItem

        FlowActionArea {
            target: flowTransition2
            x: 8
            y: 21
            width: 236
            height: 51
        }

        FlowActionArea {
            target: flowTransition3
            x: 8
            y: 140
            width: 236
            height: 47
        }

        FlowActionArea {
            target: flowTransition10
            x: 8
            y: 198
            width: 236
            height: 51
        }
    }

    CustomScreenItem {
        id: customScreenItem

        FlowActionArea {
            target: flowTransition4
            x: 8
            y: 19
            width: 234
            height: 52
        }

        FlowActionArea {
            target: flowTransition5
            x: 8
            y: 79
            width: 234
            height: 52
        }

        FlowActionArea {
            target: flowTransition11
            x: 8
            y: 197
            width: 234
            height: 55
        }
    }

    SoftwareScreenItem {
        id: softwareScreenItem

        FlowActionArea {
            target: flowTransition6
            x: 8
            y: 18
            width: 234
            height: 54
        }

        FlowActionArea {
            target: flowTransition7
            x: 8
            y: 78
            width: 234
            height: 53
        }

        FlowActionArea {
            target: flowTransition8
            x: 8
            y: 137
            width: 234
            height: 55
        }
    }
}

/*##^##
Designer {
    D{i:0;areaColor:"#ff6e00";blockColor:"#ff00e7";formeditorZoom:0.125;height:10000;transitionColor:"#0001ff";width:10000}
D{i:14;flowX:390.20446440222213;flowY:268.60223220111106}D{i:18;flowX:1701.8401796200005;flowY:1582.6022322011108}
D{i:22;flowX:192.8736626366673;flowY:1866.0446440222227}D{i:26;flowX:2560;flowY:625.4794611399989}
}
##^##*/

