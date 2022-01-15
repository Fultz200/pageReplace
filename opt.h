#ifndef OPT_H
#define OPT_H
#include<QDebug>
#include<QStringList>
#include<QList>
#include<QMap>
#include<time.h>
#include<QThread>
#include<QtGlobal>
#include<QTimer>
#include<QMutex>
#include<QWaitCondition>
class OPT : public QThread
{
    Q_OBJECT
public:
    OPT();
    ~OPT();
    void run();
    void stop();
    void initistate();
private:
    QList<QString> list1;
    QString st,str1;
    QList<QString> list2;
    QList<int> list3;
    QMap <int,int>map;
    QTimer *timer;
    QMutex mutex;
    QWaitCondition condition;
    int a,h,missnum,listnum,pagevolume,mtime,i;
    bool state,stopped;
private slots:
    void endclue();
    void guaqiopt(int x);
     void listnumSlot(int n);
     void pageVolumeSlot(int v);

signals:
     void xulie(QString str,int a);
    void optpage(QString str,int h);
      void clueshow(int a);
      void missnumSignal(int num,int i,int t);
      void optProgressBarValue(int x,int l);


};

#endif // OPT_H
