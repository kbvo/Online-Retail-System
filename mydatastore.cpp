#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    // deallocate products
    for (size_t i = 0;  i < myProducts.size(); ++i) {
        delete myProducts[i];
    }
    
    // deallocate users
    for (map<string, User*>::iterator it = myUsers.begin(); it != myUsers.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    myProducts.push_back(p); // add product

    // add product's keywords (if added already then just find) and insert product that contains them into set of products each keyword is mapped to
    set<string> productKeywords = p->keywords();
    for (set<string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it) {
        myKeywords[convToLower(*it)].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    // add user and map to username
    myUsers[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    set<Product*> myHits;

    // if no terms or invalid type, return nothing
    if (terms.empty() || (type != 0 && type != 1)) {
        return hitResult;
    }
    
    // AND search
    if (type == 0) {
        map<string, set<Product*>>::iterator it = myKeywords.find(terms[0]); // find first term in my keywords
        if (it != myKeywords.end()) { // if found
            myHits = it->second; // my hits are the products with that term
            
            // iterate through the rest of the terms
            for (size_t i = 1; i < terms.size(); ++i) {
                map<string, set<Product*>>::iterator it = myKeywords.find(terms[i]); // find term in my keywords
                if (it != myKeywords.end()) { // if found
                    myHits = setIntersection(myHits, it->second); // take intersecting hits between my hits so far and hits for current term
                }
                else { // if no intersecting hits 
                    return hitResult; // return nothing
                }
            }
        }
        else { // if first term is not found in keywords
            return hitResult; // return nothing
        }
    }
    // OR search
    else {
        // iterate through all terms
        for (size_t i = 0; i < terms.size(); ++i) {
            map<string, set<Product*>>::iterator it = myKeywords.find(terms[i]); // find term in my keywords
            if (it != myKeywords.end()) { // if found
                myHits = setUnion(myHits, it->second); // take union of all hits found so far
            }
        }
    }

    return hitResult = vector<Product*>(myHits.begin(), myHits.end()); // convert set myHits into vector hitResults and return
}

void MyDataStore::dump(std::ostream& ofile)
{   
    // print product information
    ofile << "<products>" << endl;
    for (size_t i = 0; i < myProducts.size(); ++i) {
        myProducts[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    
    // print user information
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = myUsers.begin(); it != myUsers.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(const std::string& userName, int hitResultIndex)
{
    map<string, User*>::iterator it = myUsers.find(userName); // find username in my usernames of users
    
    // if not found or hit index is out of range of hitResult, print error message and exit
    if (it == myUsers.end() || hitResultIndex > static_cast<int>(hitResult.size()) || hitResultIndex <= 0) {
        cout << "Invalid request" << endl;
        return;
    }

    Product* hitProduct = hitResult[--hitResultIndex]; // access hit product in hitResult
    myCarts[userName].push_back(hitProduct); // add username (if already added then just find) and add hit product in FIFO order to cart mapped to username
}

void MyDataStore::viewCart(const std::string& userName)
{
    map<string, deque<Product*>>::iterator cartIt = myCarts.find(userName); // find username in usernames with carts

    // if not found, print error message and exit
    if (cartIt == myCarts.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    // iterate through user's cart's products with productIt and display products in cart
    int itemCount = 0;
    for (deque<Product*>::iterator productIt = cartIt->second.begin(); productIt != cartIt->second.end(); ++productIt) {
        cout << "Item " <<  ++itemCount << endl;
        cout << (*productIt)->displayString() << endl;
    }
}

void MyDataStore::buyCart(const std::string& userName)
{
    map<string, User*>::iterator userIt = myUsers.find(userName); // find username in usernames of my users
    map<string, deque<Product*>>::iterator cartIt = myCarts.find(userName); // find username in usernames with carts
    
    // if not found in usernames with cart, print error message and exit
    if (cartIt == myCarts.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    // iterate through user's cart's products and buy products in cart
    for (size_t i = 0; i < cartIt->second.size(); ) {
        // if product in stock and user has enough money
        if (cartIt->second[i]->getQty() > 0 && userIt->second->getBalance() >= cartIt->second[i]->getPrice()) {
            cartIt->second[i]->subtractQty(1); // subtract product's quantity by 1
            userIt->second->deductAmount(cartIt->second[i]->getPrice()); // product's price debited from user's balance
            if (cartIt->second.front() == cartIt->second[i]) { // if product is front element of cart
                cartIt->second.pop_front(); // remove product from cart using pop_front
            }
            else { // if element is not front element of cart
                cartIt->second.erase(cartIt->second.begin() + i); // remove product from cart using erase
            }
        }
        else { // if product can't be bought
            ++i; // skip and move to next product
        }
    }
}