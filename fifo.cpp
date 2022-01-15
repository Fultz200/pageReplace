#include "fifo.h"
#include"creatrandlist.h"
#include<QtGlobal>
#include<QMessageBox>
FIFO::FIFO()
{
    a=2;   //挂起部分的参数
    missnum=0;  //缺页次数       2ms         2ms                10ms
    mtime=0;//访问内存的时间=查找页表的时间+访问实际物理地址的时间+处理缺页中断的时间
   location=0;
    stopped=false;    //用来终止线程，避免使用危险的terminate函数
    connect(this,SIGNAL(finished()),this,SLOT(endclue()));  //显示正常结束对话框


}
FIFO::~FIFO()
{

}


//线程执行run函数
void FIFO::run(){
    state=true;
    list1=CreateRanlist(listnum);
    str=list1.join(""); //str是list的字符串形式
    emit xulie(str,1);



    QListIterator <QString>iter(list1);            //JAVA风格迭代器

    while(iter.hasNext()&&stopped==false)

    {

        if(a==0)              //暂停当前线程
        {
        mutex.lock();
        conditon.wait(&mutex);
        mutex.unlock();
        }
        QString x=iter.next();

        if(list2.contains(x))     //判断list2中物理块是否包含当前的页面
        {
           h=list2.indexOf(x);
            sleep(1);
           mtime+=4;

        }
        if(!list2.contains(x)){

           if(list2.size()<pagevolume)
               {
                   h=list2.size();
                   list2.append(x);

                   que.append(x);
                   sleep(2);
               }

            else
                 {
              QString m=que.head(); //m表示当前队列的头结点，即第一个入队的页面

              h=list2.indexOf(m);
            list2.replace(list2.indexOf(m),x);//将list2中最先进入队列的页面用当前页面替换掉
            que.dequeue();      //去掉头
            que.enqueue(x); //添加尾


        sleep(3);
                  }
                  missnum++;
                  mtime+=14;
        }
        location++;
        str1=list2.join("");

        emit pageshow(str1,h);
        emit missnumSignal(missnum,0,mtime);
        emit fifoProgressValue(0,location);



}
    initstate();


}
void FIFO::endclue(){
    if(state)
    emit clueshow(0);
}

void FIFO::guaqififo(int x){
   a=x;
   if(a==1)
       conditon.wakeAll();
}
void FIFO::ListnumSlot(int n){
    if(!isRunning())
            listnum=n;
}
void FIFO::pageVolumeSlot(int v)
    {
    if(!isRunning())     //防止正在运行时改变容量
         pagevolume=v;
    }
void FIFO::stop()
{

    state=false;    //判断为强制终止线程，不显示结束的提示框

    stopped=true;   //从循环中跳出，结束循环


}
void FIFO::initstate()
{
    stopped=false;
    missnum=0;
    mtime=0;
    location=0;
    list2.clear();
    que.clear();
    list1.clear();
}

