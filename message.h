#ifndef MESSAGE_H
#define MESSAGE_H

struct Message{
    Message(){}
    Message(QString title, QString text, QSystemTrayIcon::MessageIcon icon, size_t delay){
        this->title = title;
        this->text = text;
        this->icon = icon;
        this->delay = delay;
    }

    QString title;
    QString text;
    QSystemTrayIcon::MessageIcon icon;
    size_t delay;
};
#endif // MESSAGE_H
