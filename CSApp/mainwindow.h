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

private slots:
    void on_actionClientInfo_triggered();

    void on_actionProductInfo_triggered();

    void on_actionOrderInfo_triggered();

    void on_actionChatManager_triggered();

    void on_actionChat_triggered();

private:
    Ui::MainWindow *ui;
    ClientManagerForm *clientForm;
    ProductManagerForm *productForm;
    OrderManagerForm *orderForm;
    ChatServerForm *serverForm;
    ChatClient *chatForm;
};
#endif // MAINWINDOW_H
