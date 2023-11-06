#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class TreeType {
    private:
        string mColor;
        char mModel[20 * 1024];
    
    public:
        ostream& draw(ostream &os, TreeType treeType) {
            return os << "[" << treeType.mColor << "]" << endl;
        }
};

class Tree {
    private:
        int mX;
        int mY;

    public:
        Tree(int x, int y)
            : mX(x), mY(y) {}

        ostream& draw(ostream &os, Tree &tree) {
            return os << "[" << tree.mX << ", " << tree.mY << "]" << endl;  
        }
}

class Forest {
    private:
        list<Tree>* mTrees;
    
    public:
        // TODO: in progress..    
}