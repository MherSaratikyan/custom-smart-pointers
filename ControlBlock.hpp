#ifndef CONTROL_BLOCK_HPP
#define CONTROL_BLOCK_HPP

#include <type_traits>

template <typename T>
struct ControlBlock{
public:

    ControlBlock(T* ptr)
    : m_resource{ptr}
    , m_strong_count{1}
    , m_weak_count{0} {}

    void incrementStrongCount(){
        ++m_strong_count;
    }

    void decrementStrongCount(){
        --m_strong_count;
        if(m_strong_count == 0){
            delete m_resource;
            m_resource = nullptr;
        }
    }

    void incrementWeakCount(){
        ++m_weak_count;
    }

    void decrementWeakCount(){
        --m_weak_count;
    }

    int getStrongCount() const{
        return m_strong_count;
    }

    int getWeakCount() const{
        return m_weak_count;
    }

    
    ~ControlBlock(){
        if(m_strong_count == 0){
            delete m_resource;
        }
    }

    T* m_resource;
    int m_strong_count;
    int m_weak_count;
    
};
#endif