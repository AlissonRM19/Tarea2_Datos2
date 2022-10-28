#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QTranslator>
#include "graphicsview.h"
#include "dialog_gaussianblur.h"
#include "tools.h"
#include "gaussianblur.h"

#define WINDOW_TITLE    "ImageQt"
#define WINDOW_CRITICAL "Error - ImageQt"
#define WINDOW_WARNING  "Notice - ImageQt"
#define WINDOW_ABOUT    "About - ImageQt"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateRightImage(QPixmap &pixmap);
    void cleanImage();

    void setActionStatus(bool);
    void createToolBar();
    void createAction();

private slots:

    void receiveGaussianFactor(int radius, double sigma);

    // On action triggered
    void on_actionOpen_triggered();
    void on_actionClose_triggered();        // Clear both left and right Scene
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();      // Save as
    void on_actionExit_triggered();         // Exit the program
    void on_actionGrayscale_triggered();    // Grayscale
    void on_actionAdjust_brightness_triggered();
    void on_actionRestore_triggered();      // Restore to the original image
    void on_actionSimple_triggered();
    void on_actionGauss_triggered();
    void on_actionLeft_triggered();         // Rotate Left: 90^
    void on_actionRight_triggered();        // Rotate Right:90^
    void on_zoomAction_triggered();         // Zoom action with dialog
    void on_actionHorizontal_triggered();
    void on_actionVertical_triggered();
    void on_actionAdjust_triggered();       // Adjust to fit the window size
    void on_actionNormal_triggered();       // Restore the right image to original size
    void on_actionT_triggered();
    void on_actionConnected_domain_triggered();

private:
    QAction *finalEx;

    Ui::MainWindow  *ui;
    QGraphicsScene  *leftScene;
    QGraphicsScene  *rightScene;
    QGraphicsPixmapItem* leftPixmapItem;
    QGraphicsPixmapItem* rightPixmapItem;

    QLabel          *size;

    QFileInfo *info;

    QString getUserName();
    QString getUserPath();
};

#endif // MAINWINDOW_H
