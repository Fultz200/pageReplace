#include "widget.h"
#include "ui_widget.h"
#include"creatrandlist.h"
#include<time.h>
#include<QDebug>
#include<QDockWidget>
#include<QMessageBox>
#include<QPalette>
#include<QProcess>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);

effect=new QSoundEffect;
effect->setSource(QUrl::fromLocalFile("D:/Qtprogram/pageReplace/images/1.wav"));
effect->setVolume(0.1f);
effect->setLoopCount(QSoundEffect::Infinite);
effect->play();


//connect(ui->stopmusicBtn,SIGNAL(clicked()),this,SLOT(stopmusicSlot()));
//connect(ui->startmusicBtn,SIGNAL(clicked()),this,SLOT(startmusicSlot()));

setWindowTitle(tr("页面置换算法"));
ui->titleLabel->setText(tr("模拟页面置换算法"));
ui->titleLabel->setAlignment(Qt::AlignCenter);


ui->dockWidget->setWindowTitle(tr("菜单"));

setMaximumSize(1247,747);
setMinimumSize(1247,747);

ui->textEdit->setReadOnly(true);
ui->textEdit_2->setReadOnly(true);
ui->textEdit_3->setReadOnly(true);
ui->textEdit_4->setReadOnly(true);
ui->textEdit_5->setReadOnly(true);

QPalette p;
p.setBrush(QPalette::Background,QBrush(QPixmap(":/image/images/1.jpg").scaled(this->size())));
 this->setPalette(p);
//ui->dockWidget->setPalette(p);
ui->dockWidget->hide();

ui->listspinBox->setMaximum(1000000);
ui->pageVolumespinBox->setMaximum(10);

shpare=new ShowParameter;   //参数对话框



timer1=new QTimer(this);
connect(timer1,SIGNAL(timeout()),this,SLOT(setRestartBtn()));
timer1->start(100);

objectFunction();        //对象的初始定义

ui->fifoProgressBar->setValue(0);
ui->optProgressBar->setValue(0);
ui->lruProgressBar->setValue(0);
ui->ranProgressBar->setValue(0);

connect(this,SIGNAL(Emitmissnum(int,int,int)),shpare,SLOT(missnumSLOT(int,int,int)));

connect(this,SIGNAL(listnumSignal(int)),shpare,SLOT(listnumSLOT(int)));
connect(this,SIGNAL(listshow(QString)),shpare,SLOT(showlist(QString)));


connect(ui->logBtn,SIGNAL(clicked()),this,SLOT(logBtnSlot()));



     connect(ui->listspinBox,SIGNAL(valueChanged(int)),this,SLOT(listnumSlot(int)));
     connect(ui->pageVolumespinBox,SIGNAL(valueChanged(int)),this,SLOT(pageVolumeSlot(int)));



       connect(ui->fifoStartBtn,SIGNAL(clicked()),this,SLOT(fifostartSlot()));
       connect(ui->fifoSuspendBtn,SIGNAL(clicked()),this,SLOT(fifoSuspendBtnSlot()));
       connect(ui->fifoContinueBtn,SIGNAL(clicked()),this,SLOT(fifoContinutBtnSlot()));



        connect(ui->optStartBtn,SIGNAL(clicked()),this,SLOT(optstartSlot()));
        connect(ui->optSuspendBtn,SIGNAL(clicked()),this,SLOT(optSuspendBtnSlot()));
        connect(ui->optContinueBtn,SIGNAL(clicked()),this,SLOT(optContinueBtnSlot()));

         connect(ui->lruStartBtn,SIGNAL(clicked()),this,SLOT(lrustartSlot()));
         connect(ui->lruSuspendBtn,SIGNAL(clicked()),this,SLOT(lruSuspendBtnSlot()));
         connect(ui->lruContinueBtn,SIGNAL(clicked()),this,SLOT(lruContinueBtnSlot()));

         connect(ui->ranStartBtn,SIGNAL(clicked()),this,SLOT(ranstartSlot()));
         connect(ui->ranSuspendBtn,SIGNAL(clicked()),this,SLOT(ranSuspendBtnSlot()));
         connect(ui->ranContinueBtn,SIGNAL(clicked()),this,SLOT(ranContinueBtnSlot()));

        //connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(startBtnSLot()));

        //connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(stopBtnSlot()));
          connect(ui->quitBtn,SIGNAL(clicked()),this,SLOT(quitBtnSLot()));
        //connect(ui->suspendBtn,SIGNAL(clicked()),this,SLOT(suspendSlot()));
         //connect(ui->continueBtn,SIGNAL(clicked()),this,SLOT(continueSLot()));



       // connect(ui->restartBtn,SIGNAL(clicked()),this,SLOT(restartBtnSlot()));

        connect(ui->parameterBtn,SIGNAL(clicked()),this,SLOT(parameterBtnSLOT()));

        connect(ui->toolBtn,SIGNAL(clicked()),this,SLOT(toolBtnSlot()));

        initBtnState(); //各个按钮的状态初始化

}

