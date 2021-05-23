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

#ifndef __drift_db_cache_client_hpp__
#define __drift_db_cache_client_hpp__

#include "database_if.hpp"

#include <vector>
#include <map>

namespace drift {

template<typename T>
class Table {
public:
    T get(std::string key_) {

    }

    bool set(std::string key_, T&& value_) {

    }

private:
    std::map<std::string, T> _table;
};

class CacheClient : public DataBaseIF {
public:
    virtual bool connect() override {

        return true;
    }

    virtual bool disconnect() override {

        return true;
    }

    template<typename T>
    T get(std::string key) {

    }

    template<typename T>
    bool set(std::string key, T&& value) {

    }

    template<typename T>
    bool hash_get(std::string key, T&& value) {

    }

    template<typename T>
    bool hash_set(std::string key, T&& value) {

    }

private:
    std::map<std::string, void*> _master_tables;
};

} // namespace drift


#endif // __drift_db_cache_client_hpp__
