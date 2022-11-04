#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientManagerForm;
class ProductManagerForm;
class OrderManagerForm;
class ChatClient;
class ChatServerForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool createConnection();

private slots:
    void on_actionClientInfo_triggered();
    void on_actionProductInfo_triggered();
    void on_actionOrderInfo_triggered();
    void on_actionChatManager_triggered();
    void on_actionChat_triggered();         /*tool bar를 눌렀을 때 각 Form으로 이동*/

private:
    Ui::MainWindow *ui;
    ClientManagerForm *clientForm;       //clientForm
    ProductManagerForm *productForm;     //productForm
    OrderManagerForm *orderForm;         //orderForm
    ChatServerForm *serverForm;          //serverForm
    ChatClient *chatForm;                //chatForm
};
#endif // MAINWINDOW_H
