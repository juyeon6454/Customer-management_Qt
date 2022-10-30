#include "logthread.h"

#include <QTreeWidgetItem>
#include <QFile>
#include <QDateTime>

LogThread::LogThread(QObject *parent)
    : QThread{parent}
{
    QString format = "yyyyMMdd_hhmmss";
    filename = QString("log_%1.txt").arg(QDateTime::currentDateTime().toString(format));
    //로그 파일 이름을 log_년월일시간으로 지정
}

void LogThread::run()
{
    Q_FOREVER {         // 무한 반복
        saveData();
        sleep(60);      // 1분마다 저장
    }
}

void LogThread::appendData(QTreeWidgetItem* item)
{
    itemList.append(item);  //itemlist에 요소 추가
}

void LogThread::saveData()
{
    if(itemList.count() > 0) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //지정한 파일 이름으로 쓰기용 저장
            return;

        QTextStream out(&file);
        foreach(auto item, itemList) {                          //itemlist는 메세지 전송, 파일 전송시 저장
            out << item->text(0) << ", ";
            out << item->text(1) << ", ";
            out << item->text(2) << ", ";
            out << item->text(3) << ", ";
            out << item->text(4) << ", ";
            out << item->text(5) << "\n";                       //해당 형식으로 itemlist가 담긴 파일을 반환
        }
        file.close();
    }
}
