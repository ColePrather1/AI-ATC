#include <sqlite_orm/sqlite_orm.h>
#include <chrono>

using namespace sqlite_orm;

struct Record {
    int id;
    std::string data;
};

int main() {
    auto storage = make_storage("database.sqlite",
                                make_table("records",
                                           make_column("id", &Record::id, primary_key()),
                                           make_column("data", &Record::data)));
    storage.sync_schema();

    // Begin transaction
    storage.begin_transaction();

    auto start = std::chrono::high_resolution_clock::now();

    // Perform high-frequency inserts
    for (int i = 0; i < 10000; ++i) {
        storage.insert(Record{i, "data" + std::to_string(i)});
    }

    // Commit transaction
    storage.commit();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to insert 10000 records: " << diff.count() << " s" << std::endl;

    return 0;
}
