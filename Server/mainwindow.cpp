#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    leftScene = new QGraphicsScene;
    rightScene = new QGraphicsScene;


    size = new QLabel;



    info = NULL;

    leftScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->leftGraphicsView->setScene(leftScene);
    rightScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->rightGraphicsView->setScene(rightScene);

    ui->statusBar->addPermanentWidget(size);


    createAction();
    createToolBar();


    setActionStatus(false);
    setWindowTitle("ImageQt");
    ui->actionEnglish->setEnabled(false);
}

void MainWindow::createToolBar()
{
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionClose);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionRestore);
    ui->toolBar->addAction(ui->actionHistogram);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionChinese);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(finalEx);
}

void MainWindow::createAction()
{
    finalEx = new QAction(QIcon(":/img/src/Final_Cut_Pro_X_96px_1134672_easyicon.net.png"), tr("Final"), this);
    connect(finalEx, SIGNAL(triggered(bool)), this, SLOT(on_actionFinal_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;

    if (leftScene)
    {
        delete leftScene;
        leftScene = NULL;
    }

    if (size)
    {
        delete size;
        size = NULL;
    }


    //add
    if (rightScene)
    {
        delete leftScene;
        leftScene = NULL;
    }

}

/******************************************************************************
 *                Update and repaint right scene
 *****************************************************************************/
void MainWindow::updateRightImage(QPixmap &pixmap)
{

    rightPixmapItem->setPixmap(pixmap);
    rightScene->setSceneRect(QRectF(pixmap.rect()));

       qDebug() << "repaintRightScene"  << rightScene->items().count();
}

/******************************************************************************
 *                      Clean image of both canvas
 *****************************************************************************/
void MainWindow::cleanImage()
{
    leftScene->clear();
    ui->leftGraphicsView->resetTransform();

    rightScene->clear();
    ui->rightGraphicsView->resetTransform();


    if (size)
    {
        delete size;
        size = new QLabel;
        ui->statusBar->addPermanentWidget(size);
    }



    this->setWindowTitle(WINDOW_TITLE);
    setActionStatus(false);
}

void MainWindow::setActionStatus(bool status)
{
    ui->actionPrewitt->setEnabled(status);
    ui->actionContour_extraction->setEnabled(status);
    ui->actionEdge_following->setEnabled(status);
    // sharpen
    ui->actionLaplace->setEnabled(status);
    ui->actionSobel->setEnabled(status);
    //ui->actionEdge_Detection->setEnabled(status);
    // Blur
    ui->actionSimple->setEnabled(status);
    ui->actionGauss->setEnabled(status);
    ui->actionMeida_Filter->setEnabled(status);
    // Grey Transform
    ui->actionBinaryzation->setEnabled(status);
    ui->actionStretch_transformation->setEnabled(status);
    ui->actionExp_transfrom->setEnabled(status);
    ui->actionTwo_thresholds_transform->setEnabled(status);
    ui->actionPower_transformation->setEnabled(status);
    ui->actionLogarithm_grey_level_transformation->setEnabled(status);
    ui->actionSave->setEnabled(status);
    ui->actionClose->setEnabled(status);
    ui->actionSave_As->setEnabled(status);

    ui->actionCool->setEnabled(status);
    ui->actionWarm->setEnabled(status);
    ui->actionFlower_frame->setEnabled(status);
    ui->actionGrayscale->setEnabled(status);
    ui->actionHistogram->setEnabled(status);
    ui->actionHorizontal->setEnabled(status);
    ui->actionLeft->setEnabled(status);
    ui->actionLinear_level_transformation->setEnabled(status);
    ui->actionMetal->setEnabled(status);
    ui->actionMovie_frame->setEnabled(status);
    ui->actionNormal->setEnabled(status);
    ui->actionRestore->setEnabled(status);
    ui->actionVertical->setEnabled(status);
    ui->actionClassic_frame->setEnabled(status);
    ui->actionAdjust_brightness->setEnabled(status);
    ui->actionRight->setEnabled(status);
    ui->zoomAction->setEnabled(status);
}


void MainWindow::receiveGaussianFactor(int radius, double sigma)
{
    GaussianBlur *blur = new GaussianBlur(radius, sigma);

    QPixmap rightImage = rightPixmapItem->pixmap();

    QImage newImage = blur->BlurImage(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}


/******************************************************************************
 *                 Open a image file and show it on canvas
 *****************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
        // Automatically detects the current user's home directory and waits the user to select an image
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                 tr("All Files (*);;"
                                                    "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                    "Image BPM (*.bpm);;"
                                                    "Image GIF (*.gif);;"
                                                    "Image JPG (*.jpg);;"
                                                    "Image JPEG (*.jpeg);;"
                                                    "Image PNG (*.png);;"
                                                    "Image PPM (*.ppm);;"
                                                    "Image XBM (*.xbm);;"
                                                    "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL),
                                  tr("Unable to open image."));
            return;
        }

        // Delete previous image
        cleanImage();

        // Upload image
        info = new QFileInfo(imagePath);

        // Left canva (uploaded image)
        QPixmap leftPixmap(imagePath);
        leftPixmapItem = leftScene->addPixmap(leftPixmap);
        leftScene->setSceneRect(QRectF(leftPixmap.rect()));

        // Right canva (edited image)
        QPixmap rightPixmap(imagePath);
        rightPixmapItem = rightScene->addPixmap(rightPixmap);
        rightScene->setSceneRect(QRectF(rightPixmap.rect()));

        qDebug()<<"depth:"<<rightPixmap.depth();
        qDebug()<<"hasAlpha:"<<rightPixmap.hasAlpha();

        // settings
        this->setWindowTitle(info->fileName() + " - ImageQt");

        setActionStatus(true);

        size->setText(QString::number(leftPixmapItem->pixmap().width())
                      + " x " + QString::number(leftPixmapItem->pixmap().height()));
    }
}

/******************************************************************************
 *                      Clean image of both canvas
 *****************************************************************************/
void MainWindow::on_actionClose_triggered()
{
    cleanImage();
}

void MainWindow::on_actionSave_triggered()
{

}

/******************************************************************************
 *                        Action for "Save as..."
 *****************************************************************************/
void MainWindow::on_actionSave_As_triggered()
{

    QString newPath = QFileDialog::getSaveFileName(this, tr("Save image"), QString(),
            tr("All files (*);;"
               "Image BPM (*.bpm);;"
               "Image GIF (*.gif);;"
               "Image JPG (*.jpg);;"
               "Image JPEG (*.jpeg);;"
               "Image PNG (*.png);;"
               "Image PPM (*.ppm);;"
               "Image XBM (*.xbm);;"
               "Image XPM (*.xpm);;"));

    if (!newPath.isEmpty()) {

        QFile file(newPath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("Unable to save image."));
            return;
        }

        //Save image to new path
        rightPixmapItem->pixmap().save(newPath);
//        rightImage->save(newPath);
    }
}

/******************************************************************************
 *                        Exit program
 *****************************************************************************/
void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}




/******************************************************************************
 *                              Greyscale
 *****************************************************************************/
void MainWindow::on_actionGrayscale_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::GreyScale(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}



/******************************************************************************
 *                  Adjust the image size to fit the window
 *****************************************************************************/
void MainWindow::on_actionAdjust_triggered()
{
    // Left image
    int height = leftPixmapItem->pixmap().height();
    int width = leftPixmapItem->pixmap().width();
    int max_height = ui->leftGraphicsView->height();
    int max_width = ui->leftGraphicsView->width();
    int size,max_size,fact=0;
    double val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->leftGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->leftGraphicsView->setFactor(fact+1);
    }

    ui->leftGraphicsView->scale(val,val);


    // Right image
    height = leftPixmapItem->pixmap().height();
    width = leftPixmapItem->pixmap().width();
    max_height = ui->rightGraphicsView->height();
    max_width = ui->rightGraphicsView->width();
    size = max_size = fact = 0;
    val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->rightGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->rightGraphicsView->setFactor(fact+1);
    }

    ui->rightGraphicsView->scale(val,val);


}

