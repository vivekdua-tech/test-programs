//
//  iterator.cpp
//  test-Programs
//
//  Created by vivekdua on 4/19/22.
//  Copyright © 2022 Vivek Dua. All rights reserved.
//

#include <iostream>

using namespace std;

template <typename T>
class linkedlist
{
private:
    
    struct Node {
        using node_ptr = unique_ptr<Node>;
        T data{};
        
        node_ptr next = nullptr;
    };
    using node_ptr = unique_ptr<Node>;
    node_ptr head = nullptr;
    
    
public:
    
    linkedlist(std::initializer_list<T> list) noexcept;
    linkedlist(const linkedlist& other) noexcept;
    linkedlist& operator=(const linkedlist& other) noexcept;
    linkedlist(linkedlist&& other) noexcept;
    linkedlist&& operator=(linkedlist&& other) noexcept;
    
    
    struct iterator {
        friend class linkedlist;
        
        iterator() noexcept : curr(nullptr) {};
        iterator(const node_ptr& node) noexcept :
        curr(node.get()) {}
        
        iterator& operator++() noexcept {
            if (curr != nullptr) {
                prev = curr;
                curr = curr->next.get();
            }
        }
        
        bool operator!=(const iterator& other) const noexcept {
            
        }
        
        T operator*() const noexcept {
            return this->curr->data;
        }
        
        
        private:
        Node *prev = nullptr;
        Node *curr = nullptr;
        
    };
    
    
    
    
    
    
    
    
};
