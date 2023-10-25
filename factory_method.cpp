#include <iostream>

class Database {
    public:
        virtual ~Database() {}
        virtual void Connect() const = 0;
};

class SQLDatabase : public Database { 
    public:
        void Connect() const override {
            std::cout << "SQL Example connection." << std::endl;
        }
};

class NoSQLDatabase : public Database {
    public:
        void Connect() const override {
            std::cout << "NoSQL Example connection." << std::endl;
        }
};

class Connector {
    public:
        virtual ~Connector() {}
        virtual Database *Create() const = 0;
        void Configure() const {
            Database *database = this->Create();
            database->Connect();
            delete database;
        }
};

class SQLConnector : public Connector {
    public:
        Database *Create() const override {
            return new SQLDatabase();
        }
};

class NoSQLConnector : public Connector {
    public:
        Database *Create() const override {
            return new NoSQLDatabase();
        }
};

void SetupDatabase(Connector &connector) {
    connector.Configure();
}

int main() {
    std::cout << "Example Database connections.\n" << std::endl;

    std::cout << "SQL Database" << std::endl;
    Connector *sqlConnector = new SQLConnector();
    SetupDatabase(*sqlConnector);

    std::cout << "\nNoSQL Database" << std::endl;
    Connector *noSqlConnector = new NoSQLConnector();
    SetupDatabase(*noSqlConnector);

    delete sqlConnector;
    delete noSqlConnector;

    return 0;
}