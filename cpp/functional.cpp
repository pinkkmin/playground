/***
 * std::function  
 *  --> [functors] --> function wrapper
 *  --> 函数封装器 将函数封装成 functor
 * std::bind    
 *  --> binders
 *  --> 绑定参数到函数对象，实现延时执行 
 * functor 
 * lambda
 *
 * target:
 * functor --to--> std::function
 * lambda --to--> std::function
*/
#include <iostream>
#include <functional>


class AddFunctor {
public:
    AddFunctor():lhs(0), rhs(0) {};
    AddFunctor(int a, int b):lhs(a), rhs(b) {}
    int operator()() {
        return lhs + rhs;
    }

    int operator()(int a, int b) {
        return a + b;
    }
private:    
    int lhs, rhs;
};

class MathUtils{
public:
    MathUtils() = default;
    static int Add(int a, int b) {
        return a + b;
    }

    int Sub(int a, int b) {
        return a - b;
    }
};

int PlainAdd(int a, int b) {
    return  a + b;
}

int main() {

    std::cout << "Learn CPP: std::function, functor, lambda, std::bind. \n";

    // functor
    {
        AddFunctor add(2, 10);
        // case1: functor.
         std::cout << "functor case1: " << add() << "\n";
    }

    // std::function
    {
        using AddFunc_t = std::function<int (int, int)>;
        
        // case1: assgin static member function to std::function.
        AddFunc_t add = MathUtils::Add;
        std::cout << "std::function case1: " << add(10, 10) << "\n";

        // case2: assgin functor to std::function
        AddFunc_t add2 = AddFunctor();
        std::cout << "std::function case2: " << add2(5, 5) << "\n";

        // case3: assigin member function to std::function.
        using SubFunc_t = std::function<int(MathUtils*, int, int)>;
        SubFunc_t sub = &MathUtils::Sub;
        MathUtils math_utils;
        std::cout << "std::function case1: " << sub(&math_utils, 10, 10) << "\n";
    }

    // std::bind
    {
        using AddFunc_t = std::function<int (int, int)>;
        AddFunc_t add_func = AddFunctor();
        auto Add = std::bind(add_func, 1, 32);
        auto Add_10 = std::bind(add_func, 10, std::placeholders::_1);
        
        // case1: bind function as function object.
        std::cout << "std::bind case1:" << Add(1, 5) << "\n";
    
        // case2: bind function with placeholders.
        std::cout << "std::bind case2:" << Add_10(5) << "\n";

        // case3: bind a functor.
        AddFunctor add{};
        // auto bind_functor = std::bind(&AddFunctor::operator(), add);
        std::cout << "std::bind case3:" << Add_10(3, 3) << "\n";

        // case4: bind global function.
        auto bind_global_func = std::bind(&PlainAdd, 13,12);
        std::cout << "std::bind case4:" << bind_global_func() << "\n";
    
        // case4: bind lambda
        int a = 10;
        auto lambda1 = [](int a, int b)->int{
            return a + b;
        };

        auto bind_lambda1 = std::bind(lambda1, 10, 15);

        auto lambda2 = [](int &a, int b)->int{
            a ++;
            return a + b;
        };

        auto bind_lambda2 = std::bind(lambda2, std::placeholders::_1, std::placeholders::_2);

        std::cout << "std::bind case4:" << bind_lambda1() << "\n";
        std::cout << "std::bind case4:" << bind_lambda2(a, 3) << "\n";
    }

    //lambda
    {
        auto result = [](int a, int b) -> int {
            return a + b;
        }(10, 15);

    }
    return 0;
}