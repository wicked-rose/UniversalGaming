

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
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.125;height:10000;width:10000}D{i:10}D{i:8;flowX:364.5295141618784;flowY:266.88455448038576}
D{i:11;flowX:1523.399553590217;flowY:1114.520758896631}D{i:16}D{i:14;flowX:404.1168856476917;flowY:1993.6780115780768}
}
##^##*/

