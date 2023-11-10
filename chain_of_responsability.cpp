#include <iostream>
#include <memory>

using namespace std;

class Handler {
    public:
        virtual shared_ptr<Handler> SetNext(shared_ptr<Handler> next) = 0;
        virtual void Handle(string request, int value) const = 0;
};

class BaseHandler : public Handler {
    protected:
        shared_ptr<Handler> mNext;
    
    public:
        BaseHandler() : mNext(nullptr) {}

        shared_ptr<Handler> SetNext(shared_ptr<Handler> next) override {
            mNext = next;
            return mNext;
        }

        void Handle(string request, int value) const override {
            value++;

            if (mNext != nullptr) {
                cout << "(" << value << ") -> ";
                mNext->Handle(request, value);
            } else {
                cout << "(" << value << ")" << endl;
            }
        }
};

class ConcreteHandlerA : public BaseHandler {
    public:
        void Handle(string request, int value) const {
            if (request == "CATCH_A") {
                cout << "(CATCH A:" << value << ")" << endl;
            } else {
                BaseHandler::Handle(request, value);
            }
        }
};

class ConcreteHandlerB : public BaseHandler {
    public:
        void Handle(string request, int value) const {
            if (request == "CATCH_B") {
                cout << "(CATCH B:" << value << ")" << endl;
            } else {
                BaseHandler::Handle(request, value);
            }
        }
};

class ConcreteHandlerC : public BaseHandler {
    public:
        void Handle(string request, int value) const {
            if (request == "CATCH_C") {
                cout << "(CATCH in C:" << value << ")" << endl;
            } else {
                BaseHandler::Handle(request, value);
            }
        }
};

int main() {
    auto concreteHandlerA = make_shared<ConcreteHandlerA>();
    auto concreteHandlerB = make_shared<ConcreteHandlerB>();
    auto concreteHandlerC = make_shared<ConcreteHandlerC>();

    concreteHandlerA->SetNext(concreteHandlerB)->SetNext(concreteHandlerC);
    
    concreteHandlerA->Handle("CATCH_B", 0);
    concreteHandlerA->Handle("CATCH_C", 0);
    concreteHandlerA->Handle("CATCH_A", 0);
    concreteHandlerA->Handle("FULL", 0);

    return 0;
}