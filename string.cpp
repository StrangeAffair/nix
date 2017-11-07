#include <iostream>
#include <cstring>
#include <cstdio>

#include <string>

/*
unsigned int strlen(const char* s){
    unsigned int len = 0;
    while(*s) {++s; ++len;}
    return len;
}


void strcopy(char* dest, const char* src){
    while(*src) {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = *src;
}
*/

#define strcopy strcpy

class S{
    size_t _length_;
    char* _string_;
    S(size_t length);
public:
    S();
    S(char c);
    S(const char* s);
    S(const S& another);
    ~S() {delete[] _string_;}

    size_t length() const {return strlen(_string_);}
    const char*  str()    const {return _string_;}

    char&       operator[](unsigned int index)       {return *(_string_ + index);}
    const char& operator[](unsigned int index) const {return *(_string_ + index);}

    friend S operator+(const S& left, const S& right);
    const S& operator+=(const S& right);
    const S& operator=(const S& another);
    friend std::ostream& operator<<(std::ostream& out, const S& str){
        out << str._string_;
        return out;
    }
};

S::S():
    _length_(0), _string_(nullptr)
{}

S::S(unsigned int length):
    _length_(length),
    _string_(new (std::nothrow) char[_length_ + 1])
{*_string_ = '\0';}

S::S(char ch):
    _length_(1),
    _string_(new (std::nothrow) char[_length_ + 1])
{*_string_ = ch; *(_string_ + 1) = '\0';}

S::S(const char* s){
    if (s == nullptr) {
        _length_ = 0;
        _string_ = nullptr;
    }
    else {
        _length_ = strlen(s);
        _string_ = new (std::nothrow) char[_length_ + 1];
        strcopy(_string_, s);
    }
}

S::S(const S& another){
    if (another._string_ == nullptr){
        _length_ = 0;
        _string_ = nullptr;
    }
    else {
        //_length_ = another._length_;
        _length_ = strlen(another._string_);
        _string_ = new (std::nothrow) char[_length_ + 1];
        strcopy(_string_, another._string_);
    }
}

const S& S::operator=(const S& another){
    if (this == &another) return *this;
    delete[] _string_;
    if (another._string_ == nullptr) {
        _length_ = 0;
        _string_ = nullptr;
    }
    else{
        //_length_ = another._length_;
        _length_ = strlen(another._string_);
        _string_ = new (std::nothrow) char[_length_ + 1];
        strcopy(_string_, another._string_);
    }
    return *this;
}

const S& S::operator+=(const S& another){
    if (another._string_ == nullptr) return *this;
    return *this = *this + another;
}

S operator+(const S& left, const S& right){
    if ( left._string_ == nullptr) return S(right);
    if (right._string_ == nullptr) return S(left);
    S result(left._length_ + right._length_);
    //S result(strlen(left._string_) + strlen(right._string_));
    strcopy(result._string_, left._string_);
    strcat (result._string_, right._string_);
    return result;
}

/*
int main(){
    S s("abc");
    std::cout << (s += (s = s =s)) << std::endl;
}
*/
