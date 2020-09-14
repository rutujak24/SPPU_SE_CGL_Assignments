#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

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

 QImage image(220,320, QImage::Format_RGB888);

int sign(int a)
{
    if(a==0)
        return 0;
    else if(a>0)
        return 1;
    else
        return -1;
}

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
        image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        x=x+dx;
        y=y+dy;
        i=i+1;
    }
}

void Bresenham(float x1, float y1, float x2, float y2)
{
    //QImage image(191,321, QImage::Format_RGB888);

    float dx,dy,x,y,e,s1,s2,temp,interchange=0;
    x=x1;
    y=y1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    s1=sign(x2-x1);
    s2=sign(y2-y1);
    if (dy>dx)
    {
        temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
        interchange=0;
    e=(2*dy)-dx;
    for(int i=1;i<=dx;i++)
    {
        image.setPixel((int)x,(int)y,qRgb(255,255,255));
        while(e>0)
        {
            if(interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-(2*dx);
        }
        if(interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+(2*dy);
    }
}

void MainWindow::on_pushButton_clicked()
{
    //QImage image(191,321, QImage::Format_RGB888);

    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    DDA(x1,y1,x2,y2);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //QImage image(191,321, QImage::Format_RGB888);

    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    Bresenham(x1,y1,x2,y2);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    //QImage image(191,321, QImage::Format_RGB888);

    float h,w,x1,y1;
    h=ui->textEdit_5->toPlainText().toFloat();
    w=ui->textEdit_6->toPlainText().toFloat();

    x1=110-(w/2);
    y1=160-(h/2);

    Bresenham(x1,y1,x1+w,y1);
    Bresenham(x1+w,y1,x1+w,y1+h);
    Bresenham(x1+w,y1+h,x1,y1+h);
    Bresenham(x1,y1+h,x1,y1);

    DDA(110,y1,x1+w,160);
    DDA(x1+w,160,110,y1+h);
    DDA(110,y1+h,x1,160);
    DDA(x1,160,110,y1);

    //Bresenham((x1+110)/2,(y1+160)/2,(110+x1+w)/2,(y1+160)/2);
    //Bresenham((110+x1+w)/2,(y1+160)/2,(x1+w+110)/2,(y1+h+160)/2);
    //Bresenham((x1+w+110)/2,(y1+h+160)/2,(x1+110)/2,(y1+h+160)/2);
    //Bresenham((x1+110)/2,(y1+h+160)/2,(x1+110)/2,(y1+160)/2);

    x1=110-(w/4);
    y1=160-(h/4);

    Bresenham(x1,y1,x1+w/2,y1);
    Bresenham(x1+w/2,y1,x1+w/2,y1+h/2);
    Bresenham(x1+w/2,y1+h/2,x1,y1+h/2);
    Bresenham(x1,y1+h/2,x1,y1);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    int i,j;
    for(i=0;i<220;i++)
    {
        for(j=0;j<320;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}
