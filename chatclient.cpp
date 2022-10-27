#include "chatclient.h"
#include "ui_chatclient.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDataStream>
#include <QTcpSocket>
#include <QApplication>
#include <QThread>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>
#include <QPixmap>

#define BLOCK_SIZE      1024

ChatClient::ChatClient(QWidget *parent) :
    QWidget(parent), isSent(false),ui(new Ui::ChatClient)
{
    ui->setupUi(this);                                  //

    QPixmap pix("C:/CSApp/build-CSApp-Desktop_Qt_6_3_2_MSVC2019_64bit-Debug/image/a.png");
    ui->label_pic->setPixmap(pix);
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->ipAddressLineEdit->setText("127.0.0.1");
    QRegularExpression re("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegularExpressionValidator validator(re);
    ui->ipAddressLineEdit->setPlaceholderText("Server IP Address");
    ui->ipAddressLineEdit->setValidator(&validator);//포트번호 칸 수 제한

    ui->portNumLineEdit->setText(QString::number(PORT_NUMBER));
    ui->portNumLineEdit->setInputMask("00000;_");     //포트번호 입력 5자리 제한
    ui->portNumLineEdit->setPlaceholderText("Server Port No");
    ui->messageTextEdit->setReadOnly(true);

    connect(ui->messageLineEdit, SIGNAL(returnPressed( )), SLOT(sendData( )));
    connect(ui->messageLineEdit, SIGNAL(returnPressed( )), ui->messageLineEdit, SLOT(clear( )));

    connect(ui->sendPushButton, SIGNAL(clicked( )), SLOT(sendData( )));
    connect(ui->sendPushButton, SIGNAL(clicked( )), ui->messageLineEdit, SLOT(clear( )));
    ui->messageLineEdit->setEnabled(false);
    ui->sendPushButton->setEnabled(false);

    connect(ui->fileTransferPushButton, SIGNAL(clicked( )), SLOT(sendFile( )));
    ui->fileTransferPushButton->setDisabled(true);

    connect(ui->logOutPushButton, SIGNAL(clicked( )), this, SLOT(close( )));

    ///////////////////////////////////////////////\


    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QAbstractSocket::errorOccurred,
            [=]{ qDebug( ) << clientSocket->errorString( ); });
    connect(clientSocket, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientSocket, SIGNAL(disconnected( )), SLOT(disconnect( )));

//    QSettings settings("ChatClient", "Chat Client");
//    ui->nameLineEdit->setText(settings.value("ChatClient/ID").toString());

    /* 파일 전송을 위한 소켓 */
    fileClient = new QTcpSocket(this);
    connect(fileClient, SIGNAL(bytesWritten(qint64)), SLOT(goOnSend(qint64)));
//    connect(fileClient, SIGNAL(disconnected( )), fileClient, SLOT(deletelater( )));

    progressDialog = new QProgressDialog(0);
    progressDialog->setAutoClose(true);
    progressDialog->reset();

    connect(ui->chatInPushButton, &QPushButton::clicked,
            [=]{
        if(ui->chatInPushButton->text() == tr("Chat In"))  {
            sendProtocol(Chat_In, ui->nameLineEdit->text().toStdString().data());
            ui->chatInPushButton->setText(tr("Chat Out"));
            ui->messageLineEdit->setEnabled(true);
            ui->sendPushButton->setEnabled(true);
            ui->fileTransferPushButton->setEnabled(true);
            ui->nameLineEdit->setDisabled(true);
            ui->ipAddressLineEdit->setDisabled(true);
            ui->portNumLineEdit->setDisabled(true);
        }else if(ui->chatInPushButton->text() == tr("Chat Out"))  {
            sendProtocol(Chat_Out, ui->nameLineEdit->text().toStdString().data());
            ui->chatInPushButton->setText(tr("Chat In"));
            ui->messageLineEdit->setDisabled(true);
            ui->sendPushButton->setDisabled(true);
            ui->fileTransferPushButton->setDisabled(true);
            ui->nameLineEdit->setEnabled(true);
            ui->ipAddressLineEdit->setEnabled(true);
            ui->portNumLineEdit->setEnabled(true);
        }
    } );
    setWindowTitle(tr("Chat Client"));
}

ChatClient::~ChatClient()
{
    clientSocket->close( );
//    QSettings settings("ChatClient", "Chat Client");
//    settings.setValue("ChatClient/ID", ui->nameLineEdit->text());
    delete ui;
}

void ChatClient::closeEvent(QCloseEvent*)
{
    sendProtocol(Chat_LogOut, ui->nameLineEdit->text().toStdString().data());
    clientSocket->disconnectFromHost();
    if(clientSocket->state() != QAbstractSocket::UnconnectedState)
        clientSocket->waitForDisconnected();
}



