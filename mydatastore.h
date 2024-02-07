#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include <deque>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    // inherited methods
    MyDataStore(); // constructor
    ~MyDataStore(); // destructor (deallocates products and users)
    void addProduct(Product* p); // add products and map keywords
    void addUser(User* u); // add users and map usernames
    std::vector<Product*> search(std::vector<std::string>& terms, int type); // AND/OR search
    void dump(std::ostream& ofile); // outputs updated database

    // added methods
    void addToCart(const std::string& userName, int hitResultIndex); // add product to user's cart
    void viewCart(const std::string& userName); // view products in user's cart
    void buyCart(const std::string& userName); // buy products in user's cart
    
private:
    std::vector<Product*> myProducts; // stores products
    std::map<std::string, std::set<Product*>> myKeywords; // stores keywords that map to a set of products that contain that keyword
    std::map<std::string, User*> myUsers; // stores usernames that map to users
    std::map<std::string, std::deque<Product*>> myCarts; // stores usernames that map to their carts
    std::vector<Product*> hitResult; // stores hits after search
};

#endif