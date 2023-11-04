#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Component {
    public:
        virtual ~Component() {}
        virtual void Add(shared_ptr<Component> component) {}
        virtual void Remove(shared_ptr<Component> component) {}
        virtual string Operation() const = 0;
};

class Composite : public Component {
    private:
        list<shared_ptr<Component>> mChildren;

    public:
        void Add(shared_ptr<Component> component) override {
            mChildren.push_back(component);
        }

        void Remove(shared_ptr<Component> component) override {
            mChildren.remove(component);
        }

        string Operation() const override {
            string result;

            for (const shared_ptr<Component> component : mChildren) {
                result += component->Operation();

                if (component != mChildren.back()) {
                    result += " | ";
                }
            }
                
            return "Branch[ " + result + " ]";
        }
};

class Leaf : public Component {
    public:
        string Operation() const override {
            return "Leaf";
        }
};

int main() {
    cout << "Starting Composite pattern." << endl << endl;
    
    Leaf leaf;
    cout << "Simple Component: " << leaf.Operation() << endl << endl;
    
    auto tree = make_shared<Composite>();
    auto firstBranch = make_shared<Composite>();
    auto secondBranch = make_shared<Composite>();

    auto treeLeaf = make_shared<Leaf>();
    auto firstLeaf = make_shared<Leaf>();
    auto secondLeaf = make_shared<Leaf>();
    auto thirdLeaf = make_shared<Leaf>();

    tree->Add(firstBranch);
    tree->Add(secondBranch);
    tree->Add(treeLeaf);

    firstBranch->Add(firstLeaf);
    firstBranch->Add(secondLeaf);

    secondBranch->Add(thirdLeaf);

    cout << "Tree Component: " << tree->Operation() << endl << endl;
    return 0;
}