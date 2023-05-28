#define _CRT_SECURE_NO_WARNINGS 1

#include <chrono>
#include <iostream>
#include <cstring>

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
    const int N = 1000000;

    // ��ʹ���ƶ����캯��������´�������
    auto start = std::chrono::steady_clock::now();
    MyString str1("Hello");
    for (int i = 0; i < N; ++i) {
        MyString temp(str1);
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "��ʹ���ƶ����� " << duration.count() << " milliseconds" << std::endl;

    // ʹ���ƶ����캯��������´�������
    start = std::chrono::steady_clock::now();
    MyString str2("Hello");
    for (int i = 0; i < N; ++i) {
        MyString temp(std::move(str2));
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "ʹ���ƶ����壺 " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

