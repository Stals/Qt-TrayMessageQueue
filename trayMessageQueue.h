#include <queue>
#include <string>

#include <QSystemTrayIcon>

class TrayMessageQueue{
	public:
		enum class MessageIcon{
				NoIcon,
				Information,
				Warning,
				Critical
		};
		TrayMessageQueue(QSystemTrayIcon& tray, size_t defaultDelay = 1000);
		void addMessage(std::string titile, std::string text, size_t delay = defaultDelay, MessageIcon icon = MessageIcon::NoIcon);
		void addMessage(std::string titile, std::string text, std::string messageType);

	private:
		QSystemTrayIcon tray;
		std::queue<Message> messageQueue;
		size_t defaultDelay;
		void addMessage(Message message);

		struct Message{
			Message(MessageIcon icon, std::string title, std::string text_, size_t delay) :
				icon_(icon),
				title_(titile),
				text_(text),
				delay_(delay){
			}
				
			MessageIcon icon_;
			std::string title_;
			std::string text_;
			size_t delay_;
		};

};




