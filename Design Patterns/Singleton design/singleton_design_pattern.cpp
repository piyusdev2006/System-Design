#include<iostream>
#include <mutex>

using namespace std;

class Singleton {

    private:

    static Singleton* instance;
    static mutex mtx;

    Singleton() {
        cout << "Constructor called" << endl;
    }

    public:
    static Singleton* getInstance() {

        // double locking : kyoki 2 thread ek saath instance create karne ki kosis karenge aur first time maan lete hai instance null hai toh first if block ko dono paar kar jayenge but lock ke andar ek hi thread jayega aur dusra thread wait karega jab tak first thread kaam complete nahi kar leta and instance create kar leta hai. then second thread toh instance create karne ki kosis karega but instance ab null nahi hai toh second thread if block ke andar nahi jayega and instance return ho jayega.
        if(instance == nullptr) {
           lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;
int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl; // dono object sam nhi hai
}