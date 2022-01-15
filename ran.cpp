#include "ran.h"
#include"creatrandlist.h"
#include<QMessageBox>
RAN::RAN()
{
    a=2;   //挂起线程的参数
    missnum=0;      //缺页次数
    mtime=0;       //内存访问时间

    stopped=false;     //终止线程
    connect(this,SIGNAL(finished()),this,SLOT(endclue()));   //显示线程正常结束

}
RAN::~RAN()
{

}


//线程执行run函数
void RAN::run(){
    state=true;    //state用来判断线程是否异常终止，不显示完成的对话框
    list1=CreateRanlist(listnum);
    str=list1.join("");
    emit xulie(str,3);
    qsrand((int)time(0));
    QList <QString>::const_iterator iter;
    for(iter=list1.constBegin();iter!=list1.constEnd()&&stopped==false;iter++)
    {
        if(a==0)
        {
        mutex.lock();
        condition.wait(&mutex);
        mutex.unlock();
        }
        if(list2.contains(*iter))
        {
            h=list2.indexOf(*iter);
            sleep(1);
            mtime+=4;
        }
        if(!list2.contains(*iter))
        {

            if(list2.size()<pagevolume)
            {
                list2.append(*iter);
                h=list2.indexOf(*iter);
                 sleep(2);
            }
            else{
            x=qrand()%pagevolume;
            list2[x]=*iter;
            h=x;
              sleep(3);
                }
            missnum++;
            mtime+=14;

        }
        str=list2.join("");

        emit rantextshow(str,h);
        emit missnumSignal(missnum,3,mtime);
        emit ranProgressBarValue(3,iter-list1.constBegin()+1);
    }
initistate();

}
void RAN::endclue(){  //线程正常结束的提示

    if(state)
    {
        emit clueshow(3);

    }
}
void RAN::guaqiran(int x){     //挂起线程
    a=x;
    if(a==1)

        condition.wakeAll();

}
void RAN::judgeTerminal(int i){      //判断是否异常终止
   if(!i)
    state=false;
   else state=true;
}
void RAN::ListnumSlot(int n){    //随机序列的个数
    if(!isRunning())
    listnum=n;
}
void RAN::pageVolumeSlot(int v){   //内存中最多容纳的页面数
    if(!isRunning())        //防止正在运行时改变容量
    pagevolume=v;
}
void RAN::stop(){   //线程的终止
     state=false;    //判断为强制终止线程，不显示线程正常结束的对话框
    stopped=true;    //结束循环，结束线程


}
void RAN::initistate()   //状态的初始化
{
    list2.clear();
    list1.clear();
    stopped=false;
    missnum=0;
    mtime=0;
}
