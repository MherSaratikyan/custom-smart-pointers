#ifndef SHARED_TPP
#define SHARED_TPP

#include "SharedPtr.hpp"
#include <stdexcept>

template <typename T>
SharedPtr<T>::SharedPtr(): m_ptr{nullptr} {}

template <typename T>
SharedPtr<T>::SharedPtr(std::nullptr_t): m_ptr{nullptr} {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr): m_ptr{new ControlBlock(ptr)} {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& src): m_ptr{src.m_ptr}{
    if(m_ptr != nullptr){
        m_ptr->incrementStrongCount();
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& src): m_ptr{src.m_ptr}{
    if(m_ptr != nullptr){
        m_ptr->incrementStrongCount();
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& src) noexcept: m_ptr{src.m_ptr}{
    src.m_ptr = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& rhs){
    SharedPtr<T> temp(rhs);
    swap(temp);
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& rhs) noexcept{
    if(this != &rhs){
        if(m_ptr != nullptr){
            m_ptr->decrementStrongCount();
            if(m_ptr->getStrongCount() == 0 && m_ptr->getWeakCount() == 0){
                delete m_ptr;
            }
        }

        m_ptr = std::exchange(rhs.m_ptr, nullptr);
    }

    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr(){
    if(m_ptr != nullptr){
        m_ptr->decrementStrongCount();
        if(m_ptr->getStrongCount() == 0 && m_ptr->getWeakCount() == 0){
            delete m_ptr;
        }
    }
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr<T>& other){
    std::swap(m_ptr,other.m_ptr);
}

template <typename T>
T& SharedPtr<T>::operator*() const{
    if(m_ptr == nullptr){
        throw std::runtime_error("Attemt to dereference nullptr");
    }
    return *(m_ptr->m_resource);
}

template <typename T>
T* SharedPtr<T>::operator->() const{
    if(m_ptr == nullptr){
        throw std::runtime_error("Attempt to dereference nullptr");
    }
    return m_ptr->m_resource;
}

template <typename T>
const T* SharedPtr<T>::get() const{
    if(m_ptr == nullptr){
        throw std::runtime_error("Attempt to dereference nullptr");
    }
    return m_ptr->m_resource;
}

template <typename T>
T* SharedPtr<T>::get(){
    return const_cast<T*>(std::as_const(*this).get());
}

template <typename T>
int SharedPtr<T>::use_count() const{
    return (m_ptr == nullptr) ? 0 : m_ptr->getStrongCount();
}

template <typename T>
SharedPtr<T>::operator bool() const{
    return (m_ptr != nullptr) && (m_ptr->getStrongCount() != 0);
}

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args){
    return SharedPtr<T>(new T{std::forward(args)...});
}

#endif