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

 QImage image(260, 380, QImage::Format_RGB888);

int sign(int a)
{
    if(a==0)
        return 0;
    else if(a>0)
        return 1;
    else
        return -1;
}

void DDA(float x1, float y1, float x2, float y2,int c, int t)
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
        if(i%c&&t==0)
            image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        else if(i%c&&t==1)
        {
            if(i%c!=5 && i%c!=6 && i%c!=8)
                image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        }
        x=x+dx;
        y=y+dy;
        i=i+1;
    }
}

void Bresenham(float x1, float y1, float x2, float y2, int c, int t)
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
        if(i%c!=0 && t==0)
            image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        else if(i%c!=0 && t==1)
        {
            if(i%c!=5 && i%c!=6 && i%c!=8)
                image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        }
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

void MainWindow::on_pushButton_2_clicked()
{
    //SOLID

    float x1,y1,x2,y2;
     x1=ui->textEdit->toPlainText().toFloat();
     y1=ui->textEdit_2->toPlainText().toFloat();
     x2=ui->textEdit_3->toPlainText().toFloat();
     y2=ui->textEdit_4->toPlainText().toFloat();

     if(ui->radioButton->isChecked())
        DDA(x1,y1,x2,y2,500,0);
     if(ui->radioButton_2->isChecked())
         Bresenham(x1,y1,x2,y2,500,0);

     ui->label_5->setPixmap(QPixmap::fromImage(image));
     ui->label_5->show();
 }

void MainWindow::on_pushButton_3_clicked()
{
    //DOTTED

    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    if(ui->radioButton->isChecked())
       DDA(x1,y1,x2,y2,2,0);
    if(ui->radioButton_2->isChecked())
        Bresenham(x1,y1,x2,y2,2,0);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    //DASHED

    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    if(ui->radioButton->isChecked())
       DDA(x1,y1,x2,y2,5,0);
    if(ui->radioButton_2->isChecked())
        Bresenham(x1,y1,x2,y2,5,0);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    //DASH-DOT

    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();

    if(ui->radioButton->isChecked())
       DDA(x1,y1,x2,y2,9,1);
    if(ui->radioButton_2->isChecked())
        Bresenham(x1,y1,x2,y2,9,1);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    //THICK

    float x1,y1,x2,y2,w,wy,wx,t;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    x2=ui->textEdit_3->toPlainText().toFloat();
    y2=ui->textEdit_4->toPlainText().toFloat();
    w=ui->textEdit_5->toPlainText().toFloat();

    if(x2!=x1)
    {
        wy=((w-1)/2*((sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))))/abs(x2-x1)));
        t=wy;
    }
    else if(x2==x1)
    {
        wx=((w-1)/2*((sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))))/abs(y2-y1)));
        t=wx;
    }
    if(ui->radioButton->isChecked())
    {
       for(int i=0;i<t;i++)
       {
           if(x2!=x1)
                DDA(x1,y1-(wy/2)+i,x2,y2-(wy/2)+i,500,0);
           else if(x1==x2)
                DDA(x1-(wx/2)+i,y1,x2-(wx/2)+i,y2,500,0);
       }
    }
    if(ui->radioButton_2->isChecked())
    {
       for(int i=0;i<t;i++)
       {
           if(x2!=x1)
                Bresenham(x1,y1-(wy/2)+i,x2,y2-(wy/2)+i,500,0);
           else if(x1==x2)
                Bresenham(x1-(wx/2)+i,y1,x2-(wx/2)+i,y2,500,0);
       }
    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_clicked()
{
    int i,j;
    for(i=0;i<260;i++)
    {
        for(j=0;j<380;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();

}
