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
так чтобы сообщение не перекрывало сразуже предведущее, позволяя указать сколько каждое сообщение будет показываться пользователю.
*/
class TrayMessageQueue{
public:
    TrayMessageQueue(QSystemTrayIcon*& tray, size_t defaultDelay = 1000); // defaultDelay указывается в миллисекундах

    // Добавляем сообщение в Очередь для последующего показа
    void addMessage(std::string title, //  заголовок сообщение
                    std::string text, // текст сообщения
                    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::NoIcon, // иконка сообщения трея. Доступны следуюшие: NoIcon, Information, Warning, Critical
                    size_t delay = 0 // сколько миллисекунд сообщение будет на экране (если указан 0 - будет использоваться задержка по умолчанию)
                    ); 
    
    //void addMessage(std::string titile, std::string text, std::string messageType);

private:
    QSystemTrayIcon* tray_; 
    size_t defaultDelay_;

    std::queue<Message> messageQueue;
    //std::map<std::string, MessageType> messageTypes;
    ShowMessageThread* messageThread;

    void addMessage(Message message);

    /*
 	struct MessageType{
		MessageType(MessageIcon icon, size_t delay) :
			icon_(icon),
			delay_(delay){
		}
  		MessageIcon icon_;
  		size_t delay_;
 	};
 	*/

};


#endif // TRAYMESSAGEQUEUE_H
