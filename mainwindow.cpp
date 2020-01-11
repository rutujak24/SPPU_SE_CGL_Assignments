#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"iostream"
using namespace std;
QImage image(300,300,QImage::Format_RGB888);


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


void MainWindow::on_DDA_clicked()
{
    QRgb value;
    value=qRgb(255,0,0);

    QString a;
    a=ui->x1->toPlainText();
    float X1=a.toFloat();
    a=ui->x2->toPlainText();
    float X2=a.toFloat();
    a=ui->y1->toPlainText();
    float Y1=a.toFloat();
    a=ui->y2->toPlainText();
    float Y2=a.toFloat();
    float dx=X2-X1;
    float dy=Y2-Y1;
    float step,Xinc,Yinc;
    if(abs(dx)>abs(dy)){
        step=abs(dx);
    }
    else{
        step=abs(dy);
    }
    Xinc=dx/step;
    Yinc=dy/step;
    for(int i=1;i<=step;i++){
        image.setPixel(X1,Y1,value);
        X1=X1+Xinc;
        Y1=Y1+Yinc;
    }
    ui->out->setPixmap(QPixmap::fromImage(image));
    ui->out->show();

}
void MainWindow:: DDA(float X1,float Y1,float X2,float Y2 ){
    QRgb value;
    value=qRgb(255,0,0);

    float dx=X2-X1;
    float dy=Y2-Y1;
    float step,Xinc,Yinc;
    if(abs(dx)>abs(dy)){
        step=abs(dx);
    }
    else{
        step=abs(dy);
    }
    Xinc=dx/step;
    Yinc=dy/step;
    for(int i=1;i<=step;i++){
        image.setPixel(X1,Y1,value);
        X1=X1+Xinc;
        Y1=Y1+Yinc;
    }
    ui->out->setPixmap(QPixmap::fromImage(image));
    ui->out->show();

   }

void MainWindow::on_bresenham_clicked()
{
    QRgb value;
        value=qRgb(255,0,0);

        QString a;
        a=ui->x1->toPlainText();
        float X1=a.toFloat();
        a=ui->x2->toPlainText();
        float X2=a.toFloat();
        a=ui->y1->toPlainText();
        float Y1=a.toFloat();
        a=ui->y2->toPlainText();
        float Y2=a.toFloat();
        float X=X1;
        float Y=Y1;
        float dx=X2-X1;
        float dy=Y2-Y1;
        if(abs(dy/dx)<1){
        float P=2*dy-dx;
        while(X<=X2){
            image.setPixel(X,Y,value);
            X++;
            if(P<0){
                P=P+2*dy;
            }
            else{
                P=P+2*dy-2*dx;
                Y++;
            }
        }
        }
        else{
            float P=2*dx-dy;

        while(Y<=Y2){
            image.setPixel(X,Y,value);
            Y++;
            if(P<0){
                P=P+2*dx;
                }
            else{
                P=P+2*dx-2*dy;
                X++;
            }
        }
        }
        ui->out->setPixmap(QPixmap::fromImage(image));
        ui->out->show();

}
void MainWindow::Bresenham(float X1,float Y1,float X2,float Y2){
    QRgb value;
        value=qRgb(255,0,0);

    float X=X1;
    float Y=Y1;
    float dx=X2-X1;
    float dy=Y2-Y1;
    if(abs(dy/dx)<1){
    float P=2*dy-dx;
    while(X<=X2){
        image.setPixel(X,Y,value);
        X++;
        if(P<0){
            P=P+2*dy;
        }
        else{
            P=P+2*dy-2*dx;
            Y++;
        }
    }
    }
    else{
        float P=2*dx-dy;

    while(Y<=Y2){
        image.setPixel(X,Y,value);
        Y++;
        if(P<0){
            P=P+2*dx;
            }
        else{
            P=P+2*dx-2*dy;
            X++;
        }
    }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QRgb value;
    value=qRgb(255,0,0);
    DDA(140,60,40,130);
    DDA(140,60,240,130);
    DDA(140,200,240,130);
    DDA(40,130,140,200);
    Bresenham(40,60,240,60);
    Bresenham(40,60,40,200);
    Bresenham(240,60,240,200);
    Bresenham(40,200,240,200);
    Bresenham(90,95,190,95);
    Bresenham(90,95,90,165);
    Bresenham(90,165,190,165);
    Bresenham(190,95,190,165);

    ui->out->setPixmap(QPixmap::fromImage(image));
    ui->out->show();



}

void MainWindow::on_len_and_b_clicked()
{
    QRgb value;
        value=qRgb(255,0,0);

        QString a;
        a=ui->x1->toPlainText();
        float len=a.toFloat();
        a=ui->x2->toPlainText();
        float b=a.toFloat();
        Bresenham(40,60,40+len,60);
        Bresenham(40,60,40,60+b);
        Bresenham(40+len,60,40+len,60+b);
        Bresenham(40,60+b,40+len,60+b);
        DDA(40,60+b/2,40+len/2,60);
        DDA(40,60+b/2,40+len/2,60+b);
        DDA(40+len/2,60+b,40+len,60+b/2);
        DDA(40+len/2,60,40+len,60+b/2);
        Bresenham(40+len/4,60+b/4,40+3*len/4,60+b/4);
        Bresenham(40+len/4,60+b/4,40+len/4,60+3*b/4);
        Bresenham(40+len/4,60+3*b/4,40+3*len/4,60+3*b/4);
        Bresenham(40+3*len/4,60+b/4,40+3*len/4,60+3*b/4);

        ui->out->setPixmap(QPixmap::fromImage(image));
        ui->out->show();

}
