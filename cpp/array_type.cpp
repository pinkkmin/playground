#include <iostream>
#include <typeinfo>

int main() {    

    int array[1] {1};
    int array1[] {2};
    int array2[] {1, 2};
    int array3[1][1] {{1}};
    char str[1]{1};

    std::cout << "array:" << typeid(array).name() << ":" << typeid(array).hash_code() << std::endl;
    std::cout << "array1:" << typeid(array1).name() << ":" << typeid(array1).hash_code() << std::endl;
    std::cout << "array2:" << typeid(array2).name() << ":" << typeid(array2).hash_code() << std::endl;
    std::cout << "array3:" << typeid(array3).name() << ":" << typeid(array3).hash_code() << std::endl;

    std::cout << "str:" << typeid(str).name() << ":" << typeid(str).hash_code() << std::endl;
    std::cout << "str[0]:" << typeid(str[0]).name() << ":" << typeid(str[0]).hash_code() << std::endl;
    return 0;
}

/** OUT:
array:A1_i:15662646373754146716
array1:A1_i:15662646373754146716
array2:A2_i:6987825362790964077
array3:A1_A1_i:16314808761641955905
str:A1_c:9797170860092239068
str[0]:c:10959529184379665549
*/