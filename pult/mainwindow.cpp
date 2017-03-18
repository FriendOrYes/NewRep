#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGradient>
#include <QBitmap>
#include <random>
#include <time.h>
//#include <QMovie>
 static const QSize resultSize(200, 200);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentScrean(Camera1)
{
    ui->setupUi(this);
//    QPicture Picture;
//    Picture.load(":/image.jpg");
//    ui->currentScreanButton->hide();
//    ui->currentScreanButton_2->hide();
//    ui->currentScreanButton_3->hide();
    //    ui->currentScreanButton_4->hide();

    m_tempTimer = new QTimer(this);
    m_tempTimer->start(700);

    m_chackMagnaticTimer = new QTimer(this);
    m_chackMagnaticTimer->start(1000);

    connect(m_tempTimer, SIGNAL(timeout()), this, SLOT(SetTempOnLcdNumber()));
    //connect(m_tempTimer, SIGNAL(timeout()), m_chackMagnaticTimer, SLOT(start()));
    connect(m_chackMagnaticTimer, SIGNAL(timeout()), this, SLOT(ChackMagneticSensors()));

    m_movies["camera 1"] = std::make_shared<QMovie>("gif.gif");
    m_movies["camera 2"] = std::make_shared<QMovie>("animation/1.gif");
    m_movies["camera 3"] = std::make_shared<QMovie>("animation/2.gif");
    m_movies["camera 4"] = std::make_shared<QMovie>("animation/3.gif");

    m_movies["camera 1"]->setScaledSize(ui->label->size());
    m_movies["camera 2"]->setScaledSize(ui->label_2->size());
    m_movies["camera 3"]->setScaledSize(ui->label_3->size());
    m_movies["camera 4"]->setScaledSize(ui->label_4->size());

    ui->label->setMovie(m_movies["camera 1"].get());
    ui->label_2->setMovie(m_movies["camera 2"].get());
    ui->label_3->setMovie(m_movies["camera 3"].get());
    ui->label_4->setMovie(m_movies["camera 4"].get());

    m_movies["camera 1"]->start();
    m_movies["camera 2"]->start();
    m_movies["camera 3"]->start();
    m_movies["camera 4"]->start();

   // m_movies["camera 4"]->stop();
    m_screans[Camera1] = ui->label;
    m_screans[Camera2] = ui->label_2;
    m_screans[Camera3] = ui->label_3;
    m_screans[Camera4] = ui->label_4;

    m_camerasSeeNow[Camera1] = "camera 1";
    m_camerasSeeNow[Camera2] = "camera 2";
    m_camerasSeeNow[Camera3] = "camera 3";
    m_camerasSeeNow[Camera4] = "camera 4";

    PaintFrame();
//    ui->label->setPixmap(QString("gif.gif"));
    //    m_screans["camera 1"] =  std::make_shared<QLabel>(ui->label);
    //    m_screans["camera 2"] =  std::make_shared<QLabel>(ui->label_2);
    //    m_screans["camera 3"] =  std::make_shared<QLabel>(ui->label_3);
    //    m_screans["camera 4"] =  std::make_shared<QLabel>(ui->label_4);

    //m_screans["camera 1"]->setMovie(m_movies["camera 1"]/*.get()*/);
    //m_screans["camera 2"]->setMovie(m_movies["camera 2"]/*.get()*/);
    //m_screans["camera 3"]->setMovie(m_movies["camera 3"]/*.get()*/);
    //m_screans["camera 4"]->setMovie(m_movies["camera 4"]/*.get()*/);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update(const int&  numberOfScrean)
{
    m_movies[m_camerasSeeNow[numberOfScrean]]->setScaledSize(m_screans[numberOfScrean]->size());
    m_screans[numberOfScrean]->setMovie(m_movies[m_camerasSeeNow[numberOfScrean]].get());
    m_movies[m_camerasSeeNow[numberOfScrean]]->start();
}

void MainWindow::UpdateAll()
{
    qDebug() << m_camerasSeeNow.size();
    for(int i = 0; i < m_camerasSeeNow.size(); ++i)
    {
        //qDebug() << m_camerasSeeNow[i];
        m_movies[m_camerasSeeNow[i]]->setScaledSize(m_screans[i]->size());
        //qDebug() << m_camerasSeeNow[i];
        m_screans[i] -> setMovie(m_movies[m_camerasSeeNow[i]].get());
        //qDebug() << m_camerasSeeNow[i];
        m_movies[m_camerasSeeNow[i]]->start();
        qDebug() << m_camerasSeeNow[i];
    }
}

void MainWindow::PaintFrame()
{
//    QBitmap bitmap;
//    bitmap.load("window.png");
    ui->windowLabel_2->setPixmap(QPixmap("window.png"));
    ui->windowLabel_3->setPixmap(QPixmap("window.png"));
    ui->windowLabel_4->setPixmap(QPixmap("window.png"));


    QPainter paint;
    QPixmap graph(ui->label_5->size());
    QPolygon polygon;

    const int radiusOfPaintingSensors = 11;

    //painting float walls
    polygon << QPoint(75, ui->label_5->height() - 75);//1.
    polygon << QPoint(75, ui->label_5->height() - 206);//2|
    polygon << QPoint(185, ui->label_5->height() - 206);//3|-
    polygon << QPoint(75, ui->label_5->height() - 206);//4|--
    polygon << QPoint(75, 75);//|--|
    polygon << QPoint(ui->label_5->width() - 75,  75);//|--|-
    polygon << QPoint(ui->label_5->width() - 75,  175);//|--|-|
    polygon << QPoint(ui->label_5->width() - 200,  175);//|--|-|-
    polygon << QPoint(ui->label_5->width() - 150,  175);//|--|-|--
    polygon << QPoint(ui->label_5->width() - 150, ui->label_5->height() - 75);//|--|-|--|



    QRadialGradient radialGrad(QPointF(15, 15), 15);
    radialGrad.setColorAt(0, Qt::blue);
    //radialGrad.setColorAt(1, Qt::white);

    //painting frame
    paint.begin(&graph); // запускаем отрисовку
    paint.eraseRect(25, 25, ui->label_5->width() - 50, ui->label_5->height() - 50); // очищаем рисунок
    paint.setPen(QPen(Qt::blue, 10, Qt::SolidLine));
    paint.drawRect(25, 25, ui->label_5->width() - 50, ui->label_5->height() - 50);
    paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    paint.drawPolygon(polygon);

    //painting angle in ractangle
    paint.setBrush(QBrush(radialGrad));

    paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    paint.drawEllipse(15, 15, 25, 25);
    paint.drawEllipse(ui->label_5->width() - 40, 15, 25, 25);
    paint.drawEllipse(0 + 15, ui->label_5->height() - 40, 25, 25);
    paint.drawEllipse(ui->label_5->width() - 40, ui->label_5->height() - 40, 25, 25);



    //painting temp sensors
    if(ui->checkBox->checkState())
    {
        //painting magnetic sensors
        paint.drawEllipse(ui->SensorMagneticWindow->x() - ui->label_5->x(), ui->SensorMagneticWindow->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->SensorMagneticWindow_2->x() - ui->label_5->x(), ui->SensorMagneticWindow_2->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->SensorMagnetic_3->x() - ui->label_5->x(), ui->SensorMagnetic_3->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        //painting servo Meh
        radialGrad.setColorAt(0, Qt::darkGray);
        paint.setBrush(QBrush(radialGrad));

        paint.drawEllipse(ui->ServoMehDoor->x() - ui->label_5->x(), ui->ServoMehDoor->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->ServoMehWindow->x() - ui->label_5->x(), ui->ServoMehWindow->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->ServoMehWindow_2->x() - ui->label_5->x(), ui->ServoMehWindow_2->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
    }

    if(ui->checkBox_2->checkState())
    {
        //painting temp sensors
        radialGrad.setColorAt(0, Qt::red);
        paint.setBrush(QBrush(radialGrad));

        paint.drawEllipse(ui->SensorTemp->x() - ui->label_5->x(), ui->SensorTemp->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->SensorTemp_2->x() - ui->label_5->x(), ui->SensorTemp_2->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
    }

    if(ui->checkBox_3->checkState())
    {
        //painting present sensors
        radialGrad.setColorAt(0, Qt::green);
        paint.setBrush(QBrush(radialGrad));

        paint.drawEllipse(ui->SensorPresentsRoom->x() - ui->label_5->x(), ui->SensorPresentsRoom->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);
        paint.drawEllipse(ui->SensorPresentsRoom_2->x() - ui->label_5->x(), ui->SensorPresentsRoom_2->y() - ui->label_5->y(),
                          radiusOfPaintingSensors, radiusOfPaintingSensors);


    }

    ui->label_5->setPixmap(graph);
    paint.end();
}

void MainWindow::SetTempOnLcdNumber()
{
    if(ui->flameIvant->checkState())
    {
        ui->lcdNumber->display(rand()%10 * 1.0/ 10 + 50);
        ui->lcdNumber_2->display(rand()%10 * 1.0/ 10 + 50);
    }
    else
    {
        ui->lcdNumber->display(rand()%10 * 1.0/ 10 + 28);
        ui->lcdNumber_2->display(rand()%10 * 1.0/ 10 + 28);
    }

    if(ui->checkBox_2->checkState())
    {
        qDebug() << ui->lcdNumber_2->value();
        if(ui->lcdNumber->value() > 49 || ui->lcdNumber_2->value() > 49)
        {
            ui->lineEdit->setText("flame!");
            ui->textEdit->setText("Firefighters are caused, Anti-fire system works");
        }
    }
}

void MainWindow::ChackMagneticSensors()
{
    if(ui->checkBox->checkState())
    {
        if(ui->SensorMagneticWindow->isChecked() || ui->hackingDor->checkState())
        {
            ui->lineEdit->setText("dor Hacking");
            ui->textEdit->setText("Blocking dor");
        }

        if(ui->SensorMagneticWindow->isChecked() || ui->hackingWindow->checkState())
        {
            ui->lineEdit->setText("Windows Hacking");
            ui->textEdit->setText("Blocking Window");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    //m_movies[m_camerasSeeNow[0]]->stop();
    //m_movies[ui->comboBox->currentText()]->setScaledSize(ui->label->size());

    //m_screans[m_currentScrean]->setMovie(m_movies[ui->comboBox->currentText()].get());
    ui->label->setMovie(m_movies[ui->comboBox->currentText()].get());
    m_movies[ui->comboBox->currentText()]->start();
    m_camerasSeeNow[Camera1] = ui->comboBox->currentText();
    Update(Camera1);
}

void MainWindow::on_pushButton_2_clicked()
{
    //m_movies[m_camerasSeeNow[1]]->stop();
    //m_movies[ui->comboBox_2->currentText()]->setScaledSize(ui->label_2->size());

    //m_screans[ui->comboBox_2->currentText()]->setMovie(m_movies[ui->comboBox_2->currentText()]/*.get()*/);
    ui->label_2->setMovie(m_movies[ui->comboBox_2->currentText()].get());
    m_movies[ui->comboBox_2->currentText()]->start();
    m_camerasSeeNow[Camera2] = ui->comboBox_2->currentText();
    Update(Camera2);
}

void MainWindow::on_pushButton_6_clicked()
{
    //m_movies[m_camerasSeeNow[2]]->stop();
    //m_movies[ui->comboBox_3->currentText()]->setScaledSize(ui->label_3->size());

//    m_screans[ui->comboBox_3->currentText()]->setMovie(m_movies[ui->comboBox_3->currentText()]/*.get()*/);
    ui->label_3->setMovie(m_movies[ui->comboBox_3->currentText()].get());
    m_movies[ui->comboBox_3->currentText()]->start();
    m_camerasSeeNow[Camera3] = ui->comboBox_3->currentText();

    Update(Camera3);
}

void MainWindow::on_pushButton_4_clicked()
{
    //m_movies[m_camerasSeeNow[3]]->stop();
    //m_movies[ui->comboBox_4->currentText()]->setScaledSize(ui->label_4->size());

 //   m_screans[ui->comboBox_4->currentText()]->setMovie(m_movies[ui->comboBox_4->currentText()]/*.get()*/);
    ui->label_4->setMovie(m_movies[ui->comboBox_4->currentText()].get());
    m_movies[ui->comboBox_4->currentText()]->start();
    m_camerasSeeNow[Camera4] = ui->comboBox_4->currentText();
    Update(Camera4);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->resize(400, 250);
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    Update(Camera1);
}

void MainWindow::on_pushButton_3_clicked()
{

    ui->label->resize(ui->label_3->width(), ui->label_2->height());
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    UpdateAll();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event);
//    QPainter painter(this); // Создаём объект отрисовщика
//    // Устанавливаем кисть абриса
//    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

}
//void MainWindow::on_currentScreanButton_clicked()
//{
//    qDebug() << m_currentScrean;
//    m_currentScrean = Camera1;
//}

//void MainWindow::on_currentScreanButton_2_clicked()
//{
//     qDebug() << m_currentScrean;
//     m_currentScrean = Camera2;
//}

//void MainWindow::on_currentScreanButton_3_clicked()
//{
//     qDebug() << m_currentScrean;
//     m_currentScrean = Camera3;
//}

//void MainWindow::on_currentScreanButton_4_clicked()
//{
//     qDebug() << m_currentScrean;
//     m_currentScrean = Camera4;
//}


void MainWindow::on_SensorTemp_clicked()
{
    ui->lineEdit->setText("SensorTemp in 1 room ");
}

void MainWindow::on_SensorTemp_2_clicked()
{
     ui->lineEdit->setText("SensorTemp in 2 room ");
}

void MainWindow::on_SensorPresentsRoom_2_clicked()
{
     ui->lineEdit->setText("Sensor Present in 2 room ");
}

void MainWindow::on_SensorPresentsRoom_clicked()
{
     ui->lineEdit->setText("Sensor Present in 1 room ");
}

void MainWindow::on_SensorMagneticWindow_clicked()
{
     ui->lineEdit->setText("Sensor Magnetic in 1 Window");
}

void MainWindow::on_ServoMehWindow_clicked()
{
     ui->lineEdit->setText("Servo Meh Window in 1 Window");
}

void MainWindow::on_SensorMagneticWindow_2_clicked()
{
     ui->lineEdit->setText("Sensor Magnetic in 2 Window");
}

void MainWindow::on_SensorMagnetic_3_clicked()
{
     ui->lineEdit->setText("Sensor Magnetic in door");
}

void MainWindow::on_ServoMehDoor_clicked()
{
    ui->lineEdit->setText("Servo Meh Window in in door");
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->SensorMagneticWindow->setVisible(false);
        ui->SensorMagneticWindow_2->setVisible(false);
        ui->SensorMagnetic_3->setVisible(false);
        ui->ServoMehDoor->setVisible(false);
        ui->ServoMehWindow->setVisible(false);
        ui->ServoMehWindow_2->setVisible(false);
    }
    else
    {
        ui->SensorMagneticWindow->setVisible(true);
        ui->SensorMagneticWindow_2->setVisible(true);
        ui->SensorMagnetic_3->setVisible(true);
        ui->ServoMehDoor->setVisible(true);
        ui->ServoMehWindow->setVisible(true);
        ui->ServoMehWindow_2->setVisible(true);
    }
    PaintFrame();
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if(checked)
    {
        ui->SensorTemp->setVisible(false);
        ui->SensorTemp_2->setVisible(false);
    }
    else
    {
        ui->SensorTemp->setVisible(true);
        ui->SensorTemp_2->setVisible(true);
    }
    PaintFrame();
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    if(checked)
    {
        ui->SensorPresentsRoom->setVisible(false);
        ui->SensorPresentsRoom_2->setVisible(false);
    }
    else
    {
        ui->SensorPresentsRoom->setVisible(true);
        ui->SensorPresentsRoom_2->setVisible(true);
    }
    PaintFrame();
}
