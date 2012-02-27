#include "trayMessageQueue.h"

//todo сделать чтобы trayMessageQueue был friend с showMessageThread , чтобы был постоянный доступ к tray и queue
TrayMessageQueue::TrayMessageQueue(QSystemTrayIcon* tray, size_t defaultDelay){
    this->defaultDelay = defaultDelay;

    messageThread = new ShowMessageThread(tray, &messageQueue);
    messageThread->start();
}

void TrayMessageQueue::addMessage(QString title, QString text, QSystemTrayIcon::MessageIcon icon, size_t delay){
    delay = (delay == 0) ? defaultDelay : delay;
    addMessage(Message(title, text, icon, delay));
}

void TrayMessageQueue::addMessage(Message message){
    messageQueue.push(message);
}

void TrayMessageQueue::addMessage(QString messageTemplateName){

    if (messageTemplates.find(messageTemplateName) != messageTemplates.end()){
        addMessage(messageTemplates[messageTemplateName]);
    }else{
    	// Если шаблона с таким названием нет - в терей будет выведено сообщение об ошибке
        QString errorMessage = "'" + messageTemplateName + "' - unknown template.";
        addMessage("Internal Error", errorMessage, QSystemTrayIcon::Warning, 3000);
    }
}

void TrayMessageQueue::addMessageTemplate(QString messageTemplateName, QString title, QString text, QSystemTrayIcon::MessageIcon icon, size_t delay){
    delay = (delay == 0) ? defaultDelay : delay;
    messageTemplates[messageTemplateName] = Message(title, text, icon, delay);
}


void TrayMessageQueue::removeMessageTemplate(QString messageTemplateName){
    std::map<QString, Message>::iterator it = messageTemplates.find(messageTemplateName);
    if (it != messageTemplates.end())
        messageTemplates.erase(it);
}