void ChatClient::receiveData( )
{
    QTcpSocket *clientSocket = dynamic_cast<QTcpSocket *>(sender( ));
    if (clientSocket->bytesAvailable( ) > BLOCK_SIZE) return;
    QByteArray bytearray = clientSocket->read(BLOCK_SIZE);

    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
    memset(data, 0, 1020);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);

    switch(type) {
    case Chat_Talk:
        if(flag==0){
        ui->messageTextEdit->append(QString(data));
        ui->messageLineEdit->setEnabled(true);
        ui->sendPushButton->setEnabled(true);
        ui->fileTransferPushButton->setEnabled(true);
        }
        else{
        ui->messageTextEdit->setReadOnly(true);
        ui->messageLineEdit->setDisabled(true);
        ui->sendPushButton->setDisabled(true);
        ui->fileTransferPushButton->setDisabled(true);
        }
        break;
    case Chat_KickOut:
        flag = 1;
        QMessageBox::critical(this, tr("Chatting Client"), \
                              tr("Kick out from Server"));
        ui->messageLineEdit->setDisabled(true);
        ui->sendPushButton->setDisabled(true);
        ui->fileTransferPushButton->setDisabled(true);
        ui->nameLineEdit->setReadOnly(false);
        break;
    case Chat_Invite:
        flag = 0;
        QMessageBox::critical(this, tr("Chatting Client"), \
                              tr("Invited from Server"));
        ui->messageLineEdit->setEnabled(true);
        ui->sendPushButton->setEnabled(true);
        ui->fileTransferPushButton->setEnabled(true);
        ui->nameLineEdit->setReadOnly(true);
        break;

    case Chat_LogInCheck:
        ui->nameLineEdit->clear();
        ui->chatInPushButton->setDisabled(true);
        ui->sendPushButton->setDisabled(true);
        ui->fileTransferPushButton->setDisabled(true);
        ui->logInPushButton->setEnabled(true);
        break;

    };
}

void ChatClient::disconnect( )
{
    QMessageBox::critical(this, tr("Chatting Client"), \
                          tr("Disconnect from Server"));
    ui->messageLineEdit->setEnabled(false);
    ui->nameLineEdit->setReadOnly(false);
    ui->sendPushButton->setEnabled(false);
    ui->logInPushButton->setText(tr("Log in"));
}

void ChatClient::sendProtocol(Chat_Status type, char* data, int size)
{
    QByteArray dataArray;           // 소켓으로 보낼 데이터를 채우고
    QDataStream out(&dataArray, QIODevice::WriteOnly);
    out.device()->seek(0);
    out << type;
    out.writeRawData(data, size);
    clientSocket->write(dataArray);     // 서버로 전송
    clientSocket->flush();
    while(clientSocket->waitForBytesWritten());
}


void ChatClient::sendData(  )
{
    QString str = ui->messageLineEdit->text( );
    if(str.length( )) {
        QByteArray bytearray;
        bytearray = str.toUtf8( );
        ui->messageTextEdit->append("<font color=blue>나</font> : " + str);
        sendProtocol(Chat_Talk, bytearray.data());
    }
}


void ChatClient::goOnSend(qint64 numBytes) // Start sending file content
{
    byteToWrite -= numBytes; // Remaining data size
    outBlock = file->read(qMin(byteToWrite, numBytes));
    fileClient->write(outBlock);

    progressDialog->setMaximum(totalSize);
    progressDialog->setValue(totalSize-byteToWrite);

    if (byteToWrite == 0) { // Send completed
        qDebug("File sending completed!");
        progressDialog->reset();
    }
}

void ChatClient::sendFile() // Open the file and get the file name (including path)
{
    loadSize = 0;
    byteToWrite = 0;
    totalSize = 0;
    outBlock.clear();

    QString filename = QFileDialog::getOpenFileName(this);
    file = new QFile(filename);
    file->open(QFile::ReadOnly);

    qDebug() << QString("file %1 is opened").arg(filename);
    progressDialog->setValue(0); // Not sent for the first time
    if (!isSent) { // Only the first time it is sent, it happens when the connection generates the signal connect
        fileClient->connectToHost(ui->ipAddressLineEdit->text( ),
                                  ui->portNumLineEdit->text( ).toInt( ) + 1);

        isSent = true;
    }
    // When sending for the first time, connectToHost initiates the connect signal to call send, and you need to call send after the second time

    byteToWrite = totalSize = file->size(); // The size of the remaining data
    loadSize = 1024; // The size of data sent each time

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out << qint64(0) << qint64(0) << filename;

    totalSize += outBlock.size(); // The total size is the file size plus the size of the file name and other information
    byteToWrite += outBlock.size();

    out.device()->seek(0); // Go back to the beginning of the byte stream to write a qint64 in front, which is the total size and file name and other information size
    out << totalSize << qint64(outBlock.size());

    fileClient->write(outBlock); // Send the read file to the socket

    progressDialog->setMaximum(totalSize);
    progressDialog->setValue(totalSize-byteToWrite);
    progressDialog->show();

    qDebug() << QString("Sending file %1").arg(filename);
}


void ChatClient::on_logInPushButton_clicked()
{
    clientSocket->connectToHost(ui->ipAddressLineEdit->text( ),
                                ui->portNumLineEdit->text( ).toInt( ));
    clientSocket->waitForConnected();
    sendProtocol(Chat_Login, ui->nameLineEdit->text().toStdString().data());
    ui->chatInPushButton->setEnabled(true);
    ui->fileTransferPushButton->setDisabled(true);
}

void ChatClient::on_logOutPushButton_clicked()
{
    sendProtocol(Chat_LogOut, ui->nameLineEdit->text().toStdString().data());
    ui->nameLineEdit->setReadOnly(false);
    //server창 꺼지지 않게
}
