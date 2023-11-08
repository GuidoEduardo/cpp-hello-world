#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>
#include <cstring>

using namespace std;

const int UNIQUE_STATE_SIZE_INCREASE = 0;

struct SharedState {
    private:
        int ID;
        char kilobytes[1024 * 20];
    
    public:
        SharedState(int id)
            : ID(id) {
            for (int i = 0; i < 1024 * 20; i++) {
                kilobytes[i] = 'A';
            }
        }

        int GetID() const {
            return ID;
        }

        int GetSize() const {
            return sizeof(ID) + sizeof(kilobytes);
        }

        friend ostream& operator<<(ostream& os, const SharedState& sharedState) {
            return os << "[" << sharedState.ID << "]" << endl;
        }
};

struct UniqueState {
    private:
        int x, y;
        char kilobytes[UNIQUE_STATE_SIZE_INCREASE];

    public:
        UniqueState(int x, int y)
            : x(x), y(y) {
            for (int i = 0; i < UNIQUE_STATE_SIZE_INCREASE; i++) {
                kilobytes[i] = 'A';
            }
        }

        int GetSize() const {
            return sizeof(x) + sizeof(y) + sizeof(kilobytes);
        }

        friend ostream& operator<<(ostream& os, UniqueState& uniqueState) {
            return os << "[" << uniqueState.x << ", " << uniqueState.y << "]" << endl;  
        }
};

class Flyweight {
    private:
        shared_ptr<SharedState> mSharedState;
    
    public:
        Flyweight(const SharedState* sharedState)
            : mSharedState(new SharedState(*sharedState)) {}
        
        Flyweight(const Flyweight& other)
            : mSharedState(new SharedState(*other.mSharedState)) {}
        
        void Operation(const UniqueState& uniqueState) const {
            cout << "shared " << mSharedState
                << " with sizeof(" << mSharedState->GetSize()
                << ") || unique " << &uniqueState 
                << " with sizeof(" << uniqueState.GetSize() << ")" << endl;
        }
};

class FlyweightFactory {
    private:
        unordered_map<int, Flyweight> mFlyweights;
    
        int GetKey(const SharedState& sharedState) const {
            return sharedState.GetID();
        }
    
    public:
        FlyweightFactory(list<SharedState> sharedStates) {
            for (const SharedState& sharedState : sharedStates) {
                this->mFlyweights.insert(
                    make_pair<int, Flyweight>(
                        this->GetKey(sharedState), 
                        Flyweight(&sharedState)
                    )
                );
            }
        }

        Flyweight GetFlyweight(const SharedState& sharedState) {
            int key = this->GetKey(sharedState);

            if (this->mFlyweights.find(key) == this->mFlyweights.end()) {
                this->mFlyweights.insert(
                    make_pair<int, Flyweight>(
                        this->GetKey(sharedState), 
                        Flyweight(&sharedState)
                    )
                );
            } 

            return this->mFlyweights.at(key);
        }
};

int main() {
    SharedState sharedState1(1);

    FlyweightFactory flyweightFactory({sharedState1});

    const Flyweight &flyweight = flyweightFactory.GetFlyweight(sharedState1);
    
    list<UniqueState*> uniqueStates;

    for (int i = 0; i < 400000; i++) {
        uniqueStates.push_back(new UniqueState(0, 0));
    }
    
    for (const UniqueState* uniqueState : uniqueStates) {
        flyweight.Operation(*uniqueState);
    }
        
    return 0;
}