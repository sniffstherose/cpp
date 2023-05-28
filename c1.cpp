#define _CRT_SECURE_NO_WARNINGS 1

#include <chrono>
#include <iostream>
#include <cstring>

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

    // 重载+=操作符
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
    const int N = 1000000;

    // 不使用移动构造函数的情况下创建对象
    auto start = std::chrono::steady_clock::now();
    MyString str1("Hello");
    for (int i = 0; i < N; ++i) {
        MyString temp(str1);
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "不使用移动语义 " << duration.count() << " milliseconds" << std::endl;

    // 使用移动构造函数的情况下创建对象
    start = std::chrono::steady_clock::now();
    MyString str2("Hello");
    for (int i = 0; i < N; ++i) {
        MyString temp(std::move(str2));
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "使用移动语义： " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

