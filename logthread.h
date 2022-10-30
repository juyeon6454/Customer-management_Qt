#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <QList>

class QTreeWidgetItem;

class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = nullptr);

private:
    void run();                         //60초에 한 번 저장

    QList<QTreeWidgetItem*> itemList;   //기록을 저장하는 list
    QString filename;                   //날짜로 파일 이름 저장

signals:
    void send(int data);

public slots:
    void appendData(QTreeWidgetItem*);  //기록 data append
    void saveData();                    //txt 파일로 저장
};

#endif // LOGTHREAD_H
