#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "ControlBlock.hpp"
template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr{
public:
    WeakPtr();
    WeakPtr(const WeakPtr&);
    WeakPtr(WeakPtr&&) noexcept;
    WeakPtr(const SharedPtr<T>& );

    WeakPtr& operator=(const WeakPtr&);
    WeakPtr& operator=(WeakPtr&&) noexcept;

    ~WeakPtr();

public:
    void swap(WeakPtr& other);
    int use_count() const;
    bool expired() const;
    SharedPtr<T> lock() const;
private:
    ControlBlock<T>* m_ptr;

    friend class SharedPtr<T>;
};

#include "WeakPtr.tpp"
#endif