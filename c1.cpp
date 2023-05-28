#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstring>

class MyString {
public:
	// 默认构造函数
	MyString() : data(nullptr), length(0) {}

	// 构造函数，接受C风格字符串作为参数
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

	// 重载赋值操作符
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
		char* temp = new char[length + other.length + 1];
		std::strcpy(temp, data);
		std::strcat(temp, other.data);
		delete[] data;
		data = temp;
		length += other.length;
		return *this;
	}

	// 重载+操作符
	MyString operator+(const MyString& other) const {
		MyString result(*this);
		result += other;
		return result;
	}

	// 重载<<操作符
	friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
		os << str.data;
		return os;
	}

	// 重载[]操作符
	char& operator[](int index) {
		return data[index];
	}

private:
	char* data;
	size_t length;
};

int main() {
	// 创建一个MyString对象，并输出
	MyString str1("Hello");
	std::cout << "str1: " << str1 << std::endl;

	// 使用拷贝构造函数创建一个新的MyString对象
	MyString str2(str1);
	std::cout << "str2: " << str2 << std::endl;

	// 使用移动构造函数创建一个新的MyString对象
	MyString str3(std::move(str1));
	std::cout << "str3: " << str3 << std::endl;

	// 使用赋值操作符进行赋值，并输出结果
	str2 = str3;
	std::cout << "str2 after assignment: " << str2 << std::endl;

	// 使用+=操作符进行字符串连接，并输出结果
	str2 += " World";
	std::cout << "str2 after +=: " << str2 << std::endl;

	// 使用+操作符进行字符串连接，并输出结果
	MyString str4 = str2 + "!";
	std::cout << "str4: " << str4 << std::endl;

	// 修改特定索引位置的字符，并输出结果
	str4[0] = 'G';
	std::cout << "str4 after modification: " << str4 << std::endl;

	//验证移动语义的效率提升
		// 创建两个MyString对象
	MyString str1("Hello");
	MyString str2("World");

	// 测试赋值操作符（使用深拷贝）
	MyString str3 = str1;
	std::cout << "str3: " << str3 << std::endl;

	// 测试移动构造函数
	MyString str4 = std::move(str2);
	std::cout << "str4: " << str4 << std::endl;

	// 测试+=操作符
	str3 += str4;
	std::cout << "str3 after +=: " << str3 << std::endl;

	// 测试+操作符
	MyString str5 = str1 + str4;
	std::cout << "str5: " << str5 << std::endl;


	return 0;
}

