#include <iostream>

class Button {
    public:
        virtual ~Button() {}
        virtual std::string Click() const = 0;
};

class WinButton : public Button {
    public:
        std::string Click() const override {
            return "Win button pressed.";
        }
};

class MacButton : public Button {
    public:
        std::string Click() const override {
            return "Mac button pressed.";
        }
};

class Checkbox {
    public:
        virtual ~Checkbox() {}
        virtual std::string Check() const = 0;
};

class WinCheckbox : public Checkbox {
    public:
        std::string Check() const override {
            return "Win checkbox checked.";
        }
};

class MacCheckbox : public Checkbox {
    public:
        std::string Check() const override {
            return "Mac checkbox checked.";
        }
};

class GUIFactory {
    public:
        virtual Button *CreateButton() const = 0;
        virtual Checkbox *CreateCheckbox() const = 0;
};

class WinFactory : public GUIFactory {
    public:
        Button *CreateButton() const override {
            return new WinButton();
        }

        Checkbox *CreateCheckbox() const override {
            return new WinCheckbox();
        }
};

class MacFactory : public GUIFactory {
    public:
        Button *CreateButton() const override {
            return new MacButton();
        }

        Checkbox *CreateCheckbox() const override {
            return new MacCheckbox();
        }
};

class Application {
    private:
        GUIFactory &mFactory;
    
    public:
        Application(GUIFactory &factory) : mFactory(factory) {}

        virtual ~Application() {}

        void RenderUI() {
            Button *button = mFactory.CreateButton();
            Checkbox *checkbox = mFactory.CreateCheckbox();

            button->Click();
            checkbox->Check();

            delete button;
            delete checkbox;
        }
};

int main() {
    std::cout << "Client: Testing abstract factory. \n" << std::endl;

    WinFactory winFactory;
    Application winApp(winFactory);
    winApp.RenderUI();

    MacFactory macFactory;
    Application macApp(macFactory);
    macApp.RenderUI();

    return 0;
}