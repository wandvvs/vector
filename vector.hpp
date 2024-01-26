#pragma once

#include <utility>
#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class vector
{
private:
    T* arr;
    size_t sz;
    size_t cap;
    Alloc alloc;

public:
    using Traits = std::allocator_traits<Alloc>;

    vector() : arr(nullptr), sz(0), cap(0) {}

    ~vector()
    {
        for(size_t i = 0; i < sz; ++i)
        {
            Traits::destroy(alloc, arr+i);
        }
        Traits::deallocate(alloc, arr, cap);
    }

    vector(const vector& oth) : sz(oth.sz), cap(oth.cap)
    {
        arr = Traits::allocate(alloc, sz);
        for(size_t i = 0; i < sz; ++i)
        {
            Traits::construct(alloc, arr+i, oth.arr[i]);
        }
    }

    vector& operator=(const vector& oth)
    {
        if(this != &oth)
        {
            for(size_t i = 0; i < sz; ++i)
            {
                Traits::destroy(alloc, arr+i);
            }
            Traits::deallocate(alloc, arr, cap);

            sz = oth.sz;
            cap = oth.cap;
            arr = Traits::allocate(alloc, oth.sz);

            for(size_t i = 0; i < sz; ++i)
            {
                Traits::construct(alloc, arr+i, oth.arr[i]);
            }
        }
        return *this;
    }

    vector(vector&& oth) noexcept
    {
        arr = std::exchange(oth.arr, nullptr);
        sz = std::exchange(oth.sz, 0);
        cap = std::exchange(oth.cap, 0);
    }

    vector& operator=(vector&& oth) noexcept
    {
        if(this != &oth)
        {
            for(size_t i = 0; i < sz; ++i)
            {
                Traits::destroy(alloc, arr+i);
            }
            Traits::deallocate(alloc, arr, cap);

            arr = std::exchange(oth.arr, nullptr);
            sz = std::exchange(oth.sz, 0);
            cap = std::exchange(oth.cap, 0);
        }
        return *this;
    }

    void reserve(const size_t& new_cap)
    {
        if(new_cap <= cap) return;

        T* newarr = Traits::allocate(alloc, new_cap);

        for(size_t i = 0; i < sz; ++i)
        {
            Traits::construct(alloc, newarr + i, std::move_if_noexcept(arr[i]));
        }

        for(size_t i = 0; i < sz; ++i)
        {
            Traits::destroy(alloc, arr+i);
        }
        Traits::deallocate(alloc, arr, cap);

        arr = newarr;
        cap = new_cap;
    }

    void push_back(const T& value)
    {
        if(sz == cap)
        {
            reserve((cap == 0) ? 1 : cap*2);
        }
        Traits::construct(alloc, arr+sz, value);
        sz++;
    }

    void push_back(T&& value)
    {
        if(sz == cap)
        {
            reserve((cap == 0) ? 1 : cap*2);
        }
        Traits::construct(alloc, arr+sz, std::move(value));
        sz++;
    }

    T& operator[](size_t index)
    {
        return arr[index];
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if(sz == cap)
        {
            reserve(5);
        }
        Traits::construct(alloc, arr+sz, std::forward<Args>(args)...);
        sz++;
    } 

    T* begin() {return arr;}
    T* end() {return arr+sz;}

    size_t get_sz() {return sz;}
    size_t get_cap() {return cap;}
    T* get_arr() {return arr;}
};

