#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base vptr address:0x" << std::hex << reinterpret_cast<void*>(this) << std::endl;

        size_t* vptr  = reinterpret_cast<size_t*>(this);
        std::cout << "Base vptr table address:0x" << std::hex << *vptr << std::endl;
    }    
    virtual int func() {
        return 0;
    }
};

class Derived: public Base {
public:   
    Derived():Base() {
        std::cout << "Derived vptr address:0x" << std::hex << reinterpret_cast<void*>(this) << std::endl; 
        size_t* vptr  = reinterpret_cast<size_t*>(this);
        std::cout << "Derived vptr table address:0x" << std::hex << *vptr << std::endl; 
    } 
    virtual int func() override {
        return 1;
    }
};

int main() {
    Base b;
    Derived d;

    std::cout << " sizeof(class Base):" << sizeof(Base) << "\n";
    std::cout << " sizeof(class Derived):" << sizeof(Derived) << "\n";

    return 0;
}