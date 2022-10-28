#include "tools.h"

#define min2(a,b) (a)<(b)?(a):(a)
#define min(a,b,c) (min2(a,b))<(c)?(min2(a,b)):(c)


/*****************************************************************************
 *                           Greyscale
 * **************************************************************************/
QImage Tools::GreyScale(QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                   QImage::Format_ARGB32);
    QColor oldColor;

    for (int x=0; x<newImage->width(); x++) {
        for (int y=0; y<newImage->height(); y++) {
            oldColor = QColor(origin.pixel(x,y));
            int average = (oldColor.red()*299+oldColor.green()*587+oldColor.blue()*114+500)/1000;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }

    return *newImage;

}

/*****************************************************************************
 *                          Adjust image brightness
 * **************************************************************************/
QImage Tools::Brightness(int delta, QImage origin)
{
    QImage *newImage = new QImage(origin.width(), origin.height(),
                                  QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;

    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue() + delta;

            // Check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return *newImage;
}

/*****************************************************************************
 *                                   Flip
 * **************************************************************************/
QImage Tools::Horizontal(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(newImage->width()-x-1,y, qRgb(r,g,b));

        }
    }
    return *newImage;
}

QImage Tools::Vertical(const QImage &origin)
{
    QImage *newImage = new QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int x=0; x<newImage->width(); x++)
    {
        for (int y=0; y<newImage->height(); y++)
        {
            tmpColor = QColor(origin.pixel(x, y));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();

            newImage->setPixel(x, newImage->height()-y-1, qRgb(r,g,b));

        }
    }
    return *newImage;
}





/*****************************************************************************
 *                            Draw Frame
 * **************************************************************************/
QImage Tools::DrawFrame(QImage origin, QImage &frame)
{
    QImage *newImage = new QImage(origin);
    QPainter painter;

    int width = origin.width();
    int height = origin.height();

    QImage tmpFrame = frame.scaled(QSize(width, height));

    painter.begin(newImage);
    painter.drawImage(0, 0, tmpFrame);
    painter.end();

    return *newImage;

}

/*****************************************************************************
 *                               Simple Smoothing
 * **************************************************************************/
QImage Tools::SimpleSmooth(const QImage &origin)
{
    QImage *newImage = new QImage(origin);

    int kernel[5][5] = {
        {0,0,1,0,0},
        {0,1,3,1,0},
        {1,3,7,3,1},
        {0,1,3,1,0},
        {0,0,1,0,0}
    };
    int kernelSize = 5;
    int sumKernel=27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-kernelSize/2; x++)
    {
        for (int y=kernelSize/2; y<newImage->height()-kernelSize/2; y++)
        {
            r = g = b = 0;
            for (int i=-kernelSize/2; i<=kernelSize/2; i++)
            {
                for (int j=-kernelSize/2; j<=kernelSize/2; j++)
                {
                    color = QColor(origin.pixel(x+i,y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];

                }
            }
            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y,qRgb(r,g,b));

        }
    }
    return *newImage;
}

/*****************************************************************************
 *                                  Gaussian Smoothing/Gaussian Blur
 * **************************************************************************/
QImage Tools::GaussianSmoothing(const QImage &origin, int radius, double sigma)
{

    GaussianBlur *blur = new GaussianBlur(radius, sigma);
    QImage newImage = blur->BlurImage(origin);

    return newImage;
}

