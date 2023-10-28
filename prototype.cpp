#include <iostream>
#include <unordered_map>

enum ButtonType {
    MAC = 0,
    WIN
};

class ButtonPrototype {
    public:
        virtual ~ButtonPrototype() {}
        virtual ButtonPrototype *Clone() const = 0;
        virtual ButtonType GetType() const = 0;
};

class Button : public ButtonPrototype {
    private:
        ButtonType mType;

    public:
        Button(ButtonType type)
            : mType(type) {}
        
        ButtonPrototype *Clone() const override {
            return new Button(*this);
        }

        ButtonType GetType() const override {
            return this->mType;
        }
};

class PrototypeRegistry {
    private: 
        std::unordered_map<ButtonType, ButtonPrototype *, std::hash<int>> mPrototypes;
    
    public:
        PrototypeRegistry() {
            mPrototypes[ButtonType::MAC] = new Button(ButtonType::MAC);
            mPrototypes[ButtonType::WIN] = new Button(ButtonType::WIN);
        }

        ~PrototypeRegistry() {
            delete mPrototypes[ButtonType::MAC];
            delete mPrototypes[ButtonType::WIN];
        }

        ButtonPrototype *Create(ButtonType type) {
            return mPrototypes[type]->Clone();
        }
};

void ClientCode(PrototypeRegistry *registry) {
    std::cout << "Creating Windows button." << std::endl;
    ButtonPrototype *prototype = registry->Create(ButtonType::WIN);
    std::cout << "Button of type " << prototype->GetType() << " created.\n\n" << std::endl;
    delete prototype;

    std::cout << "Creating Mac button." << std::endl;
    prototype = registry->Create(ButtonType::MAC);
    std::cout << "Button of type " << prototype->GetType() << " created.\n" << std::endl;
    delete prototype;
}

int main() {
    PrototypeRegistry *registry = new PrototypeRegistry();
    ClientCode(registry);
    delete registry;
    return 0;
}
