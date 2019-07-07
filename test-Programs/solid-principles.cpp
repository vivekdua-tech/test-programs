//
//  solid-principles.cpp
//  test-Programs
//
//  Created by vidua on 12/19/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <vector>


using namespace std;

// Solid Principles of OOP

// SRP
// OCP
// LSP
// ISP
// DIP

// OCP open for extension but closed for modificaiton


enum class Color { Red, Blue, Green };
enum class Size  { Small, Medium, Large };

struct Product {
    string name;
    Color color;
    Size size;
    
    Product(string n, Color c, Size s) :
    name(n), color(c), size(s) {};
};

template <typename T>
struct spec {
    // Given an item if the item qualifies with the specification
    virtual bool is_satisfied(T *item) = 0;
};


// Filtering Spec
template <typename T>
struct Filter {
    // Given list of items run the specification and return the filtered list of items
    virtual vector<T*> filter(vector<T*> items, spec<T>& spec) = 0;
};

struct ImplementedFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, spec<Product>& spec) override {
        vector<Product*> result;
        for (auto &p: items) {
            if (spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};

// Implemented specifications
struct ColorSpec : spec<Product> {
    Color _color;
    
    explicit ColorSpec (const Color color) :
    _color(color) {}
    
    bool is_satisfied(Product *item) override {
        return item->color == _color;
    }
};

int main() {
    
    Product apple("Apple", Color::Green, Size::Small);
    Product tree("Tree", Color::Green, Size::Large);
    Product house("House", Color::Blue, Size::Large);
    
    vector<Product*> all {&apple, &tree, &house};
    
    ImplementedFilter If;
    
    ColorSpec green(Color::Green);
    auto green_items = If.filter(all, green);
}


// Liskov Substitution Principle
// If an interface takes an object of type Parent, it should equally taken an object to type Child without
// anything breaking.
// Rectangle and Square example

// Interface Segregation Principle
// Example breaking the ISP -

struct IMachine {
    virtual void print(vector<Document*> docs) = 0;
    virtual void fax(vector<Document*> docs) = 0;
    virtual void scan(vector<Document*> docs) = 0;
};
// If we have to implement fax, we need to inherit the Imachine class even though we do not have to implement
// other functions viz print and scan.


// Dependency Inversion Principle
// High Level modules should NOT depend on low level modules. Both should depend on abstractions.
// Abstractions should not depend on details, Details should depend on abstractions.
