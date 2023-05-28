#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstring>

class MyString {
public:
	// Ĭ�Ϲ��캯��
	MyString() : data(nullptr), length(0) {}

	// ���캯��������C����ַ�����Ϊ����
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

	// ���ظ�ֵ������
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
		char* temp = new char[length + other.length + 1];
		std::strcpy(temp, data);
		std::strcat(temp, other.data);
		delete[] data;
		data = temp;
		length += other.length;
		return *this;
	}

	// ����+������
	MyString operator+(const MyString& other) const {
		MyString result(*this);
		result += other;
		return result;
	}

	// ����<<������
	friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
		os << str.data;
		return os;
	}

	// ����[]������
	char& operator[](int index) {
		return data[index];
	}

private:
	char* data;
	size_t length;
};

int main() {
	// ����һ��MyString���󣬲����
	MyString str1("Hello");
	std::cout << "str1: " << str1 << std::endl;

	// ʹ�ÿ������캯������һ���µ�MyString����
	MyString str2(str1);
	std::cout << "str2: " << str2 << std::endl;

	// ʹ���ƶ����캯������һ���µ�MyString����
	MyString str3(std::move(str1));
	std::cout << "str3: " << str3 << std::endl;

	// ʹ�ø�ֵ���������и�ֵ����������
	str2 = str3;
	std::cout << "str2 after assignment: " << str2 << std::endl;

	// ʹ��+=�����������ַ������ӣ���������
	str2 += " World";
	std::cout << "str2 after +=: " << str2 << std::endl;

	// ʹ��+�����������ַ������ӣ���������
	MyString str4 = str2 + "!";
	std::cout << "str4: " << str4 << std::endl;

	// �޸��ض�����λ�õ��ַ�����������
	str4[0] = 'G';
	std::cout << "str4 after modification: " << str4 << std::endl;

	//��֤�ƶ������Ч������
		// ��������MyString����
	MyString str1("Hello");
	MyString str2("World");

	// ���Ը�ֵ��������ʹ�������
	MyString str3 = str1;
	std::cout << "str3: " << str3 << std::endl;

	// �����ƶ����캯��
	MyString str4 = std::move(str2);
	std::cout << "str4: " << str4 << std::endl;

	// ����+=������
	str3 += str4;
	std::cout << "str3 after +=: " << str3 << std::endl;

	// ����+������
	MyString str5 = str1 + str4;
	std::cout << "str5: " << str5 << std::endl;


	return 0;
}

