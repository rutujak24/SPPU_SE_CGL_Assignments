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

 QImage image(360, 360, QImage::Format_RGB888);

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

 void mh(float &x, float &y, float &di)
 {
     x=x+1;
     di=di+(2*x)+1;
 }

 void md(float &x, float &y, float &di)
 {
     x=x+1;
     y=y-1;
     di=di+(2*x)-(2*y)+2;
 }

 void mv(float &x,float &y,float &di)
 {
     y=y-1;
     di=di-(2*y)+1;
 }
void Bresenham_Circle(float cx, float cy,float r)
{
    float x,y,di,d1,d2,limit;
    x=0;
    y=r;
    di=2*(1-r);
    limit=0;
    while(y>=limit)
    {
        image.setPixel(cx+x,cy+y,qRgb(255,255,255));
        image.setPixel(cx-x,cy+y,qRgb(255,255,255));
        image.setPixel(cx-x,cy-y,qRgb(255,255,255));
        image.setPixel(cx+x,cy-y,qRgb(255,255,255));
        if(di<0)
        {
            d1=(2*di)+(2*y)-1;
            if(d1<=0)
                mh(x,y,di);
            else
                md(x,y,di);
        }
        else if(di>0)
        {
            d2=(2*di)-(2*x)-1;
            if(d2<=0)
                md(x,y,di);
            else
                mv(x,y,di);
        }
        else if(di==0)
            md(x,y,di);
    }
}

void DDA_Circle(int cx,int cy,int r)
{
    float x1,x2,y1,y2,eps,sx,sy;
    int val,i;
    x1=r;
    y1=0;
    sx=x1;
    sy=y1;
    i=0;
    do
    {
        val=pow(2,i);
        i++;
    }while(val<r);
    eps = 1/pow(2,i-1);
    do
    {
        x2 = x1 + y1*eps;
        y2 = y1 - eps*x2;
        image.setPixel(cx+x2,cy-y2,qRgb(255,255,255));
        x1=x2;
        y1=y2;
    }while((y1-sy)<eps || (sx-x1)>eps);
}

void MainWindow::on_pushButton_clicked()
{
    //DDA Circle

    float cx,cy,r;
    cx=ui->textEdit->toPlainText().toFloat();
    cy=ui->textEdit_2->toPlainText().toFloat();
    r=ui->textEdit_3->toPlainText().toFloat();

    DDA_Circle(cx,cy,r);

    ui->label_4->setPixmap(QPixmap::fromImage(image));
    ui->label_4->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Bresenham Circle

    float cx,cy,r;
    cx=ui->textEdit->toPlainText().toFloat();
    cy=ui->textEdit_2->toPlainText().toFloat();
    r=ui->textEdit_3->toPlainText().toFloat();

    Bresenham_Circle(cx,cy,r);

    ui->label_4->setPixmap(QPixmap::fromImage(image));
    ui->label_4->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    //Pattern

    float cx,cy,r;
    cx=ui->textEdit->toPlainText().toFloat();
    cy=ui->textEdit_2->toPlainText().toFloat();
    r=ui->textEdit_3->toPlainText().toFloat();

    Bresenham_Circle(cx,cy,r);

    DDA(cx,cy-r,cx+r*cos(3.14/6),cy+r*sin(3.14/6));
    DDA(cx+r*cos(3.14/6),cy+r*sin(3.14/6),cx-r*cos(3.14/6),cy+r*sin(3.14/6));
    DDA(cx-r*cos(3.14/6),cy+r*sin(3.14/6),cx,cy-r);

    DDA_Circle(cx,cy,r*sin(3.14/6));

    ui->label_4->setPixmap(QPixmap::fromImage(image));
    ui->label_4->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    int i,j;
    for(i=0;i<360;i++)
    {
        for(j=0;j<360;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }

    ui->label_4->setPixmap(QPixmap::fromImage(image));
    ui->label_4->show();
}

