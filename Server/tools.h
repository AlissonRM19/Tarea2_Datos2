/****************************************************************************
 *                              Basic tools:
 * greyscale, brightness, flip, wand or cool ...
 * *************************************************************************/

#ifndef TOOLS_H
#define TOOLS_H


#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include "gaussianblur.h"


namespace Tools {
QImage GreyScale(QImage origin);
QImage DrawFrame(QImage origin, QImage &frame);
QImage Brightness(int delta, QImage origin);
QImage Horizontal(const QImage &origin);
QImage Vertical(const QImage &origin);
QImage SimpleSmooth(const QImage &origin);
QImage GaussianSmoothing(const QImage &origin, int radius, double sigma);

}




#endif // TOOLS_H