/******************************************************************************
 *           Restore the image, both original size and rotation
 *****************************************************************************/
void MainWindow::on_actionRestore_triggered()
{
    on_actionNormal_triggered();

}

/******************************************************************************
 *                             Simple Smoothing
 *****************************************************************************/
void MainWindow::on_actionSimple_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::SimpleSmooth(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                    Gaussian Smoothing (Gaussian Blur)
 *****************************************************************************/
void MainWindow::on_actionGauss_triggered()
{
    GaussianBlurDialog dialog;
    connect(&dialog, SIGNAL(sendData(int, double)), this,
            SLOT(receiveGaussianFactor(int, double)));

    dialog.exec();
}


/******************************************************************************
 *                              Rotate Left
 *****************************************************************************/
void MainWindow::on_actionLeft_triggered()
{

    bool ok;
    int factor = QInputDialog::getInt(this, tr("旋转"), "请输入要旋转的角度",0,-360,360,10,&ok);
    if (ok)
    {
        if (factor != 0)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            QImage *imgRotate = new QImage;
            QMatrix matrix;
            matrix.rotate(factor);
            *imgRotate = rightImage.toImage().transformed(matrix);
            QPixmap newPixmap;
            newPixmap = QPixmap::fromImage(*imgRotate);
            updateRightImage(newPixmap);
        }
        else
        {
            return;
        }
    }

}

