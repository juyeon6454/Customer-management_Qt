#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QTreeWidgetItem>

class ClientItem : public QTreeWidgetItem
{
public:
    explicit ClientItem(int clientId = 0, QString = "", QString = "", QString = "",QString = "");

    QString getClientName() const;
    void setClientName(QString&);
    QString getPhoneNumber() const;
    void setPhoneNumber(QString&);
    QString getAddress() const;
    void setAddress(QString&);
    QString getEmail() const;
    void setEmail(QString&);
    int ClientId() const;
    bool operator==(const ClientItem &other) const;
};

#endif // CLIENTITEM_H
