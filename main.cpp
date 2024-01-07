#include <iostream>
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "WeakPtr.hpp"

struct A{
    A(int a, double b){
        std::cout<<"\nA::A(int, double)\n";
    }

    void print() const{
        std::cout<<__PRETTY_FUNCTION__<<'\n';
    }
};

int main(){
    SharedPtr<int> mySharedInt1(new int(44));
    SharedPtr<int> mySharedInt2(mySharedInt1);
    std::cout<<"\nReference count: "<<mySharedInt2.use_count();
    std::cout<<"\nThe value: "<<(*mySharedInt1);

    WeakPtr<int> myWeakInt1 = mySharedInt1;
    WeakPtr<int> myWeakInt2 = myWeakInt1;

    std::cout<<"\nReference count: "<<myWeakInt2.use_count();
    std::cout<<"\nThe value: "<<*(myWeakInt1.lock());

    WeakPtr<int> myWeakInt3;
    {
        std::cout<<"\nInner scope\n";
        SharedPtr<int> mySharedInt3(new int(66));
        myWeakInt3 = mySharedInt3;
        std::cout<<"\nReference count: "<<myWeakInt3.use_count();
        std::cout<<"\nThe value: "<<*(myWeakInt3.lock());
    }
    std::cout<<"\nAfter leaving the inner scope:";
    std::cout<<"\nReference count: "<<myWeakInt3.use_count();

    std::cout<<"\ntesting UniquePtr class template\n";
    UniquePtr<A> myUniqueA1 = make_unique<A>(42, 3.14);
    myUniqueA1->print();

    UniquePtr<A> myUniqueA2 = std::move(myUniqueA1);
    myUniqueA2->print();
}