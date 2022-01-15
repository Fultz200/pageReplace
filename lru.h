#ifndef LRU_H
#define LRU_H
#include<QThread>
#include<QDebug>
#include<QList>
#include<QTimer>

#include<QMutex>
#include<QWaitCondition>
class LRU : public QThread
{
    Q_OBJECT
public:
    LRU();
    ~LRU();
    void run();
    void judgeTerminal(int i);
    void stop();
    void initistate();
private:
    QList<QString>list1;
    QList<QString>list2;
    QList<QString>list3;
    QString str,str1;
    QTimer *timer;
    int a,h,missnum,listnum,pagevolume,mtime;
    QWaitCondition condition;
    QMutex mutex;
    bool state,stopped;
signals:
    void xulie(QString x,int m);
    void lrupage(QString x,int h);
    void clueshow(int a);
    void missnumSignal(int num,int i,int j);
    void lruProgressBarValue(int x,int l);
private slots:
    void endclue();
    void guaqilru(int x);
    void listNumSlot(int n);
    void pageVolumeSlot(int v);
};

#endif // LRU_H