Widget::~Widget()
{
    delete fifo;
    delete lru;
    delete opt;
    delete ran;
    delete shpare;
    delete ui;
}


//初始化对象及相关的信号和槽的连接
void Widget::objectFunction(){


   fifo=new FIFO;
   lru=new LRU;
   opt=new OPT;
   ran=new RAN;



    connect(fifo,SIGNAL(xulie(QString,int)),this,SLOT(xulieshow(QString,int)));
      connect(fifo,SIGNAL(pageshow(QString,int)),this,SLOT(fifotextshow(QString,int)));
        connect(fifo,SIGNAL(clueshow(int)),this,SLOT(showclue(int)));
            connect(fifo,SIGNAL(missnumSignal(int,int,int)),this,SLOT(missnumSlot(int,int,int)));
                 connect(this,SIGNAL(listnumSignal(int)),fifo,SLOT(ListnumSlot(int)));
                   connect(this,SIGNAL(pageVolumeSignal(int)),fifo,SLOT(pageVolumeSlot(int)));
                      connect(fifo,SIGNAL(fifoProgressValue(int,int)),this,SLOT(updateProgressBar(int,int)));

    connect(lru,SIGNAL(xulie(QString,int)),this,SLOT(xulieshow(QString,int)));
         connect(lru,SIGNAL(lrupage(QString,int)),this,SLOT(lrutextshow(QString,int)));
             connect(lru,SIGNAL(clueshow(int)),this,SLOT(showclue(int)));
        connect(lru,SIGNAL(missnumSignal(int,int,int)),this,SLOT(missnumSlot(int,int,int)));
    connect(this,SIGNAL(listnumSignal(int)),lru,SLOT(listNumSlot(int)));
    connect(this,SIGNAL(pageVolumeSignal(int)),lru,SLOT(pageVolumeSlot(int)));
    connect(lru,SIGNAL(lruProgressBarValue(int,int)),this,SLOT(updateProgressBar(int,int)));


    connect(opt,SIGNAL(xulie(QString,int)),this,SLOT(xulieshow(QString,int)));
       connect(opt,SIGNAL(optpage(QString,int)),this,SLOT(opttextshow(QString,int)));
     connect(opt,SIGNAL(clueshow(int)),this,SLOT(showclue(int)));
         connect(opt,SIGNAL(missnumSignal(int,int,int)),this,SLOT(missnumSlot(int,int,int)));
    connect(this,SIGNAL(listnumSignal(int)),opt,SLOT(listnumSlot(int)));
       connect(this,SIGNAL(pageVolumeSignal(int)),opt,SLOT(pageVolumeSlot(int)));
       connect(opt,SIGNAL(optProgressBarValue(int,int)),this,SLOT(updateProgressBar(int,int)));


    connect(ran,SIGNAL(xulie(QString,int)),this,SLOT(xulieshow(QString,int)));
        connect(ran,SIGNAL(rantextshow(QString,int)),this,SLOT(rantextshow(QString,int)));
    connect(ran,SIGNAL(clueshow(int)),this,SLOT(showclue(int)));
        connect(ran,SIGNAL(missnumSignal(int,int,int)),this,SLOT(missnumSlot(int,int,int)));
    connect(this,SIGNAL(listnumSignal(int)),ran,SLOT(ListnumSlot(int)));
    connect(this,SIGNAL(pageVolumeSignal(int)),ran,SLOT(pageVolumeSlot(int)));
    connect(ran,SIGNAL(ranProgressBarValue(int,int)),this,SLOT(updateProgressBar(int,int)));


        connect(this,SIGNAL(suspendfifo(int)),fifo,SLOT(guaqififo(int)));
        connect(this,SIGNAL(suspendopt(int)),opt,SLOT(guaqiopt(int)));
        connect(this,SIGNAL(suspendlru(int)),lru,SLOT(guaqilru(int)));
        connect(this,SIGNAL(suspendran(int)),ran,SLOT(guaqiran(int)));

}



