/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) 2024 peng Hou.
 * 
 * CPP idioms : CRTP (Curiously Recurring Template Pattern 奇异递归)
 * 
 * Description: 基类是类模板，派生类在继承该基类时，将自身作为模板参数传递给基类。
 *   - 静态多态：编译时，
 *   - 动态多态：运行时，虚函数表和虚函数表指针
 *   - 省去动态绑定、查询虚函数表带来得开销  
 *  
 * Apply:
 * 1. std::enable_shared_from_this
 *    在C++中想要返回一个已经被shared_ptr管理的对象的this，为了防止this已经被释放而导致成为悬挂指针
 *    可能会考虑以shared_ptr的形式返回this  
 * 2. 多态拷贝构造
 * 3. 多态链式编程
*/
#include <iostream>
#include <memory>

template<class DerivedT>
class Based {
public:
    virtual ~Based() {}
    void interface() {
        static_cast<DerivedT*>(this)->implementation();
    }
    void implementation() {
        std::cout << "Default implementation in Base \n";
    }
};

class Derived: public Based<Derived> {
public:
    void implementation() {
        std::cout << "Custom implementation in Derived \n";
    }
};
/////////////////////////////////////////////////////////////

class Shape {
public:
    virtual ~Shape(){}
    virtual Shape* clone() const = 0;
};

template<class DerivedT>
class Shape_CRTP : public Shape {
public:
    virtual ~Shape_CRTP() {}
    virtual Shape* clone() const override {
        return new DerivedT(static_cast<DerivedT const&>(*this));
    }
};

class Square : public Shape_CRTP<Square> {
};

class SharedPtr : public std::enable_shared_from_this<SharedPtr> {
public:
    std::shared_ptr<SharedPtr> getptr() {
        return shared_from_this();
    }    
};

int main() {
    /* CRTP */
    Derived d;
    d.interface();
    
    return 0;
}


