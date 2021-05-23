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


#include "chat_server.hpp"

namespace drift {

ChatServer::ChatServer() {

}

ChatServer::~ChatServer() {

}

bool ChatServer::send(std::string account_id_, std::string contact_id_, Message messages_) {


    return true;
}

bool ChatServer::send_group(std::string account_id_, std::vector<std::string> contacts_, Message messages_) {

}

std::vector<PullMessage> ChatServer::pull_message(std::string account_id_) {
    std::vector<PullMessage> msgs;


    return msgs;
}

bool ChatServer::contact_add_new(std::string account_id_, std::string contact_id_) {

    return true;
}

bool ChatServer::contact_delete(std::string account_id_, std::string contact_id_) {
    return true;
}

Contact ChatServer::contact_load(std::string account_id_, std::string contact_id_) {

    return {};
}

bool ChatServer::contact_update(std::string account_id_, Contact contact_) {
    return true;
}

Account ChatServer::account_load(std::string account_id_) {

    return {};
}

bool ChatServer::account_update(std::string account_id_, Account account_) {
    return true;
}

bool ChatServer::voice_call() {
    return true;
}

bool ChatServer::video_call() {
    return true;
}

void ChatServer::notify(std::string account_id_, std::string contact_id_, std::vector<Message> messages_) {

}

} // namespace drift
