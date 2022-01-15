#ifndef SHOWPARAMETER_H
#define SHOWPARAMETER_H
#include<QDateTime>
#include <QWidget>
#include<QTimer>
#include<QFile>
#include<QTextStream>
namespace Ui {
class ShowParameter;
}

class ShowParameter : public QWidget
{
    Q_OBJECT

public:
    explicit ShowParameter(QWidget *parent = 0);
    ~ShowParameter();
    void initilabel();
private slots:
    void missnumSLOT(int num,int i,int mtime);
    void listnumSLOT(int listnum);
    void showlist(QString s);
    void updateTime();


private:
    Ui::ShowParameter *ui;
    float n;
   QTimer *timer;
   QFile file;
   QTextStream stream;
};

#endif // SHOWPARAMETER_H
