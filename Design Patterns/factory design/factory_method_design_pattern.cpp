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

class BasicWheatBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a basic wheat burger with lettuce, tomato, and cheese." << endl;
    }
};

class DeluxeWheatBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a deluxe wheat burger with bacon, avocado, and special sauce." << endl;
    }
};

class PremiumWheatBurger : public Burger{
    public:

    void prepare() override {
        cout << "Preparing a premium wheat burger with truffle aioli, arugula, and aged cheddar." << endl;
    }
};

/** Factory class f or creating burger instances 
 
*/
class BurgerFactory {
    public: 
    virtual Burger* createBurger(string& type) = 0; // pure virtual function for creating burger instances
};

class RegularBurgerFactory : public BurgerFactory {
    public:
    Burger* createBurger(string& type) override{
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

class WheatBurgerFactory : public BurgerFactory {
    public:
    Burger* createBurger(string& type) override{
        if(type == "basic"){
            return new BasicWheatBurger();
        }
        else if(type == "deluxe"){
            return new DeluxeWheatBurger();
        }
        else if(type == "premium"){
            return new PremiumWheatBurger();
        }
        else{
            cout << "Invalid burger type." << endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "deluxe"; // Example burger type
    BurgerFactory* factory = new RegularBurgerFactory(); // Create a regular burger factory
    Burger* burger = factory->createBurger(type);
    burger->prepare();

    BurgerFactory* wheatFactory = new WheatBurgerFactory(); // Create a wheat burger factory
    Burger* wheatBurger = wheatFactory->createBurger(type);
    wheatBurger->prepare();
    return 0;
}