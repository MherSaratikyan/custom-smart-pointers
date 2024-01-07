#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include <type_traits>

template <typename T>
class UniquePtr{
public:
    UniquePtr(T* ptr = nullptr);
    UniquePtr(UniquePtr<T>&&) noexcept;
    UniquePtr& operator=(UniquePtr<T>&&) noexcept;
    ~UniquePtr();

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

public:
    void release();
    void reset(T* ptr = nullptr);
    void swap(UniquePtr& other);

public:
    const T* get() const;
    T* get();
    explicit operator bool() const;

public:
    T& operator*() const;

    T* operator->() const;
private:
    T* m_resource;
};

#include "UniquePtr.tpp"
#endif