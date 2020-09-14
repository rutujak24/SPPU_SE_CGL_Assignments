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

QImage image(400, 400, QImage::Format_RGB888);

MainWindow::~MainWindow()
{
    delete ui;
}

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

float xf[20],yf[20];
int c=0,cnt;

void display()
{
    for(int i=0;i<cnt-1;i++)
        Bresenham(xf[i],yf[i],xf[i+1],yf[i+1]);
    Bresenham(xf[cnt-1],yf[cnt-1],xf[0],yf[0]);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    float erx,ery;

    erx=ui->label->x();
    ery=ui->label->y();

    if(event->button() == Qt::LeftButton)
    {
        xf[c]=(event->pos().x())-erx;
        yf[c]=(event->pos().y())-ery;
        image.setPixel(xf[c],yf[c],qRgb(255,255,255));
        c++;
    }

    if(event->button() == Qt::RightButton)
    {
        cnt=c;
        c=0;
        display();
    };

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
void MainWindow::on_pushButton_clicked()
{
    float sx,sy;

    sx=ui->textEdit->toPlainText().toFloat();
    sy=ui->textEdit_2->toPlainText().toFloat();

    for(int i=0;i<cnt;i++)
    {
        xf[i]=xf[i]*sx;
        yf[i]=yf[i]*sy;
    }

    on_pushButton_4_clicked();
    display();

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    float tx,ty;

    tx=ui->textEdit_3->toPlainText().toFloat();
    ty=ui->textEdit_4->toPlainText().toFloat();

    for(int i=0;i<cnt;i++)
    {
        xf[i]=xf[i]+tx;
        yf[i]=yf[i]+ty;
    }

    on_pushButton_4_clicked();
    display();

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    float ang;

    ang=ui->textEdit_5->toPlainText().toFloat();

    for(int i=0;i<cnt;i++)
    {
        xf[i]=(xf[i]*cos(ang*3.142/180))-(yf[i]*sin(ang*3.142/180));
        yf[i]=(xf[i]*sin(ang*3.142/180))+(yf[i]*cos(ang*3.142/180));
    }

    on_pushButton_4_clicked();
    display();

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    for(int i=0;i<400;i++)
    {
        for(int j=0;j<400;j++)
            image.setPixel(i,j,qRgb(0,0,0));
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
