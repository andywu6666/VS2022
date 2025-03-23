// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
    : myData()
{
}

string::string(const value_type* const ptr, const size_type count)
    : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.myRes > 15) {
        myData.bx.ptr = new value_type[count + 1];
    }
    for (size_type i = 0; i < count; i++) {
        myData.myPtr()[i] = ptr[i];
    }
    myData.myPtr()[count] = value_type();




}

string::string(const size_type count, const value_type ch)
    : myData()
{
    // construct from count * ch
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (count > 15) {
        myData.bx.ptr = new value_type[count + 1];
    }
    for (size_type i = 0; i < count; i++) {
        myData.myPtr()[i] = ch;
    }
    myData.myPtr()[count] = value_type();



}

string::string(const string& right)
    : myData()
{
    myData.mySize = right.myData.mySize;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.myRes > 15) {
        myData.bx.ptr = new value_type[myData.mySize + 1];

    }
    for (size_type i = 0; i < myData.mySize; i++) {
        myData.myPtr()[i] = right.myData.myPtr()[i];
    }
    myData.myPtr()[myData.mySize] = value_type();




}

string::~string()
{
    if (myData.myRes > 15)
        delete[] myData.bx.ptr;
}

string& string::operator=(const string& right)
{
    if (this != &right)
    {
        if (right.myData.mySize > myData.myRes)
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;

            myData.myRes = myData.myRes * 3 / 2;
            if (myData.myRes < (right.myData.mySize / 16) * 16 + 15)
                myData.myRes = (right.myData.mySize / 16) * 16 + 15;

            myData.bx.ptr = new value_type[myData.myRes + 1];
        }

        for (size_type i = 0; i < right.myData.mySize; i++) {
            myData.myPtr()[i] = right.begin()[i];
        }
        myData.mySize = right.myData.mySize;
        myData.myPtr()[myData.mySize] = value_type();

    }

    return *this;
}

string& string::operator=(const value_type* const ptr)
{
    size_t count = strlen(ptr);
    if (count > 0)
    {
        if (count > myData.myRes)
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;

            myData.myRes = myData.myRes * 3 / 2;
            if (myData.myRes < (count / 16) * 16 + 15)
                myData.myRes = (count / 16) * 16 + 15;

            myData.bx.ptr = new value_type[myData.myRes + 1];
        }
        for (size_type i = 0; i < count; i++) {
            myData.myPtr()[i] = ptr[i];
        }
        myData.mySize = count;
        myData.myPtr()[myData.mySize] = value_type();


    }



    return *this;
}

string& string::erase(size_t off, size_t count)
{
    if (off < myData.mySize)
    {
        if (off + count < myData.mySize)
        {
            for (size_type i = off; i + count < myData.mySize; ++i) {
                myData.myPtr()[i] = myData.myPtr()[i + count];
            }
            myData.mySize -= count;

        }
        else
            myData.mySize = off;

        myData.myPtr()[myData.mySize] = value_type();
    }

    return *this;
}

void string::clear()
{
    myData.mySize = 0;
    myData.myPtr()[0] = value_type();
}

string::iterator string::begin()
{
    return iterator(myData.myPtr());
}

string::const_iterator string::begin() const
{
    return const_iterator(myData.myPtr());
}

string::iterator string::end()
{
    return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::const_iterator string::end() const
{
    return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::reference string::operator[](size_type off)
{
    // check for off out-of-range error
    if (off > myData.mySize)
    {
        cout << "\nstring subscript out of range\n";
        system("pause");
        exit(1); // terminate program; off out of range
    }

    return myData.myPtr()[off]; // returns copy of this element
}

string::const_reference string::operator[](size_type off) const
{
    // check for off out-of-range error
    if (off > myData.mySize)
    {
        cout << "\nstring subscript out of range\n";
        system("pause");
        exit(1); // terminate program; off out of range
    }

    return myData.myPtr()[off]; // returns copy of this element
}

string::const_pointer string::data() const
{
    return myData.myPtr();
}

string::size_type string::size() const
{
    return myData.mySize;
}

string::size_type string::find(value_type ch, size_type off) const
{
    if (off < myData.mySize)
        for (size_t i = off; i < myData.mySize; i++)
            if (ch == myData.myPtr()[i])
                return i;

    return static_cast<size_t>(-1);
}

string string::substr(size_type off, size_type count) const
{
    if (off >= myData.mySize)
        return string();
    else
    {
        if (off + count > myData.mySize) {
            count = myData.mySize - off;
        }
        string str(count, '/0');
        int n = 0;
        for (size_t i = off; i < off + count; i++) {
            str.myData.myPtr()[n++] = myData.myPtr()[i];
        }

        return str;

    }
}

// compare [ 0, size() ) with right for equality
bool string::equal(const string& right) const
{
    if (myData.mySize != right.myData.mySize)
        return false;

    for (size_type i = 0; i < myData.mySize; i++)
        if (myData.myPtr()[i] != right.myData.myPtr()[i])
            return false;

    return true;
}

bool operator==(const string& left, const string& right)
{
    return left.equal(right);
    //   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=(const string& left, const string& right)
{
    return !left.equal(right);
}

ostream& operator<<(ostream& ostr, string& str)
{
    for (size_t i = 0; i < str.size(); i++)
        ostr << str.data()[i];

    return ostr; // enables cout << x << y;
}