#include <iostream>
#include <list>

using namespace std;

class GraphicComponent {
    public:
        virtual void Move(int x, int y) = 0;
        virtual void Draw() = 0;
};

class CompoundGraphicComposite : public GraphicComponent {
    private:
        list<GraphicComponent *> mChildrens;

    public:
        void Add(GraphicComponent *component) {
            mChildrens.push_back(component);
        }

        void Remove(GraphicComponent *component) {
            mChildrens.remove(component);
        }

        void Move(int x, int y) override {
            // for (const GraphicComponent *component : mChildrens) {
            //     if (component == mChildrens.back()) {
                    
            //     }
            // }
        }

        void Draw() override {}
};

class DotLeaf : public GraphicComponent {
    protected:
        int mX;
        int mY;

    public:
        DotLeaf(int x, int y)
            : mX(x), mY(y) {}

        void Move(int x, int y) override {
            mX = x;
            mY = y;
        }

        void Draw() override {
            cout << "." << endl;
        };
};

class ImageEditor {

};