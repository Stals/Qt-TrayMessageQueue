#ifndef MESSAGE_H
#define MESSAGE_H

struct Message{
    Message( QSystemTrayIcon::MessageIcon icon, std::string title, std::string text, size_t delay) :
        icon_(icon),
        title_(title),
        text_(text),
        delay_(delay){
    }

    QSystemTrayIcon::MessageIcon icon_;
    std::string title_;
    std::string text_;
    size_t delay_;
};
#endif // MESSAGE_H
