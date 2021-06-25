/*
 *
 * Copyright 2021 drift server authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef __drift_chat_server_hpp__
#define __drift_chat_server_hpp__

#include "dchat_server.hpp"
#include "database.hpp"

namespace drift {

class ChatServer : public dchatServerIF {
public:
    ChatServer();

    // Basic send message.
    virtual bool on_request_send_msg (std::string account_id, std::string contact_id, Message messages);

    // Group send message.
    virtual bool on_request_send_group (std::string account_id, std::vector<std::string> contacts, std::vector<Message> messages);

    // Pull unread message from server.
    virtual std::vector<PullMessage> on_request_pull_message (std::string account_id);

    // Add new contact by contact id.
    virtual bool on_request_contact_add_new (std::string account_id, std::string contact_id);

    // Delete contact by contact id.
    virtual bool on_request_contact_delete (std::string account_id, std::string contact_id);

    // basic send message.
    virtual std::vector<Contact> on_request_contacts_load (std::string account_id);

    // Update contact settings.
    virtual bool on_request_contact_update (std::string account_id, Contact contact);

    // Load account settings.
    virtual Account on_request_account_load (std::string account_id);

    // Update account settings.
    virtual bool on_request_account_update (Account account);

    // Establish connection for voice communication.
    virtual bool on_request_voice_call (std::string account_id, std::string contact_id);

    // Establish connection for video communication.
    virtual bool on_request_video_call (std::string account_id, std::string contact_id);


private:
    drift::db::DataBase m_db;
    bool m_account_inserted;
};

} // namespace drift

#endif // __drift_chat_server_hpp__
