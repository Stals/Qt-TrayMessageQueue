#ifndef TRAYMESSAGEQUEUE_H
#define TRAYMESSAGEQUEUE_H
#include <queue>
#include <string>
//#include <map> / <vector>

#include <QSystemTrayIcon>

#include "message.h"
#include "showMessageThread.h"

/*
Класс позволяет просто выводить сообщения в Tray
так чтобы сообщение не перекрывало предведущее даже не дав ему показаться, позволяя указать сколько каждое сообщение будет показываться пользователю.
*/
class TrayMessageQueue{
public:
    TrayMessageQueue(QSystemTrayIcon* tray, size_t defaultDelay = 2000); // defaultDelay указывается в миллисекундах

    // Добавляем сообщение в Очередь для последующего показа
    void addMessage(std::string title, //  заголовок сообщение
                    std::string text, // текст сообщения
                    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::NoIcon, // иконка сообщения трея. Доступны следуюшие: NoIcon, Information, Warning, Critical
                    size_t delay = 0 // сколько миллисекунд сообщение будет на экране (если указан 0 - будет использоваться задержка по умолчанию)
                    );

private:
    QSystemTrayIcon* tray;
    size_t defaultDelay;

    std::queue<Message> messageQueue;
    ShowMessageThread* messageThread;

    void addMessage(Message message);

};


#endif // TRAYMESSAGEQUEUE_H
