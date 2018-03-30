#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "jsonrestlistmodel.h"
#include "src/api/models/coolfeedmodel.h"


int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    //api and models
    QtRestRocketAPI::declareQML();
    CoolFeedModel::declareQML();
    JsonRestListModel::declareQML(); // FIXME: restricted name in harbour

    return SailfishApp::main(argc, argv);
}
