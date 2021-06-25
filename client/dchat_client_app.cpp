
#include "dchat_client_app.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

namespace drift {

// Basic send message.
void client_app::on_response_send_msg (bool respons_)  {
    std::cout << "[on_response_send_respons] respons_=" << respons_ << std::endl;
}

// Group send message.
void client_app::on_response_send_group (bool respons_)  {
    std::cout << "[on_response_send_group] respons_=" << respons_ << std::endl;
}

// Pull unread message from server.
void client_app::on_response_pull_message (std::vector<PullMessage> respons_) {
    std::cout << "[on_response_pull_message] respons_=" << std::endl;
//    std::string msgs;
    std::stringstream msgs;

    for (auto& pull_msg : respons_) {
        msgs << "[contact_id]:" << pull_msg.contact_id << std::endl;
        msgs << "[messages]:" << std::endl;
        for (auto& msg : pull_msg.message) {
            msgs << "> " << msg.content << (msg.is_read ? "(read)" : "(not read)") << std::endl;
        }
    }

    std::string aaa(msgs.str());
    _app->setMessages(aaa.c_str());
}

// Add new contact by contact id.
void client_app::on_response_contact_add_new (bool respons_) {
    std::cout << "[on_response_contact_add_new] respons_=" << std::endl;
}

// Delete contact by contact id.
void client_app::on_response_contact_delete (bool respons_) {
    std::cout << "[on_response_contact_delete] respons_=" << std::endl;
}

// basic send message.
void client_app::on_response_contacts_load (std::vector<Contact> respons_) {
    std::cout << "[on_response_contacts_load] respons_=" << std::endl;
}

// Update contact settings.
void client_app::on_response_contact_update (bool respons_) {
    std::cout << "[on_response_contact_update] respons_=" << std::endl;
}

// Load account settings.
void client_app::on_response_account_load (Account respons_) {
    std::cout << "[on_response_account_load] respons_=" << std::endl;
    std::cout << "[ChatClientApp] on_response_account_load called." << std::endl;
    std::cout << "[ChatClientApp] respons_.id=" << respons_.id << std::endl;
    std::cout << "[ChatClientApp] respons_.basic.id=" << respons_.basic.id << std::endl;
    std::cout << "[ChatClientApp] respons_.basic.name=" << respons_.basic.name << std::endl;
    std::cout << "[ChatClientApp] respons_.basic.gender=" << respons_.basic.gender << std::endl;
    std::cout << "[ChatClientApp] respons_.basic.region=" << respons_.basic.region << std::endl;
    std::cout << "[ChatClientApp] respons_.basic.whats_up=" << respons_.basic.whats_up << std::endl;
}

// Update account settings.
void client_app::on_response_account_update (bool respons_) {
    std::cout << "[on_response_account_update] respons_=" << respons_ << std::endl;
}

// Establish connection for voice communication.
void client_app::on_response_voice_call (bool respons_) {
    std::cout << "[on_response_voice_call] respons_=" << std::endl;
}

// Establish connection for video communication.
void client_app::on_response_video_call (bool respons_) {
    std::cout << "[on_response_video_call] respons_=" << std::endl;
}



ChatClientApp::ChatClientApp(const char* address_, QObject *parent) : QObject(parent), _client(this, address_) {

    _messages = "";
    _account_id = "drifter_a";
}

ChatClientApp::~ChatClientApp() {

}

void ChatClientApp::setProperty(QString name, QString section, QString key, QString value) {

}

QString ChatClientApp::getProperty(QString name, QString section, QString key) {

    return {};
}

bool ChatClientApp::send_msg (QString contact_id, int type, bool is_read, QString content) {

    std::cout << "[ChatClientApp] send called." << std::endl;
    std::cout << "[ChatClientApp] contact_id=" << contact_id.toStdString() << std::endl;
    std::cout << "[ChatClientApp] type=" << type << std::endl;
    std::cout << "[ChatClientApp] is_read=" << is_read << std::endl;
    std::cout << "[ChatClientApp] content=" << content.toStdString() << std::endl;

    drift::Message msg{static_cast<MessageType>(type), is_read, content.toStdString()};

    auto result = _client.send_msg(_account_id, contact_id.toStdString(), msg);

    std::cout << "[ChatClientApp] reply=" << (result.get()? "ok" : "ng") << std::endl;

    return true;
}

// Group send message.
bool ChatClientApp::send_group (std::string account_id, std::vector<std::string> contacts, std::vector<Message> messages) {

    return true;
}

// Pull unread message from server.
bool ChatClientApp::pull_message () {
    std::cout << "[ChatClientApp] pull_message called." << std::endl;
    auto result = _client.pull_message(_account_id);

    std::cout << "[ChatClientApp] pull_message called end." << std::endl;

    for (auto& msg : result.get()) {
        std::cout << "[ChatClientApp] reply=" << msg.message.size() << std::endl;
        std::cout << "[ChatClientApp] reply=" << msg.contact_id << std::endl;
        std::cout << "[ChatClientApp] reply=" << ( msg.message.empty() ? msg.message[0].content : "msg is empty") << std::endl;
    }

    return true;
}

// Add new contact by contact id.
bool ChatClientApp::contact_add_new (std::string account_id, std::string contact_id) {

    return true;
}

// Delete contact by contact id.
bool ChatClientApp::contact_delete (std::string account_id, std::string contact_id) {

    return true;
}

// basic send message.
std::vector<Contact> ChatClientApp::contacts_load (std::string account_id) {

    return {};
}

// Update contact settings.
bool ChatClientApp::contact_update (std::string account_id, Contact contact)  {

    return true;
}

// Load account settings.
bool ChatClientApp::account_load () {
    std::cout << "[ChatClientApp] account_load called."  << std::endl;
    auto result = _client.account_load(_account_id);

    std::cout << "[ChatClientApp] account_load called end." << std::endl;

    return true;
}

// Update account settings.
bool ChatClientApp::account_update ()  {
    std::cout << "[ChatClientApp] account_load called."  << std::endl;

    AccountBasicInfo basic{_account_id, "tony", "Male", "chinese dalian", "fuck fuck fuck gnu", "No", "No"};
    AccountSecurity security{_account_id, "15612341234", "password", {"drifter_a", "drifter_b"}, {"iphone", "android"}, "33722257", "33722257@qq.com"};
    Account account{_account_id, basic, security};

    auto result = _client.account_update(account);

    std::cout << "[ChatClientApp] account_load called end." << std::endl;

    return true;
}

// Establish connection for voice communication.
bool ChatClientApp::voice_call (std::string account_id, std::string contact_id)  {

    return true;
}

// Establish connection for video communication.
bool ChatClientApp::video_call (std::string account_id, std::string contact_id)  {

    return true;
}

} // namespace drift
