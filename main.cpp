#include <QApplication>
#include <QDesktopWidget>
#include "Model.hpp"
#include "View.hpp"
#include "MainWindow.hpp"

int main ( int argc, char** argv )
{
        QApplication app ( argc, argv );
        Model model;
        if( app.argc() == 2 ){
            std::string str(app.argv()[1]);
            model.openMesh( str );
        }

        View view ( model );

#if defined(Q_WS_MAC)
        // for Mac
        app.setWindowIcon ( QIcon ( ":/resources/meshview.icns" ) );
#else
        app.setWindowIcon ( QIcon ( ":/resources/meshview.ico" ) );
#endif

        MainWindow win ( model, view );

        win.show();
        return app.exec();
}
