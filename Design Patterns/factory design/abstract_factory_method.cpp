#include<iostream>
using namespace std;

// product 1 : Burger
class Burger{
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

// product 2 : GarlicBurger
class GarlicBurger {
    public: 
    virtual void prepare() = 0; // pure virtual function for preparing the burger
    virtual ~GarlicBurger() {} // virtual destructor for proper cleanup of derived classes
};

class BasicGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a basic garlic burger with lettuce, tomato, and cheese." << endl;
    }
};

class DeluxeGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a deluxe garlic burger with bacon, avocado, and special sauce." << endl;
    }
};

class PremiumGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a premium garlic burger with truffle aioli, arugula, and aged cheddar." << endl;
    }
};


class BasicWheatGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a basic wheat garlic burger with lettuce, tomato, and cheese." << endl;
    }
};

class DeluxeWheatGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a deluxe wheat garlic burger with bacon, avocado, and special sauce." << endl;
    }
};

class PremiumWheatGarlicBurger : public GarlicBurger{
    public:

    void prepare() override {
        cout << "Preparing a premium wheat garlic burger with truffle aioli, arugula, and aged cheddar." << endl;
    }
};

// meal factory interface
class MealFactory {
    public:
    virtual Burger* createBurger(string& type) = 0; // pure virtual function for creating a burger
    virtual GarlicBurger* createGarlicBurger(string& type) = 0; // pure virtual function for creating a garlic burger
    virtual ~MealFactory() {} // virtual destructor for proper cleanup of derived classes
};


// franchise 1 : SinghBurger
class SinghBurger : public MealFactory {
    public:
    Burger* createBurger(string& type) override {
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

    GarlicBurger* createGarlicBurger(string& type) override {
        if(type == "basic"){
            return new BasicGarlicBurger();
        }
        else if(type == "deluxe"){
            return new DeluxeGarlicBurger();
        }
        else if(type == "premium"){
            return new PremiumGarlicBurger();
        }
        else{
            cout << "Invalid garlic burger type." << endl;
            return nullptr;
        }
    }
};



// franchise 2 : WheatBurger
class KingBurger : public MealFactory {
    public:
    Burger* createBurger(string& type) override {
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

    GarlicBurger* createGarlicBurger(string& type) override {
        if(type == "basic"){
            return new BasicWheatGarlicBurger();
        }
        else if(type == "deluxe"){
            return new DeluxeWheatGarlicBurger();
        }
        else if(type == "premium"){
            return new PremiumWheatGarlicBurger();
        }
        else{
            cout << "Invalid garlic burger type." << endl;
            return nullptr;
        }
    }
};



int main(){
    string type = "premium"; // Example burger type

    MealFactory* singhFactory = new SinghBurger(); // Create a SinghBurger factory
    Burger* singhBurger = singhFactory->createBurger(type);
    singhBurger->prepare();


    MealFactory* kingFactory = new KingBurger(); // Create a KingBurger factory
    Burger* kingBurger = kingFactory->createBurger(type);
    kingBurger->prepare();
}

