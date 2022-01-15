#ifndef WIDGET_H
#define WIDGET_H
#include"fifo.h"
#include"opt.h"
#include"lru.h"
#include"ran.h"
#include"showparameter.h"
#include <QWidget>
#include<QList>
#include<QStringList>
#include<QTimer>
#include<QWaitCondition>
#include<QSharedPointer>
#include<QSoundEffect>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void objectFunction();
    void cleartext();
    void allStopclue();
    bool inputError();
    void initBtnState();

private:
    Ui::Widget *ui;
    QList <int> list;
   QString str;
   FIFO *fifo;
   OPT *opt;
   LRU *lru;
   RAN *ran;
   /*QSharedPointer <FIFO> fifo;
   QSharedPointer <OPT> opt;
   QSharedPointer <LRU> lru;
   QSharedPointer <RAN> ran;
   QWaitCondition condition;*/
   ShowParameter *shpare;
   QTimer *timer,*timer1;
   QSoundEffect *effect;
private slots:
   void opttextshow(QString st,int h);
   void fifotextshow(QString st,int h);
   void lrutextshow(QString st,int h);
   void xulieshow(QString st,int a);
   void rantextshow(QString st,int h);
   void startBtnSLot();
   void stopBtnSlot();
   void quitBtnSLot();
   void showclue(int a);
   void fifostartSlot();
   void lrustartSlot();
   void optstartSlot();
   void ranstartSlot();
   void suspendSlot();
   void continueSLot();
   void restartBtnSlot();
   void parameterBtnSLOT();
   void toolBtnSlot();
   void missnumSlot(int num,int i,int mtime);
   void listnumSlot(int listnum);
   void pageVolumeSlot(int v);
   void fifoSuspendBtnSlot();
   void fifoContinutBtnSlot();
   void optSuspendBtnSlot();
   void optContinueBtnSlot();
   void lruSuspendBtnSlot();
   void lruContinueBtnSlot();
   void ranSuspendBtnSlot();
   void ranContinueBtnSlot();
   void updateProgressBar(int x,int l);
   void setRestartBtn();
   void logBtnSlot();
   void stopmusicSlot();
   void startmusicSlot();


signals:
   void  suspendfifo(int a);
   void suspendopt(int a);
   void suspendlru(int a);
   void suspendran(int a);
   void Emitmissnum(int num,int i,int mtime);
   void listnumSignal(int n);
   void pageVolumeSignal(int v);
   void listshow(QString s);


};

#endif // WIDGET_H
