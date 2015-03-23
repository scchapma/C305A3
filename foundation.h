#ifndef foundation_h
#define foundation_h

#define EPSILON 0.00001
#define SEP << " " <<
#define NL  << "\n"

using namespace std;

// I can't seem to make the -LANG:bool=ON switch work so :

//---------------------------------------------------------------------------
// if C++ type `bool' is not defined with compiler being used ...

#ifdef NOBOOL
typedef int bool;

#define true  1
#define false 0
#endif

#define SEP << " " <<
#define NL  << "\n"
//---------------------------------------------------------------------------
#include "version.h"
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
#include <qmessagebox.h>
#include <QPainter>
#include <QFile>
#include <stdio.h>
#include <QEvent>
#include <qfiledialog.h>



//const  double   M_PI = 3.1415925;
const  double pib5 = M_PI/5.0;
const  double torr = sin (2.0*pib5) / sin(pib5);
const  int  X = 0;
const  int  Y = 1;
const  int  Z = 2;

const double svth=1.0/7.0;
const double todeg = 180.0/M_PI;
const double r3 = sqrt(3.0);
const double r7 = sqrt(7.0);
const double r32= sqrt(3.0)/2.0;
const double ir7=1.0/sqrt(7.0);
const double ir72=0.5/sqrt(7.0);



class iostream;
#endif

