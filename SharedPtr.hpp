#ifndef SHARED_HPP
#define SHARED_HPP

#include "ControlBlock.hpp"
#include "WeakPtr.hpp"

template <typename T>
class SharedPtr{
public:
    SharedPtr();
    SharedPtr(std::nullptr_t);
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr&);
    SharedPtr(const WeakPtr<T>&);
    SharedPtr(SharedPtr&&) noexcept;
    SharedPtr& operator=(const SharedPtr&);
    SharedPtr& operator=(SharedPtr&&) noexcept;
    ~SharedPtr();
public:

    void swap(SharedPtr& other);
    
    T& operator*() const;
    T* operator->() const;

    const T* get() const;
    T* get();

    int use_count() const;
    operator bool() const;
private:
    ControlBlock<T>* m_ptr;
    friend class WeakPtr<T>;
};

#include "SharedPtr.tpp"
#endif
