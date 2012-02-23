#include "trayMessageQueue.h"


//todo сделать чтобы trayMessageQueue был friend с showMessageThread , чтобы был постоянный доступ к tray и queue
TrayMessageQueue::TrayMessageQueue(QSystemTrayIcon* tray, size_t defaultDelay){
    this->tray = tray;
    this->defaultDelay = defaultDelay;

    messageThread = new ShowMessageThread(tray, &messageQueue);
    messageThread->start();
}

void TrayMessageQueue::addMessage(std::string title, std::string text, QSystemTrayIcon::MessageIcon icon, size_t delay){
    delay = (delay == 0) ? defaultDelay : delay;
    addMessage(Message(title, text, icon, delay));
}

void TrayMessageQueue::addMessage(Message message){
    messageQueue.push(message);
}

void TrayMessageQueue::addMessage(std::string messageTemplateName){
    // Если шалона с таким названием нет - вылетит исключение
    addMessage(messageTemplates[messageTemplateName]);
}

void TrayMessageQueue::addMessageTemplate(std::string messageTemplateName, std::string title, std::string text, QSystemTrayIcon::MessageIcon icon, size_t delay){
    delay = (delay == 0) ? defaultDelay : delay;
    messageTemplates[messageTemplateName] = Message(title, text, icon, delay);
}


void TrayMessageQueue::removeMessageTemplate(std::string messageTemplateName){
    std::map<std::string, Message>::iterator it = messageTemplates.find(messageTemplateName);
    if (it != messageTemplates.end())
        messageTemplates.erase(it);
}
