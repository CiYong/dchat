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


#ifndef __drift_chat_db_orm_hpp__
#define __drift_chat_db_orm_hpp__

#include "dchat_data.hpp"
#include "dorm.hpp"

using namespace drift;

DORM_VISIT(AccountBasicInfo,
           RedisType::String,
           id,
           id, name, gender, region, whats_up, qr_code, photo)

DORM_VISIT(AccountSecurity,
           RedisType::String,
           id,
           id, phone, password, emergency_contacts, manage_devices, qq_id, email)

DORM_VISIT(Account,
           RedisType::String,
           id,
           id, basic, security)

#endif // __drift_chat_db_orm_hpp__
