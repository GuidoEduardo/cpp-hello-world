#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename U>
class Iterator {
    protected:
        typedef typename vector<T>::iterator DataType;

        U* mValues;
        DataType mCurrent;

    public:
        Iterator(U* values) : mValues(values) {
            mCurrent = mValues->mItems.begin();
        }

        void First() {
            mCurrent = mValues->mItems.begin();
        }

        void Next() {
            mCurrent++;
        }

        bool IsDone() {
            return (mCurrent == mValues->mItems.end());
        }

        DataType GetCurrent() {
            return mCurrent;
        }
};

template <class T>
class IterableCollection {
    friend class Iterator<T, IterableCollection>;

    private:
        vector<T> mItems;
    
    public:
        Iterator<T, IterableCollection>* CreateIterator() {
            return new Iterator<T, IterableCollection>(this);
        }

        void Add(T item) {
            mItems.push_back(item);
        }
};

class CustomClass {
    private:
        string mData;
    
    public:
        CustomClass(string data)
            : mData(data) {}

        string GetData() {
            return mData;
        }
};

int main() {
    cout << "Executing Iterator pattern." << endl;

    CustomClass a("Star"), b("Ocean"), c("Stone");

    IterableCollection<CustomClass> items;
    items.Add(a);
    items.Add(b);
    items.Add(c);

    auto iterator = items.CreateIterator();
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        cout << iterator->GetCurrent()->GetData() << endl;
    }

    delete iterator;
    return 1;
}