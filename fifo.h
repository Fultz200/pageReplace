#ifndef FIFO_H
#define FIFO_H
#include<QTimer>
#include<QDebug>
#include<time.h>
#include<QVariant>
#include<QThread>
#include<QList>
#include<QQueue>
#include<QMutex>
#include<QWaitCondition>
class FIFO : public QThread
{
    Q_OBJECT
public:
    FIFO();
    ~FIFO();
    void run();
    void stop();
    void initstate();
private:
   QStringList list1;
   QString str,str1;
   QStringList list2;
   QTimer *timer;
   QQueue <QString> que;
   QMutex mutex;
   QWaitCondition conditon;
   int a,h,missnum,listnum,pagevolume,mtime,location;
   bool state,stopped;

signals:
   void pageshow(QString str,int h);
   void xulie(QString str,int a);
   void clueshow(int a);
   void missnumSignal(int n,int i,int j);
   void stopclue(int a);
   void fifoProgressValue(int x,int l);
private slots:
   void endclue();
   void guaqififo(int x);
   void ListnumSlot(int n);
   void pageVolumeSlot(int v);

};

#endif // FIFO_H
