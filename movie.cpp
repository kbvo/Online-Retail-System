#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, const std::string genre, const std::string rating, double price, int qty) : 
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
    set<string> myKeywords;
    
    myKeywords = parseStringToWords(getName()); // parse name into keywords
    myKeywords.insert(convToLower(genre_)); // add genre in lowercase to keywords
    
    return myKeywords;
}

std::string Movie::displayString() const
{
    std::ostringstream movieDisplay;

    movieDisplay << getName() << endl;
    movieDisplay << "Genre: " << genre_ << " Rating: " << rating_ << endl;
    movieDisplay << std::fixed << std::setprecision(2) << getPrice() << " " << getQty() << " left." << endl;
    
    return movieDisplay.str();
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << endl;
    os << rating_ << endl;
}