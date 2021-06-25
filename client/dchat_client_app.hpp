/*
 *
 * Copyright 2021 drift chat authors.
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


#ifndef __drift_chat_client_hpp__
#define __drift_chat_client_hpp__

#include "dchat_client.hpp"
#include <QObject>

namespace drift {
class ChatClientApp;

class client_app : public dchatClient {
public:
    client_app(ChatClientApp* app, const char* address_) : dchatClient(address_), _app(app) {}
    // Basic send message.
    virtual void on_response_send_msg (bool respons_);

    // Group send message.
    virtual void on_response_send_group (bool respons_);

    // Pull unread message from server.
    virtual void on_response_pull_message (std::vector<PullMessage> respons_);

    // Add new contact by contact id.
    virtual void on_response_contact_add_new (bool respons_);

    // Delete contact by contact id.
    virtual void on_response_contact_delete (bool respons_);

    // basic send message.
    virtual void on_response_contacts_load (std::vector<Contact> respons_);

    // Update contact settings.
    virtual void on_response_contact_update (bool respons_);

    // Load account settings.
    virtual void on_response_account_load (Account respons_);

    // Update account settings.
    virtual void on_response_account_update (bool respons_);

    // Establish connection for voice communication.
    virtual void on_response_voice_call (bool respons_);

    // Establish connection for video communication.
    virtual void on_response_video_call (bool respons_);

private:
    ChatClientApp* _app;

    std::deque<std::pair<int, bool>> m_queue_send_msg;
};

class ChatClientApp :  public QObject {
    Q_OBJECT
public:
    explicit ChatClientApp(const char* address_, QObject *parent = nullptr);
    ~ChatClientApp();

    Q_INVOKABLE void setProperty(QString name, QString section, QString key, QString value);
    Q_INVOKABLE QString getProperty(QString name, QString section, QString key);

    Q_INVOKABLE bool send_msg (QString contact_id, int type, bool is_read, QString content);

    // Group send message.
    Q_INVOKABLE bool send_group (std::string account_id, std::vector<std::string> contacts, std::vector<Message> messages);

    // Pull unread message from server.
    Q_INVOKABLE bool pull_message ();

    // Add new contact by contact id.
    virtual bool contact_add_new (std::string account_id, std::string contact_id);

    // Delete contact by contact id.
    virtual bool contact_delete (std::string account_id, std::string contact_id);

    // basic send message.
    virtual std::vector<Contact> contacts_load (std::string account_id);

    // Update contact settings.
    virtual bool contact_update (std::string account_id, Contact contact);

    // Load account settings.
    Q_INVOKABLE bool account_load ();

    // Update account settings.
    Q_INVOKABLE bool account_update ();

    // Establish connection for voice communication.
    virtual bool voice_call (std::string account_id, std::string contact_id);

    // Establish connection for video communication.
    virtual bool video_call (std::string account_id, std::string contact_id);


    QString messages() const {
        return _messages;
    }
    void setMessages(QString messages_) {
        _messages = messages_;
        emit messagesChanged();
    }


signals:
    QString messagesChanged();

private:
    client_app _client;
    std::string _account_id;

    Q_PROPERTY(QString _messages READ messages WRITE setMessages NOTIFY messagesChanged)
    QString _messages;
};

} // namespace drift

#endif // __drift_chat_client_hpp__
