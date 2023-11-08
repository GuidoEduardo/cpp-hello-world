#include <iostream>
#include <memory>

using namespace std;

class Service {
    public:
        virtual void Operation() const = 0;
};

class RealService : public Service {
    public:
        void Operation() const override {
            cout << "Request RealService executed." << endl;           
        }
};

class Proxy : public Service {
    private:
        Service* mService;

        void BeforeOperation() const {
            cout << "Before request Proxy executed." << endl;
        }

        void AfterOperation() const {
            cout << "After request Proxy executed." << endl;
        }

    public:
        Proxy(Service* service)
            : mService(service) {}

        ~Proxy() {
            delete mService;
        }

        void Operation() const override {
            BeforeOperation();
            mService->Operation();
            AfterOperation();
        }
};

int main() {
    cout << "Executing Proxy pattern." << endl;

    RealService realService;
    realService.Operation();

    cout << endl << "Executing with Proxy" <<  endl;
    Proxy proxy(&realService);
    proxy.Operation();

    return 0;
}