//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department 
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QColorDialog>
#include "ui_MainWindow.h"
#include "glwidget.h"

class GLWidget;

//Create a window and load the components from generated code ui_MainWindow.h
class Window : public QDialog, public Ui::frmMain
{
	Q_OBJECT;

public:
	//Constructor 
	Window(QWidget *parent = 0);
	
private:
	//Member variable to hold the GLWidget instance
    //We need a reference to this
    GLWidget *m_glWidget;

    private slots:
        void openImage();
        void saveImage();        
        void makeImage();
        void aboutBut();
        void helpBut();

//protected:
   //    void  resizeEvent(QResizeEvent * );
   //      void wheelEvent(QWheelEvent *event);

};


#endif
