#include "MagicalContainer.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

namespace ariel{

    // prime check
    bool isPrime(int elem)
    {
        if (elem == 1)
        {
            return false;
        }
        else if (elem == 2)
        {
            return true;
        }
        else
        {
            for (int i = 2; i < sqrt(elem) + 1; i++)
            {
                if (elem % i == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }

    // sorting originalElem vector by bubble sort
    void MagicalContainer::sortOriginalElem()
    {
        for(unsigned long i = 0; i < originalElem.size(); i++)
        {
            for(unsigned long j = 0; j < originalElem.size() - i - 1; j++)
            {
                if(originalElem[j] > originalElem[j + 1])
                {
                    int temp = originalElem[j];
                    originalElem[j] = originalElem[j + 1];
                    originalElem[j + 1] = temp;
                }
            }
        }
    }

    // fixing the sortedElem vector
    void MagicalContainer::fixSorted()
    {
        sortedElem.clear();
        //add all elements to sortedElem
        for (auto it = originalElem.begin(); it != originalElem.end(); ++it)
        {
            sortedElem.push_back(&(*it));
        }
    }

    // fixing the primeElem vector
    void MagicalContainer::fixPrime()
    {
        primeElem.clear();
        //add all prime numbers to primeElem
        for (auto it = originalElem.begin(); it != originalElem.end(); ++it)
        {
            if (isPrime(*it))
            {
                primeElem.push_back(&(*it));
            }
        }
    }

    // fixing the crossElem vector
    void MagicalContainer::fixCross()
    {
        crossElem.clear();
        //add all elements to crossElem

        auto start = originalElem.begin();
        auto end = --originalElem.end();

        // adding the elements to crossElem by crossing the originalElem vector
        while(start < end)
        {
            crossElem.push_back(&(*start));
            crossElem.push_back(&(*end));
            start++;
            end--;
        }
        // if the vector is odd, add the middle element
        if (start == end)
        {
            crossElem.push_back(&(*start));
        }

    }

    // ***************** MagicalContainer *****************
    // ***************** MagicalContainer *****************
    // ***************** MagicalContainer *****************

    void MagicalContainer::addElement(int elem)
    {   
        // add to originalElem
        originalElem.push_back(elem);
        sortOriginalElem();

        // add to sortedElem
        fixSorted();

        // add to primeElem
        fixPrime();

        // add to CrossElem
        fixCross();
    }

    void MagicalContainer::removeElement(int elem)
    {
        // check if elem is in originalElem
        bool found = false;
        for (auto it = originalElem.begin(); it != originalElem.end(); ++it)
        {
            if (*it == elem)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            throw std::runtime_error("Invalid argument");
        }

        // remove from originalElem
        originalElem.erase(std::remove(originalElem.begin(), originalElem.end(), elem), originalElem.end());

        // remove from sortedElem
        fixSorted();

        // remove from primeElem
        fixPrime();

        // remove from CrossElem
        fixCross();

    }

    int MagicalContainer::size()
    {   
        return originalElem.size();
    }





    // ***************** AscendingIterator *****************
    // ***************** AscendingIterator *****************
    // ***************** AscendingIterator *****************


    // Constructors

    // default constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : container(container), iter(container.sortedElem.begin()), pos(0) {}

    // copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) : container(other.container), iter(other.iter), pos(other.pos) {}

    // copy assignment operator
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::runtime_error("Invalid argument");
        }
        iter = other.iter;
        pos = other.pos;
        return *this;
    }

    // Operators

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
    {
        // if we are at the end of the container then throw exception
        if(iter == container.sortedElem.end())
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++pos;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*()
    {   
        // if we are at the end of the container then throw exception
        if(iter == container.sortedElem.end())
        {
            throw std::out_of_range("Out of range");
        }
        return **iter;
    }

    // Comparison operators

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos == other.pos;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos < other.pos;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos > other.pos;
    }

    // Getters

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin()
    {
        iter = container.sortedElem.begin(); // iterates to the beginning of the container
        pos = 0;                             // sets the position to 0
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end()
    {
        iter = container.sortedElem.end(); // iterates to the end of the container
        pos = container.sortedElem.size(); // sets the position to the size of the container
        return *this;
    }


    // ***************** SideCrossIterator *****************
    // ***************** SideCrossIterator *****************
    // ***************** SideCrossIterator *****************

    // Constructors

    // default constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : container(container), iter(container.crossElem.begin()), pos(0) {}

    // copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) : container(other.container), iter(other.iter), pos(other.pos) {}

    // copy assignment operator
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::runtime_error("Invalid argument");
        }
        iter = other.iter;
        pos = other.pos;
        return *this;
    }
    // Operators

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        if(iter == container.crossElem.end()) // if we are at the end of the container then throw exception
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++pos;
        return *this;
    }

    int& MagicalContainer::SideCrossIterator::operator*()
    {
        if(iter == container.crossElem.end()) // if we are at the end of the container then throw exception
        {
            throw std::out_of_range("Out of range");
        }
        return **iter;
    }

    // Comparison operators

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos == other.pos;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos < other.pos;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos > other.pos;
    }

    // Getters

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin()
    {
        iter = container.crossElem.begin(); // iterates to the beginning of the container
        pos = 0;                             // sets the position to 0
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end()
    {
        iter = container.crossElem.end(); // iterates to the end of the container
        pos = container.crossElem.size(); // sets the position to the size of the container
        return *this;
    }


    // ***************** PrimeIterator *****************
    // ***************** PrimeIterator *****************
    // ***************** PrimeIterator *****************

    // Constructors

    // default constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : container(container), iter(container.primeElem.begin()), pos(0) {}

    // copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) : container(other.container), iter(other.iter), pos(other.pos) {}

    // copy assignment operator
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::runtime_error("Invalid argument");
        }
        iter = other.iter;
        pos = other.pos;
        return *this;
    }
    // Operators

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        if(iter == container.primeElem.end()) // if we are at the end of the container then throw exception
        {
            throw std::runtime_error("Out of range");
        }
        ++iter;
        ++pos;
        return *this;
    }

    int& MagicalContainer::PrimeIterator::operator*()
    {   
        if(iter == container.primeElem.end()) // if we are at the end of the container then throw exception
        {
            throw std::out_of_range("Out of range");
        }
        return **iter;
    }

    // Comparison operators

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos == other.pos;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos < other.pos;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
    {
        if(&container != &other.container) // if they are not the same container then throw exception
        {
            throw std::invalid_argument("Invalid argument");
        }
        return pos > other.pos;
    }

    // Getters

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin()
    {
        iter = container.primeElem.begin(); // iterates to the beginning of the container
        pos = 0;                             // sets the position to 0
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end()
    {
        iter = container.primeElem.end(); // iterates to the end of the container
        pos = container.primeElem.size(); // sets the position to the size of the container
        return *this;
    }

}


