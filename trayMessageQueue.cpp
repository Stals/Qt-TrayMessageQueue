#include "trayMessageQueue.h"


//todo сделать чтобы trayMessageQueue был friend с showMessageThread , чтобы был постоянный доступ к tray и queue
TrayMessageQueue::TrayMessageQueue(QSystemTrayIcon*& tray, size_t defaultDelay) :
    tray_(tray),
    defaultDelay_(defaultDelay){

    messageThread = new ShowMessageThread(tray_, &messageQueue);
    messageThread->start();
}

void TrayMessageQueue::addMessage(std::string title, std::string text, size_t delay,  QSystemTrayIcon::MessageIcon icon){
    delay = (delay == 0) ? defaultDelay_ : delay; 
    addMessage(Message(icon, title, text, delay));
}

void TrayMessageQueue::addMessage(Message message){
    messageQueue.push(message);
}
