#include <iostream>
#include <list>

using namespace std;

class Component {
    public:
        virtual ~Component() {}
        virtual void Add(Component *component) {}
        virtual void Remove(Component *component) {}
        virtual string Operation() const = 0;
};

class Composite : public Component {
    private:
        list<Component *> mChildren;

    public:
        ~Composite() {
            for (const Component* component : mChildren) {
                delete component;
            }

            mChildren.clear();
        }

        void Add(Component* component) override {
            mChildren.push_back(component);
        }

        void Remove(Component* component) override {
            mChildren.remove(component);
        }

        string Operation() const override {
            string result;

            for (const Component* component : mChildren) {
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
    
    Component* tree = new Composite;
    Component* firstBranch = new Composite;
    Component* secondBranch = new Composite; 

    Component* treeLeaf = new Leaf;
    Component* firstLeaf = new Leaf;
    Component* secondLeaf = new Leaf;
    Component* thirdLeaf = new Leaf;

    tree->Add(firstBranch);
    tree->Add(secondBranch);
    tree->Add(treeLeaf);

    firstBranch->Add(firstLeaf);
    firstBranch->Add(secondLeaf);

    secondBranch->Add(thirdLeaf);

    cout << "Tree Component: " << tree->Operation() << endl << endl;

    delete tree;
 
    return 0;
}