#include<iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0; // pure virtual function for preparing the burger
    virtual ~Burger() {} // virtual destructor for proper cleanup of derived classes
};

class BasicBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a basic burger with lettuce, tomato, and cheese." << endl;
    }
};


class DeluxeBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a deluxe burger with bacon, avocado, and special sauce." << endl;
    }
};

class PremiumBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a premium burger with truffle aioli, arugula, and aged cheddar." << endl;
    }
};


class BurgerFactory {
    public: 
    Burger* createBurger(string& type){
        if(type == "basic"){
            return new BasicBurger();
        }
        else if(type == "deluxe"){
            return new DeluxeBurger();
        }
        else if(type == "premium"){
            return new PremiumBurger();
        }
        else{
            cout << "Invalid burger type." << endl;
            return nullptr;
        }
    }
};


int main() {
    string type = "deluxe"; // Example burger type
    BurgerFactory* factory = new BurgerFactory();

    Burger* burger = factory->createBurger(type);

    burger->prepare();
    
    return 0;
}