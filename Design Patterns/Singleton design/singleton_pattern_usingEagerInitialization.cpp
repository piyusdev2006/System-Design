#include <iostream>

using namespace std;

class Singleton {
    private:
        Singleton() {
            cout << "Constructor called" << endl;
        }

    public:
        static Singleton& getInstance() {
            static Singleton instance;
            return instance;
        }
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();

    cout << (&s1 == &s2) << endl; // Should print 1 (true)
    return 0;
}