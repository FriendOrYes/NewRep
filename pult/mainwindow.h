#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <QToolButton>
#include <QMainWindow>
#include <QMovie>
#include <QPainter>
#include <memory>
#include <QVector>
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Update(const int &numberOfScrean);
    void UpdateAll();
    enum NumbersScreans
    {
        Camera1,
        Camera2,
        Camera3,
        Camera4,
    };
    void PaintFrame();
private slots:
    void SetTempOnLcdNumber();

    void ChackMagneticSensors();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

//    void on_currentScreanButton_clicked();

//    void on_currentScreanButton_2_clicked();

//    void on_currentScreanButton_3_clicked();

//    void on_currentScreanButton_4_clicked();

    void on_SensorTemp_clicked();

    void on_SensorTemp_2_clicked();

    void on_SensorPresentsRoom_2_clicked();

    void on_SensorPresentsRoom_clicked();

    void on_SensorMagneticWindow_clicked();

    void on_ServoMehWindow_clicked();

    void on_SensorMagneticWindow_2_clicked();

    void on_SensorMagnetic_3_clicked();

    void on_ServoMehDoor_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

protected:
       void paintEvent(QPaintEvent *event);
private:
    std::map<QString, std::shared_ptr<QMovie>> m_movies;
    std::map<int, QLabel*> m_screans;
    std::map<int, QString> m_camerasSeeNow;
    Ui::MainWindow *ui;
    int m_currentScrean;
    QPainter* m_painter;
    QTimer *m_tempTimer;
    QTimer *m_chackMagnaticTimer;
};

#endif // MAINWINDOW_H
