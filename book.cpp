#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, const std::string author, const std::string isbn, double price, int qty) : 
    Product(category, name, price, qty),
    author_(author),
    isbn_(isbn)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
    set<string> myKeywords;
    set<string> authorKeywords;

    // parse name into keywords
    myKeywords = parseStringToWords(getName());
    
    // parse author into keywords
    authorKeywords = parseStringToWords(author_);
    myKeywords.insert(authorKeywords.begin(), authorKeywords.end());

    // add ISBN into keywords
    myKeywords.insert(isbn_);
    
    return myKeywords;
}

std::string Book::displayString() const
{
    std::ostringstream bookDisplay;

    bookDisplay << getName() << endl;
    bookDisplay << "Author: " << author_ << " ISBN: " << isbn_ << endl;
    bookDisplay << std::fixed << std::setprecision(2) << getPrice() << " " << getQty() << " left." << endl;
    
    return bookDisplay.str();
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}