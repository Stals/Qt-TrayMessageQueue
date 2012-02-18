#ifndef TRAYMESSAGEQUEUE_H
#define TRAYMESSAGEQUEUE_H
#include <queue>
#include <string>
//#include <map> / <vector>

#include <QSystemTrayIcon>

//#include "showMessageThread.h"

class TrayMessageQueue{
public:
	enum MessageIcon{
    	NoIcon,
        Information,
        Warning,
        Critical
	};

	TrayMessageQueue(QSystemTrayIcon*& tray, size_t defaultDelay = 1000);
	void addMessage(std::string titile, //  заголовок сообщение
	 				std::string text, // текст сообщения
	 				size_t delay = 0, // сколько сообщение будет на экране (если указан 0 - будет использоваться задержка по умолчанию)
	 				MessageIcon icon = NoIcon); // иконка сообщения трея. Доступны следуюшие: NoIcon, Information, Warning, Critical
	//void addMessage(std::string titile, std::string text, std::string messageType);

private:
	QSystemTrayIcon* tray_;
	struct Message{
        Message(MessageIcon icon, std::string title, std::string text, size_t delay) :
            icon_(icon),
            title_(title),
            text_(text),
            delay_(delay){
        }

        MessageIcon icon_;
        std::string title_;
        std::string text_;
        size_t delay_;
	};

	std::queue<Message> messageQueue;
	//std::map<std::string, MessageType> messageTypes; 
	size_t defaultDelay_;
	//ShowMessageThread *messageThread;

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
