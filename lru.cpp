#include "lru.h"
#include"creatrandlist.h"
#include<QMessageBox>
LRU::LRU()
{
    a=2;

    stopped=false;
    missnum=0;
    mtime=0;
    connect(this,SIGNAL(finished()),this,SLOT(endclue()));  //显示正常结束对话框

}
LRU::~LRU()
{

}


//线程执行run函数
void LRU::run(){
     state=true;  //state用来判断是否强制终止
    list1=CreateRanlist(listnum);      //list1是原始随机序列
    str=list1.join("");   //容器转化为字符串
    emit xulie(str,2);                  //发射序列信号
    int m;
    QList<QString>::const_iterator iter;  //迭代器

    for(iter=list1.constBegin();iter!=list1.constEnd()&&stopped==false;++iter)  //遍历随机序列
    {
        if(a==0)      //线程的挂起
        {
        mutex.lock();
        condition.wait(&mutex);
        mutex.unlock();
        }
        if(list2.contains(*iter))  //如果当前访问页面已经在内存中
        {
            list3.move(list3.indexOf(*iter),list3.size()-1);  //将当前访问的页面在list3中的位置移到最后
            h=list2.indexOf(*iter);       //标红
            sleep(1);
            mtime+=4;     //访问内存的有效时间
        }
        if(!list2.contains(*iter))
        {
            if(list2.size()<pagevolume)    //内存未满
               {
                list2.append(*iter);
                list3.append(*iter);
                h=list2.indexOf(*iter);
                sleep(2);
               }
            else
              {
              m=list2.indexOf(list3.takeFirst()); //list3中的第一个结点是要被置换的对象，先将list3中第一个结点在
              list2[m]=*iter;                   //list2中的位置找到，用当前页面替换，将list3中第一个结点删除，
               h=m;                                   //再将当前页面添加到list3的最后面位置上
              list3.append(*iter);
              sleep(3);
              }
            missnum++;
                mtime+=14;
        }
        emit lruProgressBarValue(1,iter-list1.begin()+1);
        str1=list2.join("");
        emit lrupage(str1,h);
        emit missnumSignal(missnum,1,mtime);
    }
    initistate();

}
void LRU::endclue(){      //发射线程正常结束时的提示信号

    if(state)
    {
        emit clueshow(1);
    }
}
void LRU::guaqilru(int x){
    a=x;
    if(a==1)
    {
        condition.wakeAll();   //唤醒被挂起的线程
    }
}

void LRU::judgeTerminal(int i){     //state判断是否异常终止
  if(!i)
    state=false;
  else state=true;
}

void LRU::listNumSlot(int n){
    if(!isRunning())  //防止正在运行时改变序列数
    listnum=n;
}
void LRU::pageVolumeSlot(int v){

    if(!isRunning())      //防止正在运行时改变页面的容量
    pagevolume=v;
}

void LRU::stop(){

     state=false;       //判断为强制终止线程，不显示线程正常结束的对话框
    stopped=true;           //从循环中跳出，结束线程

}

void LRU::initistate()//初始化
{

    stopped=false;
    missnum=0;
    mtime=0;
    list2.clear();
    list3.clear();
    list1.clear();
}
