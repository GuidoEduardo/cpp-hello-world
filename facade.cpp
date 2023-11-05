#include <iostream>
#include <memory>

using namespace std;

class SubSystemA {
    public:
        string Operation() const {
            return "A";
        }
};

class SubSystemB {
    public:
        string Operation() const {
            return "B";
        }
};

class Facade {
    private:
        shared_ptr<SubSystemA> mSubSystemA;
        shared_ptr<SubSystemB> mSubSystemB;
    
    public:
        Facade(
            shared_ptr<SubSystemA> subSystemA,
            shared_ptr<SubSystemB> subSystemB)
            : mSubSystemA(subSystemA), mSubSystemB(subSystemB) {}

        void Operation() const {
            cout << "executing Operation Subsystem " << mSubSystemA->Operation() << endl;
            cout << "executing Operation Subsystem " << mSubSystemB->Operation() << endl;
        }
};

int main() {
    cout << "Executing Facade Pattern. " << endl << endl;

    auto subSystemA = make_shared<SubSystemA>();
    auto subSystemB = make_shared<SubSystemB>();

    Facade facade(subSystemA, subSystemB);
    facade.Operation();

    return 0;
}