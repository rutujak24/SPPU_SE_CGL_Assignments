#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include "QMouseEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage image(400, 400, QImage::Format_RGB888);
QImage image1(30, 30, QImage::Format_RGB888);

int c=0;
float xp[10],yp[10];
int rvalue=0, gvalue=0, bvalue=0;

void DDA(float x1, float y1, float x2, float y2)
{
    //QImage image(191,321, QImage::Format_RGB888);

    float dx,dy,length,x,y;
    if(abs(x2-x1)>=abs(y2-y1))
        length=abs(x2-x1);
    else
        length=abs(y2-y1);
    dx=(x2-x1)/length;
    dy=(y2-y1)/length;
    x=x1+0.5;
    y=y1+0.5;
    int i=1;
    while(i<=length)
    {
        image.setPixel(floor(x),floor(y),qRgb(rvalue,gvalue,bvalue));
        x=x+dx;
        y=y+dy;
        i=i+1;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int i;
    float erx=ui->label->x();
    float ery=ui->label->y();

    //float x1,y1;
    //x1=event->pos().x();
    //y1=event->pos().y();
    //image.setPixel(x1-erx,y1-ery,qRgb(255,255,255));

    if(event->button() == Qt::LeftButton)
    {
        xp[c]=(event->pos().x())-erx;
        yp[c]=(event->pos().y())-ery;
        image.setPixel(xp[c],yp[c],qRgb(rvalue,gvalue,bvalue));
        c++;
    }
    else if(event->button() == Qt::RightButton)
    {
        for(i=0;i<c-1;i++)
            DDA(xp[i],yp[i],xp[i+1],yp[i+1]);
        if(c!=1)
            DDA(xp[c-1],yp[c-1],xp[0],yp[0]);
        c=0;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<400;i++)
    {
        for(int j=0;j<400;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rvalue=value;

    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
            image1.setPixel(i,j,qRgb(rvalue,gvalue,bvalue));
    }

    ui->label_6->setPixmap(QPixmap::fromImage(image1));
    ui->label_6->show();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    gvalue=value;

    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
            image1.setPixel(i,j,qRgb(rvalue,gvalue,bvalue));
    }

    ui->label_6->setPixmap(QPixmap::fromImage(image1));
    ui->label_6->show();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    bvalue=value;

    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
            image1.setPixel(i,j,qRgb(rvalue,gvalue,bvalue));
    }

    ui->label_6->setPixmap(QPixmap::fromImage(image1));
    ui->label_6->show();
}