/******************************************************************************
 *                              Rotate Right
 *****************************************************************************/
void MainWindow::on_actionRight_triggered()
{
    //ui->rightGraphicsView->rotate(90);
    QPixmap rightImage = rightPixmapItem->pixmap();

    QImage *imgRotate = new QImage;
    QMatrix matrix;
    matrix.rotate(90);
    *imgRotate = rightImage.toImage().transformed(matrix);
    QPixmap newPixmap;
    newPixmap = QPixmap::fromImage(*imgRotate);
    updateRightImage(newPixmap);
}

/******************************************************************************
 *                             Zoom triggered
 *****************************************************************************/
void MainWindow::on_zoomAction_triggered()
{

    bool ok;
    int factor = QInputDialog::getInt(this, tr("Zoom"), "Input a value for zoom ratio(%)",100,10,1000,10,&ok);
    if (ok)
    {
        if (factor != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            int cur_width = rightImage.width();
            int cur_height = rightImage.height();

            QPixmap newPixmap = rightImage.scaled(cur_width*factor/100, cur_height*factor/100);

            updateRightImage(newPixmap);
        }
        else
        {
            return;
        }
    }

}

/******************************************************************************
 *                          Flip Horizontally
 *****************************************************************************/
void MainWindow::on_actionHorizontal_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Horizontal(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                          Flip Vertically
 *****************************************************************************/
void MainWindow::on_actionVertical_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Vertical(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}


/******************************************************************************
 *                            Brighness
 *****************************************************************************/
void MainWindow::on_actionAdjust_brightness_triggered()
{
    bool ok;
    int delta = QInputDialog::getInt(this,
                                     tr("Brightness"),
                                     "Input a value for brightness(+/-)",
                                     0,-1000,1000,10,&ok);
    if (ok)
    {
        if (delta != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            QImage newImage = Tools::Brightness(delta, rightImage.toImage());
            rightImage.convertFromImage(newImage);

            updateRightImage(rightImage);
        }
        else
        {
            return;
        }
    }

}


/******************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_actionNormal_triggered()
{
    QPixmap leftImage = leftPixmapItem->pixmap();
   updateRightImage(leftImage);
   ui->rightGraphicsView->resetTransform();
}

/******************************************************************************
 *                   Get the current user's home directory
 *****************************************************************************/
QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}

void MainWindow::on_actionT_triggered()
{
    QLabel* l = new QLabel;
    if (!rightPixmapItem->pixmap().isNull()) {
        qDebug() << "hello";
        l->setPixmap(rightPixmapItem->pixmap());
        l->show();
    }
}

void MainWindow::on_actionConnected_domain_triggered()
{

}
