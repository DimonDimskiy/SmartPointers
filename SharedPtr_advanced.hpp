// Smart pointer with shared ownership

// Make your own smart pointer template class shared_ptr.
// Requirements:
// The implementation should be as optimal as possible both in terms of the operation time of the main operations and of memory,
// i.e. no extra information should be stored or extra calls should be made.

// Complication 1. Implement an analogue of make_shared (optional).
// Complication 2. Make it possible to define a custom deleter (optional).
// Complication 3. Implement work with T[] (optional).

#include <utility>


template<class C>
using owner = C;

template <typename T>
class SharedPtr
{
public:
    SharedPtr() noexcept :ptr(nullptr){};
    explicit SharedPtr(T* rawPtr): ptr(rawPtr){count = new long(1);}
    SharedPtr(SharedPtr&& obj) noexcept :ptr(std::exchange(obj.ptr, nullptr)){}
    SharedPtr(SharedPtr& obj): ptr(obj.ptr){*count += 1;}
    ~SharedPtr() noexcept{
        *count -= 1;
        if(*count == 0){
            delete ptr;
            delete count;
        }
    };

    T& operator*() const noexcept {return *ptr;}                                  
    T* operator->() const noexcept {return ptr;}   

    SharedPtr& operator=(const SharedPtr& obj) noexcept{
        *count += 1;
        return obj;
    }; 

    SharedPtr& operator = (SharedPtr&& obj) noexcept {                            
    delete ptr;
    ptr = obj.ptr;
    obj.ptr = nullptr;
    return *this;
    };         

private:   
    owner<T*> ptr;
    long* count; 
};
