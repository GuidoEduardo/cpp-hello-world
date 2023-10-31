#include <iostream>
#include <algorithm>

class Target {
    public:
        virtual std::string Request() const {
            return "Default target.";
        }
};

class Adaptee {
    public:
        std::string AdapteeRequest() const {
            return ".tegrat eetpadA";
        }
};

class Adapter : public Target {
    private:
        Adaptee* mAdaptee;
    
    public:
        Adapter(Adaptee *adaptee)
            : mAdaptee(adaptee) {}
        
        std::string Request() const override {
            std::string toReverse = this->mAdaptee->AdapteeRequest();
            std::reverse(toReverse.begin(), toReverse.end());
            return toReverse;
        }
};

int main() {
    std::cout << "Starting Adapter pattern." << std::endl;
    
    Target target;
    std::cout << target.Request() << std::endl << std::endl;

    std:: cout << "Adaptee without Adapter." << std::endl;
    Adaptee adaptee;
    std::cout << adaptee.AdapteeRequest() << std::endl << std::endl;
    
    std::cout << "Adaptee with Adapter." << std::endl;
    Adapter adapter(&adaptee);
    std::cout << adapter.Request() << std::endl;

    return 0;
}