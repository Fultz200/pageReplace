#ifndef RAN_H
#define RAN_H
#include<QThread>
#include<QList>
#include<QDebug>
#include<time.h>
#include<QTimer>
#include<QWaitCondition>
#include<QMutex>
class RAN : public QThread
{
    Q_OBJECT
public:
    RAN();
    ~RAN();
    void run();
    void judgeTerminal(int i);
    void stop();
    void initistate();
private:
    QList<QString>list1,list2,list3;
    QString str,str1;
    int x,i;
    QTimer *timer;
    int a,h,missnum,listnum,pagevolume,mtime;
    QMutex mutex;
    QWaitCondition condition;
    bool state,stopped;
signals:
    void xulie(QString st,int m);
    void rantextshow(QString st,int h);
    void clueshow(int a);
    void missnumSignal(int num,int i,int j);
    void ranProgressBarValue(int x,int l);

private slots:
    void endclue();
    void guaqiran(int x);
    void ListnumSlot(int n);
    void pageVolumeSlot(int v);
};

#endif // RAN_H
