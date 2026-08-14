#include <iostream>
using namespace std;

class Calculator {
public:
    int divide(int a, int b) {
        if (b == 0) {
            throw "Division by zero error";  // throw exception
        }
        return a / b;
    }
};

int main() {
    Calculator obj;   // object creation

    try {
        int result = obj.divide(10, 0);  // calling function
        cout << "Result: " << result << endl;
    }
    catch (const char* msg) {
        cout << "Exception caught: " << msg << endl;
    }

    return 0;
}