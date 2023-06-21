#define _CRT_SECURE_NO_WARNINGS 1
#include <cstring>
#include <iostream>

class MyString {
private:
    char* data;
    size_t length;

public:
    // 默认构造函数
    MyString() : data(nullptr), length(0) {}

    // 带参构造函数
    MyString(const char* str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    // 移动构造函数
    MyString(MyString&& other) noexcept {
        length = other.length;
        data = other.data;
        other.length = 0;
        other.data = nullptr;
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // 重载赋值操作符=
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    // 重载操作符
    MyString& operator+=(const MyString& other) {
        size_t newLength = length + other.length;
        char* newData = new char[newLength + 1];
        std::strcpy(newData, data);
        std::strcat(newData, other.data);
        delete[] data;
        data = newData;
        length = newLength;
        return *this;
    }

    // 重载+操作符
    MyString operator+(const MyString& other) const {
        MyString result(*this);
        result += other;
        return result;
    }

    // 重载<<操作符，用于输出到流
    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        os << str.data;
        return os;
    }

    // 重载[]操作符，用于修改指定位置的字符
    char& operator[](size_t index) {
        return data[index];
    }

    // 获取字符串长度
    size_t getLength() const {
        return length;
    }

    // 获取字符串内容
    const char* getData() const {
        return data;
    }
};

int main() {
    // 测试构造函数和输出运算符重载
    MyString a("test");
    std::cout << a << std::endl;  // 输出：test

    // 测试赋值运算符重载和连接运算符重载
    MyString b(" Hello");
    a += b;
    std::cout << a << std::endl;  // 输出：test Hello

    MyString c = a + b;
    std::cout << c << std::endl;  // 输出：test Hello Hello

    // 测试修改字符和索引运算符重载
    a[2] = 'S';
    std::cout << a << std::endl;  // 输出：teSt

    // 测试移动构造函数和长度获取函数
    MyString d = std::move(a);
    std::cout << d << std::endl;  // 输出：teSt
    std::cout << "Length of d: " << d.getLength() << std::endl;  // 输出：Length of d: 4

    std::cout << "Length of a: " << a.getLength() << std::endl;  // 输出：Length of a: 0

    return 0;
}
