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

#ifndef __drift_db_database_hpp__
#define __drift_db_database_hpp__

#include "database_if.hpp"
#include "cache.hpp"
#include "redis.hpp"
#include "sql.hpp"

#include <vector>

namespace drift {
class CacheClient;
class SQLClient;

class DataBase : public DataBaseIF {
public:
    DataBase() {}
    ~DataBase() {}

    bool connect() {
        auto result = true;
        result &= _cache->connect();
        result &= _sql->connect();

        return result;
    }

    bool disconnect() {
        _cache->disconnect();
        _sql->disconnect();

        return true;
    }

    bool init_cache(std::vector<std::string> keys) {


        return true;
    }

private:
    CacheClient* _cache;
    SQLClient* _sql;
};

} // namespace drift


#endif // __drift_db_database_hpp__