//初始化各个按钮的状态
void Widget::initBtnState()
{
//    ui->suspendBtn->setEnabled(false);
//    ui->continueBtn->setEnabled(false);
//    ui->stopBtn->setEnabled(false);
//    ui->restartBtn->setEnabled(false);
    ui->fifoSuspendBtn->setEnabled(false);
    ui->fifoContinueBtn->setEnabled(false);
    ui->optSuspendBtn->setEnabled(false);
    ui->optContinueBtn->setEnabled(false);
    ui->lruSuspendBtn->setEnabled(false);
    ui->lruContinueBtn->setEnabled(false);
    ui->ranSuspendBtn->setEnabled(false);
    ui->ranContinueBtn->setEnabled(false);

}


//同时启动所有线程
void Widget::startBtnSLot(){
if(!inputError())
    return;
cleartext();
//ui->startBtn->setEnabled(false);
//ui->suspendBtn->setEnabled(true);
//ui->stopBtn->setEnabled(true);

ui->fifoStartBtn->setEnabled(false);
ui->fifoSuspendBtn->setEnabled(true);

ui->lruStartBtn->setEnabled(false);
ui->lruSuspendBtn->setEnabled(true);

ui->optStartBtn->setEnabled(false);
ui->optSuspendBtn->setEnabled(true);

ui->ranStartBtn->setEnabled(false);
ui->ranSuspendBtn->setEnabled(true);

        fifo->start();
        opt->start();
        lru->start();
        ran->start();
}




//终止所有正在运行的线程
void Widget::stopBtnSlot(){

    fifo->stop();
    opt->stop();
    lru->stop();
    ran->stop();

     allStopclue();
initBtnState();
ui->fifoStartBtn->setEnabled(true);
ui->lruStartBtn->setEnabled(true);
ui->ranStartBtn->setEnabled(true);
ui->optStartBtn->setEnabled(true);

}

//同时终止所有线程成功的提示
void Widget::allStopclue()
{
    while(1)
    {
        if(fifo->isFinished()&&opt->isFinished()&&lru->isFinished()&&ran->isFinished())
        {
        QMessageBox::warning(this,tr("提示"),tr("所有线程已全部终止!"),QMessageBox::Ok);
        break;
        }
    }

}





//挂起所有线程
void Widget::suspendSlot(){
    emit suspendfifo(0);
    emit suspendlru(0);
    emit suspendopt(0);
    emit suspendran(0);
//    ui->suspendBtn->setEnabled(false);
//    ui->continueBtn->setEnabled(true);
//    ui->restartBtn->setEnabled(false);
//    ui->stopBtn->setEnabled(false);
    QMessageBox::information(this,tr("提示"),tr("所有线程已全部挂起!"),QMessageBox::Yes);
}


//唤醒所有已经挂起的线程
void Widget::continueSLot(){
    emit suspendfifo(1);
    emit suspendlru(1);
    emit suspendopt(1);
    emit suspendran(1);
//    ui->suspendBtn->setEnabled(true);
//    ui->continueBtn->setEnabled(false);
//    ui->restartBtn->setEnabled(true);
//    ui->stopBtn->setEnabled(true);
}


//所有线程重新启动
void Widget::restartBtnSlot(){    //在任何时刻重新启动所有的线程


if(fifo->isRunning()||opt->isRunning()||ran->isRunning()||lru->isRunning())
stopBtnSlot();

  while(1)  {

      if(!fifo->isRunning()&&!opt->isRunning()&&!ran->isRunning()&&!lru->isRunning())
     break;
  }

  cleartext();
startBtnSLot(); //重新开始所有线程


}



//退出程序
void Widget::quitBtnSLot(){
    this->close();
    delete this;

}



