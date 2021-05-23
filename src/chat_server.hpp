/*
 *
 * Copyright 2021 dchat authors.
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

#include <string>
#include <vector>
#include <map>

namespace drift {

struct PullMessage {

};

struct Contact {

};

struct Account {

};

struct Message {

};

class ClientManager {
public:
    ClientManager();
    ~ClientManager();

    void add_connection(std::string logic_id_, std::string connection_ident) {
        if (_clients_connection_list.find(logic_id_) == _clients_connection_list.end()) {
            _clients_connection_list.insert(std::make_pair(logic_id_, connection_ident));
        }
    }

    void rm_connection(std::string logic_id_) {
        auto iter = _clients_connection_list.find(logic_id_);
        if (iter != _clients_connection_list.end()) {
            _clients_connection_list.erase(iter);
        }
    }

    std::string get_connection(std::string logic_id_) {
        auto iter = _clients_connection_list.find(logic_id_);
        if (iter == _clients_connection_list.end()) {
            return {};
        }

        return iter->second;
    }

private:
    typedef std::map<std::string, std::string> client_connections_t;
    client_connections_t _clients_connection_list;
};

class ChatServer {
public:
    ChatServer();
    ~ChatServer();

    virtual bool send(std::string account_id_, std::string contact_id_, Message messages_);
    virtual bool send_group(std::string account_id_, std::vector<std::string> contacts_, Message messages_);
    virtual std::vector<PullMessage> pull_message(std::string account_id_);
    virtual bool contact_add_new(std::string account_id_, std::string contact_id_);
    virtual bool contact_delete(std::string account_id_, std::string contact_id_);
    virtual Contact contact_load(std::string account_id_, std::string contact_id_);
    virtual bool contact_update(std::string account_id_, Contact contact_);
    virtual Account account_load(std::string account_id_);
    virtual bool account_update(std::string account_id_, Account account_);
    virtual bool voice_call();
    virtual bool video_call();


    void notify(std::string account_id_, std::string contact_id_, std::vector<Message> messages_);

private:

    std::map<std::string, std::string> _clients;
};


} // namespace drift


#endif // __drift_chat_server_hpp__
