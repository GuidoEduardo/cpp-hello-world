#include <iostream>

using namespace std;

class Component {
    public:
        virtual ~Component() {}
        virtual string Operation() const = 0;
};

class ConcreteComponent : public Component {
    public:
        string Operation() const override {
            return "Concrete Operation";
        }
};

class Decorator {
    protected:
        Component& mWrappee;

    public:
        Decorator(Component& component)
            : mWrappee(component) {}

        string Operation() const {
            return "Decorator (" + mWrappee.Operation() + ")";
        }
};

int main() {
    cout << "Starting Decorator pattern." << endl << endl;
    
    ConcreteComponent concreteComponent;
    cout << "Without decorated function: " 
         << concreteComponent.Operation() 
         << endl << endl;

    Decorator decorator(concreteComponent);
    cout << "With decorated function: "
         << decorator.Operation()
         << endl << endl;

    return 0;
}