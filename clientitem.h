#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QTreeWidgetItem>

class ClientItem : public QTreeWidgetItem
{
public:
    explicit ClientItem(int clientId = 0, QString = "", QString = "", QString = "",QString = "");

    QString getClientName() const;
    void setClientName(QString&);                   /*QString형 ClientItem 첫 번째 자리*/
    QString getPhoneNumber() const;
    void setPhoneNumber(QString&);                  /*QString형 ClientItem 두 번째 자리*/
    QString getAddress() const;
    void setAddress(QString&);                      /*QString형 ClientItem 세 번째 자리*/
    QString getEmail() const;
    void setEmail(QString&);                        /*QString형 ClientItem 네 번째 자리*/
    int ClientId() const;                           /*int형 ClientItem 0번째 자리 return으로 반환받기 때문에 값을 주거나 얻을 필요 없음 */
    bool operator==(const ClientItem &other) const;
};

#endif // CLIENTITEM_H
