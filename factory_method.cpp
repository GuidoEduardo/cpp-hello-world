#include <iostream>

class Database {
    public:
        virtual ~Database() {}
        virtual std::string Connect() const = 0;
};

class SQLDatabase : public Database { 
    public:
        std::string Connect() const override {
            return "SQL connection example.";
        }
};

class NoSQLDatabase : public Database {
    public:
        std::string Connect() const override {
            return "NoSQL connection example.";
        }
};

class Connector {
    private:
        Database &mDatabase;

    public:
        Connector(Database &database) : mDatabase(database) {} 
        virtual ~Connector() {}

        void Start() const {
            std::cout << mDatabase.Connect() << std::endl;
        }
};

int main() {
    std::cout << "Client: Testing factory.\n" << std::endl;

    std::cout << "SQL Database" << std::endl;
    SQLDatabase sqlDatabase;
    Connector sqlConnector(sqlDatabase);
    sqlConnector.Start();

    std::cout << "\nNoSQL Database" << std::endl;
    NoSQLDatabase noSqlDatabase;
    Connector noSqlConnector(noSqlDatabase);
    noSqlConnector.Start();

    return 0;
}