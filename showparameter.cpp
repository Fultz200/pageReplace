#include "showparameter.h"
#include "ui_showparameter.h"
#include<QDebug>
#include<QPalette>
#include<QFile>
#include<QDir>
ShowParameter::ShowParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowParameter)
{
    ui->setupUi(this);

    setWindowTitle(tr("缺页计算"));
    setMaximumSize(852,430);
    setMinimumSize(852,430);

    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/image/images/2.jpg").scaled(this->size())));
     this->setPalette(p);

    ui->listLabel->hide();
    ui->pagenumLabel->hide();

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(100);

 initilabel();
 //this->setWindowFlags(Qt::WindowStaysOnTopHint);//设置参数界面总是在最前面显示

//QDir::setCurrent("/images");
file.setFileName("Log.txt");

 stream.setDevice(&file);



}

ShowParameter::~ShowParameter()
{

    delete ui;
}

//显示缺页次数
void ShowParameter::missnumSLOT(int num,int i,int mtime)
{

         if(i==0)
                {
                 ui->fifonumLabel->setText(tr("%1").arg(num));
                 ui->fiforateLabel->setText(tr("%1%").arg(num/n*100));
                 ui->fifotimeLabel->setText(tr("%1 ms").arg(mtime));
                 ui->fifonumLabel->show();
                 ui->fiforateLabel->show();
                 ui->fifotimeLabel->show();
               return;
                }
          if(i==1)
            {
                ui->lrunumLabel->setText(tr("%1").arg(num));
                ui->lrurateLabel->setText(tr("%1%").arg(num/n*100));
                ui->lrutimeLabel->setText(tr("%1 ms").arg(mtime));
                ui->lrunumLabel->show();
                ui->lrurateLabel->show();
                ui->lrutimeLabel->show();
                return;
            }
          if(i==2)
              {
                    ui->optnumLabel->setText(tr("%1").arg(num));
                    ui->optrateLabel->setText(tr("%1%").arg(num/n*100));
                    ui->optimeLabel->setText(tr("%1 ms").arg(mtime));
                    ui->optnumLabel->show();
                    ui->optrateLabel->show();
                    ui->optimeLabel->show();
                    return;
               }
            if(i==3)
                {
                    ui->rannumLabel->setText(tr("%1").arg(num));
                    ui->ranrateLabel->setText(tr("%1%").arg(num/n*100));
                    ui->rantimeLabel->setText(tr("%1 ms").arg(mtime));
                    ui->rannumLabel->show();
                    ui->ranrateLabel->show();
                    ui->rantimeLabel->show();
                }
}


//随机序列的个数
void ShowParameter::listnumSLOT(int listnum)
{
    n=listnum;
}

//显示随机序列
void ShowParameter::showlist(QString s){
    ui->listLabel->setText(tr("%1").arg(s));
    ui->listLabel->show();
    ui->pagenumLabel->setText(tr("%1").arg(n));
    ui->pagenumLabel->show();

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
   qDebug()<<tr("日志文件打开失败!");
  stream<<QString("随机页面序列: ")<<s<<QString("     运行时间: %1\n").arg(QDateTime::currentDateTime().toString());

file.close();

}


//各标签的初始化
void ShowParameter::initilabel()
{

    ui->fifonumLabel->hide();
    ui->fiforateLabel->hide();
    ui->fifotimeLabel->hide();
    ui->lrunumLabel->hide();
    ui->lrurateLabel->hide();
    ui->lrutimeLabel->hide();
    ui->optnumLabel->hide();
    ui->optrateLabel->hide();
    ui->optimeLabel->hide();
    ui->rannumLabel->hide();
    ui->ranrateLabel->hide();
    ui->rantimeLabel->hide();

}

//显示系统时间
void ShowParameter::updateTime()
{
    ui->timeLabel->setText(tr("Current System Time: ")+QDateTime::currentDateTime().toString("MM/dd hh:mm:ss"));

}
