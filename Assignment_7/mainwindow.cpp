#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "stack"
#include "utility"
using namespace std;

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
QImage image1(30,30,QImage::Format_RGB888);

int c=0;
float xp[20],yp[20];
int rvalue,gvalue,bvalue;
int r,g,b;
QRgb bdcolour;

int sign(int a)
{
    if(a==0)
        return 0;
    else if(a>0)
        return 1;
    else
        return -1;
}

void Bresenham(float x1, float y1, float x2, float y2)
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
        image.setPixel((int)x,(int)y,qRgb(rvalue,gvalue,bvalue));
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

void FloodFill(int x, int y, QRgb colour, QRgb bgcolour)
{
    if(image.pixel(x,y) == bgcolour)
    {
        image.setPixel(x,y,colour);
        FloodFill(x+1,y,colour,bgcolour);
        FloodFill(x,y+1,colour,bgcolour);
        FloodFill(x-1,y,colour,bgcolour);
        FloodFill(x,y-1,colour,bgcolour);
        //FloodFill(x+1,y-1,colour,bgcolour);
        //FloodFill(x+1,y+1,colour,bgcolour);
        //FloodFill(x-1,y+1,colour,bgcolour);
        //FloodFill(x-1,y-1,colour,bgcolour);
    }
}

/*void BoundaryFill(int x, int y, QRgb colour)
{
    if(image.pixel(x,y) != bdcolour && image.pixel(x,y) != qRgb(rvalue,gvalue,bvalue))
    {
        image.setPixel(x,y,colour);
        BoundaryFill(x+1,y,colour);
        BoundaryFill(x,y+1,colour);
        BoundaryFill(x-1,y,colour);
        BoundaryFill(x,y-1,colour);
        //BoundaryFill(x+1,y-1,colour);
        //BoundaryFill(x+1,y+1,colour);
        //BoundaryFill(x-1,y+1,colour);
        //BoundaryFill(x-1,y-1,colour);
    }
}*/

void BoundaryFill(float x, float y, QRgb colour)
{
    stack<pair<float,float>> s;
    s.push(make_pair(x,y));

    while(!s.empty())
    {
        pair<float,float> p;
        p = s.top();
        s.pop();
        float xc = p.first, yc = p.second;
        if(image.pixel(xc,yc) != bdcolour  && image.pixel(xc,yc) != qRgb(rvalue,gvalue,bvalue))
        {
            image.setPixel(xc,yc,colour);
            s.push(make_pair(xc+1,yc));
            s.push(make_pair(xc,yc+1));
            s.push(make_pair(xc-1,yc));
            s.push(make_pair(xc,yc-1));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int i;
    float erx,ery;

    erx=ui->label->x();
    ery=ui->label->y();

    if(event->button() == Qt::LeftButton)
    {
        xp[c]=(event->pos().x())-erx;
        yp[c]=(event->pos().y())-ery;
        image.setPixel(xp[c],yp[c],qRgb(rvalue,gvalue,bvalue));
        c++;
    }
    else if(event->button() == Qt::RightButton)
    {
        bdcolour=qRgb(rvalue,gvalue,bvalue);
        for(i=0;i<c-1;i++)
            Bresenham(xp[i],yp[i],xp[i+1],yp[i+1]);
        if(c!=1)
            Bresenham(xp[c-1],yp[c-1],xp[0],yp[0]);
        c=0;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    float x,y,erx=0,ery=0;
    QRgb colour,bgcolour;

    //erx=ui->label->x();
    //ery=ui->label->y();

    x=(event->pos().x())-erx;
    y=(event->pos().y())-ery;

    bgcolour=image.pixel(x,y);
    colour=qRgb(rvalue,gvalue,bvalue);

    if(ui->radioButton->isChecked())
        FloodFill(x,y,colour,bgcolour);
    if(ui->radioButton_2->isChecked())
        BoundaryFill(x,y,colour);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_dial_valueChanged(int value)
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

void MainWindow::on_dial_2_valueChanged(int value)
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

void MainWindow::on_dial_3_valueChanged(int value)
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

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<400;i++)
    {
        for(int j=0;j<400;j++)
            image.setPixel(i,j,qRgb(0,0,0));
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
