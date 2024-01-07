#ifndef UNIQUE_TPP
#define UNIQUE_TPP

#include "UniquePtr.hpp"
#include <utility>

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr): m_resource{ptr} {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& src) noexcept: m_resource{src.m_resource}{
    src.m_resource = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& rhs) noexcept{
    if(this != &rhs){
        delete m_resource;
        m_resource = std::exchange(rhs.m_resource, nullptr);
    }
    return *this;
}

template <typename T>
UniquePtr<T>::~UniquePtr(){
    release();
}


template <typename T>
void UniquePtr<T>::release(){ 
    if(m_resource){
        delete m_resource;
        m_resource = nullptr;
    }
}

template <typename T>
void UniquePtr<T>::reset(T* ptr){
    release();
    m_resource = ptr; 
}

template <typename T>
void UniquePtr<T>::swap(UniquePtr& other){
    std::swap(m_resource,other.m_resource);
}

template <typename T>
const T* UniquePtr<T>::get() const{
    return m_resource;
}

template <typename T>
T* UniquePtr<T>::get() {
    return const_cast<T*>(std::as_const(*this).get());
}

template <typename T>
UniquePtr<T>::operator bool() const{
    return m_resource != nullptr;
}

template <typename T>
T& UniquePtr<T>::operator*() const{
    return *m_resource;
}


template <typename T>
T* UniquePtr<T>::operator->() const{
    return m_resource;
}

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
#endif