//在文本框中分别动态显示页面置换算法
void Widget::opttextshow(QString st,int h){

    ui->textEdit->append(tr("%1<font color=red>%2</font>%3").arg(st.left(h)).arg(st.at(h)).arg(st.right(st.size()-h-1)));
}
void Widget::fifotextshow(QString st,int h){

    ui->textEdit_2->append(tr("%1<font color=red>%2</font>%3").arg(st.left(h)).arg(st.at(h)).arg(st.right(st.size()-h-1)));
    //ui->textEdit_2->setHtml(tr("<font color=red>%1</font>").arg(st.at(h)));

}
void Widget::lrutextshow(QString st,int h){
    ui->textEdit_4->append(tr("%1<font color=red>%2</font>%3").arg(st.left(h)).arg(st.at(h)).arg(st.right(st.size()-h-1)));
}
void Widget::rantextshow(QString st,int h){
    ui->textEdit_5->append(tr("%1<font color=red>%2</font>%3").arg(st.left(h)).arg(st.at(h)).arg(st.right(st.size()-h-1)));
}



//主界面显示产生的随机页面号
void Widget::xulieshow(QString st,int a){

    switch (a) {
    case 0:  ui->textEdit_3->append(tr("OPT随机序列:")+st);
        break;
    case 1:  ui->textEdit_3->append(tr("FIFO序列:")+st);
        break;
    case 2: ui->textEdit_3->append(tr("LRU序列:")+st);
        break;
    case 3: ui->textEdit_3->append(tr("CLOCK序列:")+st);
        break;
    default:
        break;
               }

     emit listshow(st);  //显示运行参数界面的随机序列
}



//显示线程已完成的提示框
void Widget::showclue(int a){
    switch (a) {
    case 0: QMessageBox::information(this,tr("提示"),tr("FIFO已完成!"));

               break;
    case 1: QMessageBox::information(this,tr("提示"),tr("LRU已完成!"));
                break;
    case 2: QMessageBox::information(this,tr("提示"),tr("OPT已完成!"));
               break;
    case 3: QMessageBox::information(this,tr("提示"),tr("CLOCK已完成!"));
              break;
    default:
        break;

    }
    if(fifo->isFinished()&&lru->isFinished()&&opt->isFinished()&&ran->isFinished())
        {
//            ui->suspendBtn->setEnabled(false);
//            ui->stopBtn->setEnabled(false);

           ui->fifoStartBtn->setEnabled(true);
           ui->optStartBtn->setEnabled(true);
           ui->ranStartBtn->setEnabled(true);
           ui->lruStartBtn->setEnabled(true);

           ui->fifoSuspendBtn->setEnabled(false);
           ui->optSuspendBtn->setEnabled(false);
           ui->lruSuspendBtn->setEnabled(false);
           ui->ranSuspendBtn->setEnabled(false);

    }

}








//单个线程的启动、挂起、继续操作

//先来先服务(FIFO)算法
void Widget::fifostartSlot(){   //开始
    if(!inputError())
         return;
    ui->textEdit_2->clear();
    fifo->start();
    ui->parameterBtn->setEnabled(true);
    ui->fifoStartBtn->setEnabled(false);
    ui->fifoSuspendBtn->setEnabled(true);
    ui->fifoContinueBtn->setEnabled(false);
//    ui->startBtn->setEnabled(false);
//    ui->stopBtn->setEnabled(false);

}
void Widget::fifoSuspendBtnSlot()  //暂停
{
    emit suspendfifo(0);
    ui->fifoSuspendBtn->setEnabled(false);
    ui->fifoContinueBtn->setEnabled(true);


}
void Widget::fifoContinutBtnSlot()  //继续
{
    emit suspendfifo(1);
    ui->fifoSuspendBtn->setEnabled(true);
    ui->fifoContinueBtn->setEnabled(false);

}




//最近最久未使用(LRU)算法
void Widget::lrustartSlot(){   //开始
    if(!inputError())
        return;
    ui->textEdit_4->clear();
    lru->start();
    ui->parameterBtn->setEnabled(true);
    ui->lruStartBtn->setEnabled(false);
    ui->lruSuspendBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);
}
void Widget::lruSuspendBtnSlot()  //暂停
{
    emit suspendlru(0);
    ui->lruSuspendBtn->setEnabled(false);
    ui->lruContinueBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);
}
void Widget::lruContinueBtnSlot()  //继续
{
    emit suspendlru(1);
    ui->lruSuspendBtn->setEnabled(true);
    ui->lruContinueBtn->setEnabled(false);
}




