#ifndef SHOWMESSAGETHREAD_H
#define SHOWMESSAGETHREAD_H

#include <QThread>
#include <QtGui>

#include "message.h"
class ShowMessageThread : public QThread{

public:
    ShowMessageThread(QSystemTrayIcon* tray, std::queue<Message>* messageQueue):
            QThread(){
        this->tray = tray;
        this->messageQueue = messageQueue;
    }

    void run(){
        while(true){
            if( !messageQueue->empty() ){
                //Достаём сообщение из Очереди и удаляем его оттуда
                Message message = messageQueue->front();
                messageQueue->pop();

                //Выведем сообщение и заслипаем поток чтобы он не доставал следущее сообщение
                showMessage(message.title, message.text, message.icon, message.delay);
                msleep(message.delay);

                if(messageQueue->empty()){
                    //Если мы показали последнее сообщение - убираем его сами чтобы не висело
                    tray->showMessage("","", QSystemTrayIcon::NoIcon, 0);
                }
            }
        }
        exec();
    }

private:
    QSystemTrayIcon* tray;
    std::queue<Message>* messageQueue;

    void showMessage(std::string title, std::string text,  QSystemTrayIcon::MessageIcon icon, size_t delay){
        tray->showMessage(QString::fromLocal8Bit(title.c_str()),
                          QString::fromLocal8Bit(text.c_str()),
                          icon,
                          delay);
    }
};

#endif // SHOWMESSAGETHREAD_H


