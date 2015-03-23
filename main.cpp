//-------------------------------------------------------------------------------------------
//   Painting with Flowsnakes
//	 by
//   Brian Wyvill (brianwyvill@gmail.com)
//   Experimental Software this is version zero hacked together
//   to get something working.
//
//  The Flowsnake is drawn in order into a vertex array see:
//  see    void GLWidget::paintGL()
//  the background hexagons are treated separately and drawn by old fashioned
//  direct mode - bu thgey can be turned off in the UI.
//  Any questions email me - Brian
//  as of 2013 I am actively working on the next version.
//-------------------------------------------------------------------------------------------
#include <QApplication>
#include "window.h"
#include "glwidget.h"

//Main is needed in all win32 applications
int main(int argc, char* argv[])
{
    //Instance of new application pass arguments received from commandline
    QApplication app(argc, argv);

    //Instead of creating our GUI components ourselves. We will visually design
    //Everything then we subclass
    Window appWindow;

    //Show application MainWindow
    appWindow.show();

    //Execute app
    app.exec();

    return 0;
}
