#include "clientitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ClientItem::ClientItem(int clientId, QString clientName, QString phoneNumber, QString address, QString email)
{
    setText(0, QString::number(clientId));
    setText(1, clientName);
    setText(2, phoneNumber);
    setText(3, address);
    setText(4, email);
}

QString ClientItem::getClientName() const
{
    return text(1);
}

void ClientItem::setClientName(QString& clientId)
{
    setText(1, clientId);                            /*QString형 ClientItem 첫 번째 자리*/
}

QString ClientItem::getPhoneNumber() const
{
    return text(2);
}

void ClientItem::setPhoneNumber(QString& phoneNumber)
{
    setText(2, phoneNumber);                        /*QString형 ClientItem 두 번째 자리*/
}

QString ClientItem::getAddress() const
{
    return text(3);
}

void ClientItem::setAddress(QString& address)
{
    setText(3, address);                             /*QString형 ClientItem 세 번째 자리*/
}

QString ClientItem::getEmail() const
{
    return text(4);
}

void ClientItem::setEmail(QString& email)
{
    setText(4, email);                               /*QString형 ClientItem 네 번째 자리*/
}


int ClientItem::ClientId() const
{
    return text(0).toInt();                          /*int형 ClientItem 0번째 자리 return으로 반환받기 때문에 값을 주거나 얻을 필요 없음 */
}


bool ClientItem::operator==(const ClientItem &other) const {
    return (this->text(1) == other.text(1));
}
