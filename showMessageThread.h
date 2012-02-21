#ifndef SHOWMESSAGETHREAD_H
#define SHOWMESSAGETHREAD_H

#include <QThread>
#include <QtGui>

#include "message.h"
class ShowMessageThread : public QThread{

public:
    ShowMessageThread(QSystemTrayIcon*& tray, std::queue<Message>* messageQueue):
        QThread(),
        tray_(tray),
        messageQueue_(messageQueue){
    }

    void run(){
        while(true){
            if( !messageQueue_->empty() ){
                Message message = messageQueue_->front();
                messageQueue_->pop();
                showMessage(message.title_, message.text_, message.icon_, message.delay_);
                msleep(message.delay_);
                if(messageQueue_->empty()){
                    //Если мы показали последнее сообщение - убираем его сами чтобы не висело
                    tray_->showMessage("","", QSystemTrayIcon::NoIcon, 0);
                }
            }
        }
        exec();
    }

private:
    QSystemTrayIcon* tray_;
    std::queue<Message>* messageQueue_;

    void showMessage(std::string title, std::string text,  QSystemTrayIcon::MessageIcon icon, size_t delay){
        tray_->showMessage(QString::fromStdString(title),
                           QString::fromStdString(text),
                           icon,
                           delay);
    }
};

#endif // SHOWMESSAGETHREAD_H


