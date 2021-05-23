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

#ifndef __drift_db_sqlclient_hpp__
#define __drift_db_sqlclient_hpp__

#include "database_if.hpp"

namespace drift {

class SQLClient : public DataBaseIF {
public:
    virtual bool connect() override {

        return true;
    }

    virtual bool disconnect() override {

        return true;
    }

    virtual bool basic_query() {

        return true;
    }
};

} // namespace drift

#endif // __drift_db_sqlclient_hpp__
