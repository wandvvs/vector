#pragma once

#include "vector.hpp"

#include <cassert>
#include <iostream>

inline void push_back_test()
{
    vector<int> vec;
    vec.push_back(1);
    assert(vec[0] == 1);
    std::cout << "[+] push_back_test" << std::endl;
}

inline void copy_ctor_test()
{
    vector<int> vec;
    vec.push_back(1);
    
    vector<int> vec2(vec);
    assert(vec2[0] == 1);
    std::cout << "[+] copy_ctor_test" << std::endl;
}

inline void operator_equal_test()
{
    vector<int> vec;
    vector<int> vec2;

    vec.push_back(1);

    vec2 = vec;
    assert(vec2[0] == 1);
    std::cout << "[+] operator_equal test" << std::endl;
}

inline void move_ctor_test()
{
    vector<int> vec;
    vec.push_back(1);
    vector<int> vec2(std::move(vec));
    assert(vec2[0] == 1);
    assert(vec.get_sz() == 0);
    assert(vec.get_cap() == 0);
    assert(vec.get_arr() == nullptr);

    std::cout << "[+] move_ctor_test" << std::endl;
}

inline void operator_equal_move_test()
{
    vector<int> vec;
    vector<int> vec2;
    vec.push_back(1);
    vec2 = std::move(vec);

    assert(vec2[0] == 1);
    assert(vec.get_sz() == 0);
    assert(vec.get_cap() == 0);
    assert(vec.get_arr() == nullptr);

    std::cout << "[+] operator_equal_move_test" << std::endl;

}

inline void emplace_back_test()
{
    struct Test
    {
        std::string a,b,c;
        Test(std::string A, std::string B, std::string C) : a(A), b(B), c(C) {}
    };

    vector<Test> vec;
    std::string str = "Hello Test";

    vec.emplace_back(str, "123", "321");
    assert(!str.empty());
    assert(vec[0].a == "Hello Test");
    assert(vec[0].c == "321");
    
    std::cout << "[+] emplace_back_test" << std::endl;
}

inline void move_push_back_test()
{
    vector<std::string> vec;
    std::string str = "Hello";
    vec.push_back(std::move(str));
    assert(vec[0] == "Hello");
    assert(str != "Hello");

    std::cout << "[+] move_push_back_test" << std::endl;
}

inline void tests()
{
    push_back_test();
    copy_ctor_test();
    operator_equal_test();
    move_ctor_test();
    operator_equal_move_test();
    emplace_back_test();
    move_push_back_test();
}
