
#include "dchat_server_app.hpp"
#include "dchat_db_orm.hpp"

#include "statement.hpp"
#include <iostream>

namespace drift {

ChatServer::ChatServer() : m_account_inserted(false) {
    m_db.connect<drift::db::RedisConnection, 1>("127.0.0.1:6379");
}

// Basic send message.
bool ChatServer::on_request_send_msg (std::string account_id, std::string contact_id, Message messages) {

    std::cout << "[ChatServer] send received===============================================" << std::endl;
    std::cout << "[ChatServer] account_id=" << account_id << std::endl;
    std::cout << "[ChatServer] contact_id=" << contact_id << std::endl;
    std::cout << "[ChatServer] messages.type=" << static_cast<int>(messages.type) << std::endl;
    std::cout << "[ChatServer] messages.is_read=" << static_cast<int>(messages.is_read) << std::endl;
    std::cout << "[ChatServer] messages.content=" << messages.content << std::endl;

//    auto insert_result = drift::db::insert(std::move(temp)).execute(conn);

//    std::cout << insert_result.get_status() << std::endl;

    return true;
}

// Group send message.
bool ChatServer::on_request_send_group (std::string account_id, std::vector<std::string> contacts, std::vector<Message> messages) {


    return true;
}

// Pull unread message from server.
std::vector<PullMessage> ChatServer::on_request_pull_message (std::string account_id) {
    std::cout << "[ChatServer] pull_message received." << std::endl;
    std::cout << "[ChatServer] account_id=" << account_id << std::endl;

    std::vector<PullMessage> messages;

    PullMessage msg{"drifter_a", {Message{MessageType::text, false, "hello " + account_id},
                                  Message{MessageType::text, false, "this test message from dchat server application."},
                                  Message{MessageType::text, false, "interface is pull_message."},
                                  Message{MessageType::text, false, "welcome to drift family."}}};

    messages.emplace_back(std::move(msg));

    return messages;
}

// Add new contact by contact id.
bool ChatServer::on_request_contact_add_new (std::string account_id, std::string contact_id) {

    return true;
}

// Delete contact by contact id.
bool ChatServer::on_request_contact_delete (std::string account_id, std::string contact_id) {

    return true;
}

// basic send message.
std::vector<Contact> ChatServer::on_request_contacts_load (std::string account_id) {

    return {};
}

// Update contact settings.
bool ChatServer::on_request_contact_update (std::string account_id, Contact contact)  {

    return true;
}

// Load account settings.
Account ChatServer::on_request_account_load (std::string account_id) {
    std::cout << "[ChatServer] account_load received." << std::endl;

    auto account = drift::db::select<Account>().where(FIELD(Account, id).concat(account_id)).execute(m_db.get_redis()).get_result();

    return account;
}

// Update account settings.
bool ChatServer::on_request_account_update (Account account)  {
    std::cout << "[ChatServer] account_update received...................." << std::endl;

    auto conn = m_db.get_redis();
//    auto insert_account_result = drift::db::insert(std::move(account.basic)).execute(conn).get_status();
//    auto insert_security_result = drift::db::insert(std::move(account.security)).execute(conn).get_status();

    auto result = drift::db::insert(std::move(account)).execute(conn).get_status();

//    auto insert_security_result = true;

    std::cout << "[ChatServer] account_update insert result=" << result << std::endl;
    return result;
}

// Establish connection for voice communication.
bool ChatServer::on_request_voice_call (std::string account_id, std::string contact_id)  {

    return true;
}

// Establish connection for video communication.
bool ChatServer::on_request_video_call (std::string account_id, std::string contact_id)  {

    return true;
}

}
