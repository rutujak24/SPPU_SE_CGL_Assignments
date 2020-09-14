#include "mainwindow.h"
#include "ui_mainwindow.h"
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

QImage image(400,400,QImage::Format_RGB888);

int sign(int a)
{
    if(a==0)
        return 0;
    else if(a>0)
        return 1;
    else
        return -1;
}

void Bresenham(float x1, float y1, float x2, float y2, QImage &image, QRgb colour)
{
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
        image.setPixel((int)x,(int)y,colour);
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
    image.setPixel((int)x,(int)y,colour);
}

int c=0,cl=0,flag=1;
float xl[20],yl[20],xl2[20],yl2[20],xb,yb,xb2,yb2;

int Assign_Code(float x,float y)
{
    int code;

    code=0;
    if(y<yb)
        code=code+8;
    if(y>yb2)
        code=code+4;
    if(x>xb2)
        code=code+2;
    if(x<xb)
        code=code+1;
    return code;
}

void Clip(float x1,float y1,float x2,float y2)
{
    int code1=Assign_Code(x1,y1);
    int code2=Assign_Code(x2,y2);
    QRgb colour = qRgb(255,255,255);
    QRgb nocolour = qRgb(0,0,0);

    if(code1==0 && code2==0)
    {
       return;
    }
    else if(code1 & code2)
    {
        Bresenham(x1,y1,x2,y2,image,nocolour);
    }
    else
    {
        if(code1!=0 && code2!=0)
        {
           float x01,x02,y01,y02;
           if(code1 & 8)
           {
               x01=x1+(x2-x1)*((yb-y1)/(y2-y1));
               y01=yb;
           }
           if(code1 & 4)
           {
               x01=x1+(x2-x1)*((yb2-y1)/(y2-y1));
               y01=yb2;
           }
           if(code1 & 2)
           {
               x01=xb2;
               y01=y1+(y2-y1)*((xb2-x1)/(x2-x1));
           }
           if(code1 & 1)
           {
               x01=xb;
               y01=y1+(y2-y1)*((xb-x1)/(x2-x1));
           }

           if(code2 & 8)
           {
               x02=x1+(x2-x1)*((yb-y1)/(y2-y1));
               y02=yb;
           }
           if(code2 & 4)
           {
               x02=x1+(x2-x1)*((yb2-y1)/(y2-y1));
               y02=yb2;
           }
           if(code2 & 2)
           {
               x02=xb2;
               y02=y1+(y2-y1)*((xb2-x1)/(x2-x1));
           }
           if(code2 & 1)
           {
               x02=xb;
               y02=y1+(y2-y1)*((xb-x1)/(x2-x1));
           }

           //Bresenham(x1,y1,x01,y01,image,nocolour);
           //Bresenham(x02,y02,x2,y2,image,nocolour);
           Bresenham(x1,y1,x2,y2,image,nocolour);
           Bresenham(x01,y01,x02,y02,image,colour);
        }
        else
        {
            int code0;
            float x0,y0;
            if(code1!=0)
                code0=code1;
            else
                code0=code2;
            if(code0 & 8)
            {
                x0=x1+(x2-x1)*((yb-y1)/(y2-y1));
                y0=yb;
            }
            if(code0 & 4)
            {
                x0=x1+(x2-x1)*((yb2-y1)/(y2-y1));
                y0=yb2;
            }
            if(code0 & 2)
            {
                x0=xb2;
                y0=y1+(y2-y1)*((xb2-x1)/(x2-x1));
            }
            if(code0 & 1)
            {
                x0=xb;
                y0=y1+(y2-y1)*((xb-x1)/(x2-x1));
            }

            /*if(code1!=0)
                Bresenham(x1,y1,x0,y0,image,nocolour);
            else if(code2!=0)
                Bresenham(x0,y0,x2,y2,image,nocolour);*/

            Bresenham(x1,y1,x2,y2,image,nocolour);
            if(code1!=0)
                 Bresenham(x0,y0,x2,y2,image,colour);
            else if(code2!=0)
                 Bresenham(x1,y1,x0,y0,image,colour);
        }
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    float x,y,erx=0,ery=0;
    QRgb colour = qRgb(255,255,255);

    erx=ui->label->x();
    ery=ui->label->y();

    if(event->button() == Qt::LeftButton  && flag==1)
    {
        xb=(event->pos().x())-erx;
        yb=(event->pos().y())-ery;
    }

    else if(event->button() == Qt::RightButton)
    {
        x=(event->pos().x())-erx;
        y=(event->pos().y())-ery;
        if(cl==0)
        {
            xl[c]=x;
            yl[c]=y;
            image.setPixel(xl[c],yl[c],qRgb(255,255,255));
            cl=1;
        }
        else if(cl==1)
        {
            xl2[c]=x;
            yl2[c]=y;
            image.setPixel(xl2[c],yl2[c],qRgb(255,255,255));
            cl=0;
            Bresenham(xl[c],yl[c],xl2[c],yl2[c],image,colour);
            c++;
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    float erx,ery;
    QRgb colour = qRgb(255,255,255);

    QImage img_temp(400,400,QImage::Format_RGB888);

    if(flag)
    {
        img_temp=image;

        erx=ui->label->x();
        ery=ui->label->y();

        xb2=(event->pos().x())-erx;
        yb2=(event->pos().y())-ery;

        Bresenham(xb,yb,xb2,yb,img_temp,colour);
        Bresenham(xb2,yb,xb2,yb2,img_temp,colour);
        Bresenham(xb2,yb2,xb,yb2,img_temp,colour);
        Bresenham(xb,yb2,xb,yb,img_temp,colour);

    }

    ui->label->setPixmap(QPixmap::fromImage(img_temp));
    ui->label->show();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    float erx,ery,xb2,yb2;
    QRgb colour = qRgb(255,255,255);

    if(event->button() == Qt::LeftButton && flag==1)
    {
        erx=ui->label->x();
        ery=ui->label->y();

        xb2=(event->pos().x())-erx;
        yb2=(event->pos().y())-ery;

        Bresenham(xb,yb,xb2,yb,image,colour);
        Bresenham(xb2,yb,xb2,yb2,image,colour);
        Bresenham(xb2,yb2,xb,yb2,image,colour);
        Bresenham(xb,yb2,xb,yb,image,colour);

        flag=0;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<c;i++)
        Clip(xl[i],yl[i],xl2[i],yl2[i]);

   ui->label->setPixmap(QPixmap::fromImage(image));
   ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<400;i++)
    {
        for(int j=0;j<400;j++)
            image.setPixel(i,j,qRgb(0,0,0));
    }

    flag=1;
    c=0;

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}


/*int c=0;
float x1,y1,x2,y2;*/

/*void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //View Port by Double Click

    float x,y,erx,ery;

    erx=ui->label->x();
    ery=ui->label->y();

    x=(event->pos().x())-erx;
    y=(event->pos().y())-ery;

    if(c==0)
    {
        x1=x;
        y1=y;
        image.setPixel(x1,y1,qRgb(255,255,255));
        c++;
    }
    else if(c==1)
    {
        x2=x;
        y2=y;
        image.setPixel(x2,y2,qRgb(255,255,255));
        c=0;
        Bresenham(x1,y1,x2,y1);
        Bresenham(x2,y1,x2,y2);
        Bresenham(x2,y2,x1,y2);
        Bresenham(x1,y2,x1,y1);
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}*/


/*void MainWindow::on_pushButton_clicked()
{
    //View Port by taking co-ordinates from user

    float h,w,x1,y1,x2,y2;

    h=ui->textEdit->toPlainText().toFloat();
    w=ui->textEdit_2->toPlainText().toFloat();

    x1=200-(w/2);
    y1=200-(h/2);
    x2=200+(w/2);
    y2=200+(h/2);

    Bresenham(x1,y1,x2,y1);
    Bresenham(x2,y1,x2,y2);
    Bresenham(x2,y2,x1,y2);
    Bresenham(x1,y2,x1,y1);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}*/


