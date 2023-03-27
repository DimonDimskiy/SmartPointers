// Smart pointer with unique ownership

// Make your smart pointer template class unique_ptr.
// Requirements:
// The implementation should be maximally optimal both in terms of the running time of the main operations,
// and of memory, i.e. no redundant information should be stored or redundant calls made.

// Complication 1. Implement an analogue of make_unique (optional).
// Complication 2. Make it possible to define a custom deleter (optional).
// Complication 3. Implement work with T[] (optional).
#include <utility>


template<class C>
using owner = C;


template <typename T>
class UniquePtr
{
public:
    UniquePtr() noexcept :ptr(nullptr){}                                          // Конструктор по умолчанию
    explicit UniquePtr(T* rawPtr) noexcept :ptr(rawPtr){}                         // Конструуктор с аргументом "rawPtr"
    UniquePtr(UniquePtr&& obj) noexcept :ptr(std::exchange(obj.ptr, nullptr)){}   // move конструктор 
    
    ~UniquePtr()noexcept{delete ptr;}                                             // деструктор

    T& operator*() const noexcept {return *ptr;}                                  // операторы dereference
    T* operator->() const noexcept {return ptr;}                                    
    
    UniquePtr& operator = (UniquePtr&& obj) noexcept {                            //присваивание через move
    delete ptr;
    ptr = obj.ptr;
    obj.ptr = nullptr;
    return *this;
    };    

private:
    UniquePtr(const UniquePtr&) = delete;                               // удален конструктор копирования
    void operator=(const UniquePtr&) = delete;                          // удален оператор присваивания через копирование

    owner<T*> ptr;                                                      // явно владеем указателем
};