//最佳置换(OPT)算法
void Widget::optstartSlot(){    //开始
    if(!inputError())
        return;
    ui->textEdit->clear();
    opt->start();
    ui->parameterBtn->setEnabled(true);
    ui->optStartBtn->setEnabled(false);
    ui->optSuspendBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);
}
void Widget::optSuspendBtnSlot()   //挂起
{
    emit suspendopt(0);
    ui->optSuspendBtn->setEnabled(false);
    ui->optContinueBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);

}
void Widget::optContinueBtnSlot()  //继续
{
    emit suspendopt(1);
    ui->optSuspendBtn->setEnabled(true);
    ui->optContinueBtn->setEnabled(false);
}




//随机置换(RAN)算法
void Widget::ranstartSlot(){     //开始
    if(!inputError())
        return;
    ui->textEdit_5->clear();
    ran->start();
    ui->ranStartBtn->setEnabled(true);
    ui->ranStartBtn->setEnabled(false);
    ui->ranSuspendBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);
}
void Widget::ranSuspendBtnSlot()   //暂停
{
    emit suspendran(0);
    ui->ranSuspendBtn->setEnabled(false);
    ui->ranContinueBtn->setEnabled(true);
    //ui->startBtn->setEnabled(false);
}
void Widget::ranContinueBtnSlot()  //继续
{
    emit suspendran(1);
    ui->ranSuspendBtn->setEnabled(true);
    ui->ranContinueBtn->setEnabled(false);
}






//清空界面
void Widget::cleartext(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();
}

//显示运行参数
void Widget::parameterBtnSLOT(){

    shpare->show();

    //this->setWindowFlags(Qt::WindowStaysOnBottomHint);


}

//显示菜单窗口
void Widget::toolBtnSlot(){
    ui->dockWidget->show();
}

//发射缺页次数的信号
void Widget::missnumSlot(int num,int i,int mtime){
    emit Emitmissnum(num,i,mtime);
}

//发射随机序列数目信号
void Widget::listnumSlot(int listnum)
{
  emit listnumSignal(listnum);
    if(!fifo->isRunning())
          ui->fifoProgressBar->setMaximum(listnum);
    if(!lru->isRunning())
             ui->lruProgressBar->setMaximum(listnum);
    if(!opt->isRunning())
            ui->optProgressBar->setMaximum(listnum);
    if(!ran->isRunning())
             ui->ranProgressBar->setMaximum(listnum);
}

//发射页面数目信号
void Widget::pageVolumeSlot(int v){
    emit pageVolumeSignal(v);
}


//输入错误提示
bool Widget::inputError()
{
    if(ui->listspinBox->value()==0)
         {
         QMessageBox::warning(this,tr("警告"),tr("序列数不能为0"),QMessageBox::Yes);
             return false;
         }
     if(ui->pageVolumespinBox->value()==0)
          {
            QMessageBox::warning(this,tr("警告"),tr("页面数不能为0"),QMessageBox::Yes);
            return false;
          }
    return true;
}



//更新进度条
void Widget::updateProgressBar(int x, int l)
{
    switch (x) {
    case 0: ui->fifoProgressBar->setValue(l);
            break;
    case 1: ui->lruProgressBar->setValue(l);
             break;
    case 2: ui->optProgressBar->setValue(l);
              break;
    case 3: ui->ranProgressBar->setValue(l);
           break;
     default:
        break;
    }

}


//设置重新开始所有线程按钮的状态
//void Widget::setRestartBtn()
//{
//    if(!fifo->isRunning()&&!lru->isRunning()&&!ran->isRunning()&&!opt->isRunning())
//    {
//        ui->restartBtn->setEnabled(true);
//        ui->stopBtn->setEnabled(false);
//    }
//    else
//        ui->restartBtn->setEnabled(false);
//}
void Widget::logBtnSlot()
{
  QProcess::execute("explorer O:\\code\\Qt\\pageReplace\\Log.txt");

}
void Widget::stopmusicSlot()
{
    effect->stop();
}
void Widget::startmusicSlot()
{
    effect->setLoopCount(QSoundEffect::Infinite);
    effect->play();
}
