#define _CRT_SECURE_NO_WARNINGS 1
#include <cstring>
#include <iostream>

class MyString {
private:
    char* data;
    size_t length;

public:
    // Ĭ�Ϲ��캯��
    MyString() : data(nullptr), length(0) {}

    // ���ι��캯��
    MyString(const char* str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    // �������캯��
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    // �ƶ����캯��
    MyString(MyString&& other) noexcept {
        length = other.length;
        data = other.data;
        other.length = 0;
        other.data = nullptr;
    }

    // ��������
    ~MyString() {
        delete[] data;
    }

    // ���ظ�ֵ������=
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    // ����+=������
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

    // ����+������
    MyString operator+(const MyString& other) const {
        MyString result(*this);
        result += other;
        return result;
    }

    // ����<<�������������������
    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        os << str.data;
        return os;
    }

    // ����[]�������������޸�ָ��λ�õ��ַ�
    char& operator[](size_t index) {
        return data[index];
    }

    // ��ȡ�ַ�������
    size_t getLength() const {
        return length;
    }

    // ��ȡ�ַ�������
    const char* getData() const {
        return data;
    }
};

int main() {
    // ���Թ��캯����������������
    MyString a("test");
    std::cout << a << std::endl;  // �����test

    // ���Ը�ֵ��������غ��������������
    MyString b(" Hello");
    a += b;
    std::cout << a << std::endl;  // �����test Hello

    MyString c = a + b;
    std::cout << c << std::endl;  // �����test Hello Hello

    // �����޸��ַ����������������
    a[2] = 'S';
    std::cout << a << std::endl;  // �����teSt

    // �����ƶ����캯���ͳ��Ȼ�ȡ����
    MyString d = std::move(a);
    std::cout << d << std::endl;  // �����teSt
    std::cout << "Length of d: " << d.getLength() << std::endl;  // �����Length of d: 4

    std::cout << "Length of a: " << a.getLength() << std::endl;  // �����Length of a: 0

    return 0;
}
