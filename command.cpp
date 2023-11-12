#include <iostream>
#include <memory>

using namespace std;

class Command {
    public:
        virtual void Execute() const = 0;
};

class Invoker {
    private:
        shared_ptr<Command> mCommand;

    public:
        void SetCommand(shared_ptr<Command> command) {
            mCommand = command;
        }

        void ExecuteCommand() const {
            mCommand->Execute();
        }
};

class Receiver {
    public:
        void Operation(string param) const {
            cout << "Some operation with param: " << param << endl;
        }
};

class ConcreteCommand : public Command {
    private:
        shared_ptr<Receiver> mReceiver;
        string mParam;

    public:
        ConcreteCommand(shared_ptr<Receiver> receiver, string param)
            : mReceiver(receiver), mParam(param) {}

        void Execute() const override {
            mReceiver->Operation(mParam);
        }
};

int main() {
    cout << "Executing Command Pattern" << endl;

    auto invoker = make_shared<Invoker>();

    auto receiver = make_shared<Receiver>();

    invoker->SetCommand(make_shared<ConcreteCommand>(receiver, "PARAM"));
    invoker->ExecuteCommand();

    return 1;
}