#include "opt.h"
#include"creatrandlist.h"
#include<QMessageBox>
#include<QtAlgorithms>
OPT::OPT()
{
    a=2;     //挂起的参数
    missnum=0;    //缺页次数
    mtime=0;     //内存访问时间
    i=0;
    stopped=false;
    connect(this,SIGNAL(finished()),this,SLOT(endclue()));   //提示正常结束

}
OPT::~OPT(){

}


//线程执行run函数
void OPT::run(){

 state=true;
    list1=CreateRanlist(listnum);
    st=list1.join("");
    emit xulie(st,0);
     QList<QString>::iterator iter;

     for(iter=list1.begin();iter!=list1.end()&&stopped==false;++iter)
     {
         if(a==0)       //设置线程的挂起操作
         {
             mutex.lock();
             condition.wait(&mutex);    //挂起当前线程
             mutex.unlock();
         }
         if(list2.contains(*iter))//判断当前访问页面是否存在
             {
             sleep(1);
             h=list2.indexOf(*iter);
             mtime+=4;
              }
         if(!list2.contains(*iter))
         {

             if(list2.size()<pagevolume)   //内存没有满
                     {
                        list2.append(*iter);
                        h=list2.indexOf(*iter);
                         sleep(2);
                     }

             else         //内存已满，需要置换

             {

                 QList<QString>::iterator ite;
                for(ite=list2.begin();ite!=list2.end();++ite)
                    map.insert(i++,list1.indexOf(*ite,iter-list1.begin())); //将从序列list1当前位置开始找到
                                                                          //的位置加入map容器中，键从0开始


                QMap<int,int>::iterator p;
                int flag=0;
                for(p=map.begin();p!=map.end();++p)
                {

                if(p.value()==-1){
                     list2.replace(p.key(),*iter);   //有后面不再出现的页面号
                     h=p.key();flag=1;
                     break;
                }

                }
                if(flag==0)
                {
                    QList <int>keys=map.uniqueKeys();
                    foreach (int f, keys) {
                        foreach (int j, map.values(f)) {
                          list3.append(j);        //加入到list3
                        }


                    }
                    QList<int>::iterator iter2;
                    std::stable_sort(list3.begin(),list3.end());  //稳定排序
                    iter2=list3.end();
                    --iter2;
                    QMap<int,int>::iterator p;
                    for(p=map.begin();p!=map.end();++p)
                    {
                        if(p.value()==*iter2)
                        {
                            h=p.key();
                            break;
                        }
                    }




                    list2.replace(h,*iter);   //替换
                }

                 sleep(3);
                 list3.clear();
                 map.clear();

         }
             missnum++;
             mtime+=14;


}

         str1=list2.join("");      //转化为字符串

         emit optpage(str1,h);//向主窗口发射显示更新的信号
         emit missnumSignal(missnum,2,mtime);
           emit optProgressBarValue(2,iter-list1.begin()+1);
           i=0;

     }
     initistate();

}

void OPT::endclue(){    //发射线程正常结束的提示信号

    if(state)

        emit clueshow(2);


}
void OPT::guaqiopt(int x){
    a=x;
    if(a==1)
    {
        condition.wakeAll();   //唤醒被挂起的线程
    }
}

void OPT::listnumSlot(int n){
    if(!isRunning())
    listnum=n;
}
void OPT::pageVolumeSlot(int v){
    if(!isRunning())                //防止正在运行时改变页面容量
    pagevolume=v;
}
void OPT::stop(){

    state=false;   //判断为正常结束，不显示结束的提示框

    stopped=true;     //从循环中跳出，结束循环


}
void OPT::initistate()
{
    list2.clear();
    list1.clear();
    map.clear();
    stopped=false;
    missnum=0;
    mtime=0;
    i=0;
}
