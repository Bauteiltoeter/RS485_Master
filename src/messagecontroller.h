#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H


#include <QObject>
#include <QString>
#include <QStringList>

class MessageController : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool messageBoxVisible READ messageBoxVisible NOTIFY messageBoxVisibleChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)

public:
    MessageController();

    static MessageController* Instance()
          {
            static MessageController singleton;
            return &singleton;
          }

    bool messageBoxVisible();
    void addMessage(QString msg);
    QString message();

public slots:
    void messageBoxClosed();

signals:
    void messageBoxVisibleChanged();
    void messageChanged();

private:
    QStringList msgList;


};


#endif // MESSAGECONTROLLER_H
