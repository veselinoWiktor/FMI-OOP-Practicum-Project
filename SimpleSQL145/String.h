#pragma once
#include <fstream>

class String
{
private:
	char* data;
	size_t length;
	size_t capacity;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);

	void resize(size_t newCapacity);

	explicit String(size_t size);
public:
	String();
	String(const char* str);
	String(const String& other);
	String(char ch, size_t length);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	size_t getLength() const;
	const char* c_str() const;

	String substr(size_t begin, size_t length) const;

	String& operator+=(const String& other);
	String& operator+=(char ch);

	char& operator[](size_t idx);
	const char& operator[](size_t idx) const;

	friend std::ostream& operator<<(std::ostream& os, const String& obj);
	friend std::istream& operator>>(std::istream& is, String& obj);
	friend String operator+(const String& lhs, const String& rhs);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);