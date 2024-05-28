#include <iostream>

using namespace std;

template<class T>

class MyUnique
    {
    T * p = nullptr;
    MyUnique(MyUnique&) = delete;
    MyUnique& operator=(MyUnique&) = delete;

    public:
    MyUnique (T* p) : p(p) {}

    
    ~MyUnique() 
        {
        delete p;
        }
        
    MyUnique(MyUnique&& other) : p(other.p)
        {
        other.p = nullptr;
        }
        
    MyUnique& operator=(MyUnique&& other)
        {
        if (this != &other) 
            {
            delete p;
            p = other.p;
            other.p = nullptr;
            }
        return *this;
        }
        
    T * get() const
        {
        return p;
        }
        
    T & operator*()
        {
        return *p;
        }
        
    T * operator->()
        {
        return p;
        }
    };

template<class T, class... Args>

MyUnique <T> Make_MyUnique(Args&&... args)
    {
    return MyUnique<T>(new T(forward<Args>(args)...));
    }

class MyPoint 
    {
    private:
    int x, y;
        
    public:
    MyPoint(int x, int y) : x(x), y(y) {}
        
    void print() const 
        {
        cout << "MyPoint(" << x << ", " << y << ")\n";
        }
    };

int main() 
    {
    MyUnique <MyPoint> point = Make_MyUnique <MyPoint> (3, 4);
    
    point->print();
    
    MyUnique <MyPoint> movedPoint = move(point);
    
    movedPoint->print();
    
    return 0;
    }
