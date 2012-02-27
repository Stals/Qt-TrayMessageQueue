#ifndef TRAYMESSAGEQUEUE_H
#define TRAYMESSAGEQUEUE_H
#include <queue>
#include <string>
#include <map>

#include <QSystemTrayIcon>

#include "message.h"
#include "showMessageThread.h"

/*
Класс позволяет просто выводить сообщения в Tray
так чтобы сообщение не перекрывало предведущее даже не дав ему показаться, позволяя указать сколько каждое сообщение будет показываться пользователю.
Поддерживается unicode
Также есть возможность добавить шаблонное сообщение чтобы в последствии его выводить передавая только название этого шаблона.
*/
class TrayMessageQueue{
public:
    TrayMessageQueue(QSystemTrayIcon* tray, size_t defaultDelay = 2000); // defaultDelay указывается в миллисекундах


    // Добавляем сообщение в Очередь для последующего показа
    void addMessage(QString title, //  заголовок сообщение
                    QString text, // текст сообщения
                    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::NoIcon, // иконка сообщения трея. Доступны следуюшие: NoIcon, Information, Warning, Critical
                    size_t delay = 0); // сколько миллисекунд сообщение будет на экране (если указан 0 - будет использоваться задержка по умолчанию)

    // Добавляет сообщение из списка шаблонных в Очередь по его названию
    void addMessage(QString messageTemplateName);

    // Добавляет сообщение в список шаблонов
    // Note: Добавление сообщения в список щаблонов не добавит его в очередь для показа
    void addMessageTemplate(QString messageTemplateName, // Название шаблона для последущего быстрого добавляеня в Очередь
                            QString title,
                            QString text,
                            QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::NoIcon,
                            size_t delay = 0); // Если указан 0 - будет использоваться задержка по умолчанию

    // Удаляет шаблонное сообщение из списка если оно там есть
    void removeMessageTemplate(QString messageTemplateName);


private:
    size_t defaultDelay;

    std::queue<Message> messageQueue;
    std::map<QString, Message> messageTemplates; // Хранит шаблоны сообщений
    
    ShowMessageThread* messageThread;

    void addMessage(Message message);
};


#endif // TRAYMESSAGEQUEUE_H
