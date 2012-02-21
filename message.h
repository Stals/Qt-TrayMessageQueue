#ifndef MESSAGE_H
#define MESSAGE_H

struct Message{
    Message(std::string title, std::string text, QSystemTrayIcon::MessageIcon icon, size_t delay) :
        title_(title),
        text_(text),
        icon_(icon),
        delay_(delay){
    }

    std::string title_;
    std::string text_;
    QSystemTrayIcon::MessageIcon icon_;
    size_t delay_;
};
#endif // MESSAGE_H
