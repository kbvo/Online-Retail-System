#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, const std::string size, const std::string brand, double price, int qty) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
    set<string> myKeywords;
    set<string> brandKeywords;

    // parse name into keywords
    myKeywords = parseStringToWords(getName());
    
    // parse brand into keywords
    brandKeywords = parseStringToWords(brand_);
    myKeywords.insert(brandKeywords.begin(), brandKeywords.end());
    
    return myKeywords;
}

std::string Clothing::displayString() const
{
    std::ostringstream clothingDisplay;

    clothingDisplay << getName() << endl;
    clothingDisplay << "Size: " << size_ << " Brand: " << brand_ << endl;
    clothingDisplay << std::fixed << std::setprecision(2) << getPrice() << " " << getQty() << " left." << endl;
    
    return clothingDisplay.str();
}

void Clothing::dump(std::ostream& os) const
{
    Product::dump(os);
    os << size_ << endl;
    os << brand_ << endl;
}