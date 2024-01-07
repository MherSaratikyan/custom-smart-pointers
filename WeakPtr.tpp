#ifndef WEAK_TPP
#define WEAK_TPP

#include "WeakPtr.hpp"
#include <utility>

template <typename T> 
WeakPtr<T>::WeakPtr(): m_ptr{nullptr} {}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& src): m_ptr{src.m_ptr}{
    if(m_ptr != nullptr){
        m_ptr->incrementWeakCount();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& src) noexcept: m_ptr{src.m_ptr}{
    src.m_ptr = nullptr;
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& src): m_ptr{src.m_ptr}{
    if(m_ptr != nullptr){
        m_ptr->incrementWeakCount();
    }
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& rhs){
    WeakPtr<T> tmp(rhs);
    swap(tmp);
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& rhs) noexcept{
    if(this != &rhs){
        if(m_ptr != nullptr){
            m_ptr->decrementWeakCount();
            if(m_ptr->getWeakCount() == 0 && m_ptr->getStrongCount() == 0){
                delete m_ptr;
            }
        }
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
    }

    return *this;
}

template <typename T>
WeakPtr<T>::~WeakPtr(){
    if(m_ptr != nullptr){
        m_ptr->decrementWeakCount();
        if(m_ptr->getWeakCount() == 0 && m_ptr->getStrongCount() == 0){
            delete m_ptr;
        }
    }
}

template <typename T>
int WeakPtr<T>::use_count() const{
    return (m_ptr != nullptr) ? m_ptr->getStrongCount() : 0;
}

template <typename T>
bool WeakPtr<T>::expired() const{
    return (m_ptr == nullptr) || (m_ptr->getStrongCount() == 0);
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const{
    if(expired()){
        return SharedPtr<T>();
    }else{
        return SharedPtr<T>(*this);
    }
}

template <typename T>
void WeakPtr<T>::swap(WeakPtr<T>& other){
    std::swap(m_ptr,other.m_ptr);
}
#endif