#ifndef CHATSERVERFORM_H
#define CHATSERVERFORM_H

#include <QWidget>
#include <QList>
#include <QHash>
#include "chatclient.h"

class QLabel;
class QTcpServer;
class QTcpSocket;
class QFile;
class QProgressDialog;
class LogThread;

namespace Ui {
class ChatServerForm;
}

class ChatServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerForm(QWidget *parent = nullptr);
    ~ChatServerForm();

private:
    const int BLOCK_SIZE = 1024;        //block_size를 1024로 지정 (데이터 크기)
    const int PORT_NUMBER = 8000;       //포트 넘버를 8000으로 지정

    Ui::ChatServerForm *ui;                             //serverform ui
    QTcpServer *chatServer;                             //채팅을 위한 소켓
    QTcpServer *fileServer;                             //파일 전송을 위한 소켓
    QList<QTcpSocket*> clientList;                      //서버에 입장한 clientlist
    QList<int> clientIDList;
    QHash<quint16, QString> clientNameHash;
    QHash<QString, QTcpSocket*> clientSocketHash;       //이름으로 소켓을 찾음
    QHash<QString, int> clientIDHash;                   //id로 소켓을 찾음
    QMenu* menu;                                        //메뉴 생성
    QFile* file;                                        //파일 전송
    QProgressDialog* progressDialog;                    //파일 전송을 프로그레스 다이얼로그로 나타냄
    qint64 totalSize;                                   //다이얼로그 바를 totalSize로 결정
    qint64 byteReceived;                                //받은 byte크기
    QByteArray inBlock;                                 //데이터
    LogThread* logThread;                               //로그를 스레드 사용

private slots:
    void acceptConnection();                /* 파일 서버 (파일 전송을 위한 소켓 생성) */
    void readClient();                      //파일 전송

    void clientConnect( );                  /* 채팅 서버 (채팅을 위한 소켓 생성)*/
    void receiveData( );                    //데이터를 받아 해당 타입에 연결
    void removeClient( );                   //server가 종료되었을 때 로그아웃 상태
    void addClient(int, QString);           //고객리스트 가져옴
    void inviteClient();                    //초대
    void kickOut();                         //강퇴
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos); //우클릭시 액션 메뉴

    void removeServerClient(int, QString);          //client 등록 정보가 사라지면 server list에서도 삭제
    void modifyServerClient(int, int, QString);     //client 등록 정보가 수정되면 server list에서도 수정
    void on_clearPushButton_clicked();              //treewidget에 보여지는 정보 지워줌
};

#endif // CHATSERVERFORM_H

