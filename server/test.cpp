
#include "dorm.hpp"

#include "database.hpp"
#include "pg_connection.hpp"
#include "server_config.hpp"
#include "dchat_server_app.hpp"
#include "dchat_db_orm.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include <thread>

#include "zmq.hpp"

#include <deque>

#include "dredis.hpp"

struct TestInner {
    std::vector<std::string> value1;
};

DORM_VISIT(TestInner, RedisType::String, value1, value1);

DORM_MSGPACK(TestInner, value1);

struct Test {
    int id1;
    uint32_t id2;
    std::string value1;
    std::vector<int> value2;
    std::vector<short int> value3;
    std::vector<std::string> value4;
    TestInner value50;
};

DORM(Test,                                // struct type
     RedisType::String,                   // noSQL database store type
     id1,                                 // primary key
     id1, id2, value1, value2, value3, value4, value50);   // data field

void test_orm(const char* path_file_) {

    auto temp(Test{50, 100, "temp", {34, 34}, {56, 78}, {"abc", "def"}, TestInner{{"test", "inner"}}});


    Account account{"temp", {}, {}};

    RedisSerializer ser;
    auto result = ser.serialize(account);

    std::cout << "cmd=" << result.cmd() << " key=" << result.key() << " value=" << result.value() << std::endl;


    auto config = drift::parse_config(path_file_);
    std::cout << config.self_config.addr << std::endl;

    drift::db::DataBase db;
    db.connect<drift::db::RedisConnection, 1>("127.0.0.1:6379");

    const char* postgresql = "dbname=traindata user=postgres password=123456 hostaddr=127.0.0.1 port=5432";
    // dbname | user | pwd | addr | port
    const char* nn = "pgdb, pgusr, 123, 127.0.0.1:5432";

//    db.connect<drift::db::PGConnection, 1>("127.0.0.1, 6379, user, passwd, database1");

    auto conn = db.get_redis();


    auto insert_result = drift::db::insert(std::move(temp)).execute(conn);
    std::cout << insert_result.get_status() << std::endl;

    auto select_result = drift::db::select<Test>().where(FIELD(Test, id1).concat("50")).execute(conn).get_result();

    std::cout << select_result.id1 << std::endl;
    std::cout << select_result.id2 << std::endl;
    std::cout << select_result.value1 << std::endl;
    for (auto& v : select_result.value2) {
        std::cout << v << std::endl;
    }
}

void test_router() {
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, zmq::socket_type::router);

    socket.bind("tcp://127.0.0.1:5566");

    const char* reply_str = "router reply.";

    zmq::message_t id;
    zmq::message_t msg;

    for (; ;) {
        id.rebuild();
        msg.rebuild();

        socket.recv(id);
        socket.recv(msg);

        std::cout << "router recv id=" << id.to_string() << std::endl;
        std::cout << "router recv msg=" << msg.to_string() << std::endl;

//        std::this_thread::sleep_for(std::chrono::seconds(1));

        zmq::message_t reply(reply_str, strlen(reply_str));

        std::cout << "router send id=" << id.to_string() << std::endl;
        std::cout << "router send msg=" << reply.to_string() << std::endl;

        socket.send(id, zmq::send_flags::sndmore);
        socket.send(reply);

//        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void test_dealer() {
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, zmq::socket_type::dealer);

    socket.connect("tcp://127.0.0.1:5566");

    const char* msg_str = "dealer message.";

    for (; ;) {
        zmq::message_t msg(msg_str, strlen(msg_str));
        std::cout << "dealer send=" << msg.to_string() << std::endl;
        socket.send(msg);

        zmq::message_t reply;

//        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "dealer recv before=" << reply.to_string() << std::endl;
        socket.recv(reply/*, zmq::recv_flags::dontwait*/);

        std::cout << "dealer recv after1=" << reply.to_string() << std::endl;

//        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void test_zmq_dealer_router() {

    auto dealer = std::thread(test_dealer);
    auto router = std::thread(test_router);

    dealer.detach();
    router.detach();

    while(true);
}

void test_dchat() {
    drift::ChatServer server;
//    drpc::run(&server, "ipc:///tmp/dchat_service");
//    drpc::run(&server, "tcp://127.0.0.1:5566");
    server.run_with_blockon("tcp://127.0.0.1:5566");

}
