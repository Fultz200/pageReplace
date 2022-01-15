#ifndef CREATRANDLIST_H
#define CREATRANDLIST_H
#include<QList>
#include<QTime>
static QList <QString> CreateRanlist(int listnum){


    QList <QString>list1;

   // qsrand((int)time(0));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    int i;
    for(i=0;i<listnum;i++)
    {
         QVariant x=qrand()%10;

         list1.append(x.toString());
    }
    return list1;
}
#endif // CREATRANDLIST_H
