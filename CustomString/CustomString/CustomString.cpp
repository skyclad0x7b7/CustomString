#include "CustomString.h"

// Constructor

CustomString::CustomString(TCHAR *str) : myString(nullptr), length(0) {
	if (str == nullptr) return;

	if (this->length != 0) {
		free(this->myString);
	}

	this->length = _tcslen(str);
	this->myString = (char *)malloc((this->length + 1) * sizeof(TCHAR));
	_tcsncpy(this->myString, str, this->length + 1);
}

CustomString::CustomString(CustomString& cs) : myString(nullptr), length(0)	{
	// Self Pointer Check
	// newCS.length Check
	if (&cs == this) return;
	if (cs.getLength() == 0) return;

	if (this->length){	// Initialize
		free(this->myString);
	}
	
	// Memory allocation & copy string
	this->myString = (TCHAR *)malloc((cs.getLength() + 1) * sizeof(TCHAR));	
	_tcsncpy(this->myString, cs.getValue(), cs.getLength() + 1);
	this->length = cs.getLength();
}

// Destructor

CustomString::~CustomString() {
	if (this->length != 0) {
		free(this->myString);
	}
}

// Operator overloading

CustomString& CustomString::operator= (TCHAR *str) {
	if (str == nullptr) return *this;
	if (this->length) {
		free(this->myString);
		this->length = 0;
	}

	int newLength = _tcslen(str);
	this->myString = (TCHAR *)malloc((newLength + 1) * sizeof(TCHAR));
	_tcscpy(this->myString, str);
	this->length = newLength;
	return *this;
}

CustomString& CustomString::operator= (CustomString& cs) {
	// Null Check
	// Length Check
	if (cs.getLength() == 0) return *this;

	if (this->length) {
		free(this->myString);
		this->length = 0;
	}

	this->myString = (TCHAR *)malloc((cs.getLength() + 1) * sizeof(TCHAR));
	_tcsncpy(this->myString, cs.getValue(), cs.getLength() + 1);
	this->length = cs.getLength();

	return *this;
}

CustomString CustomString::operator+ (TCHAR *str) {
	if (str == nullptr) return *this;
	CustomString ret(*this);
	return ret+=str;	
}

CustomString CustomString::operator+ (CustomString& cs) {
	// Null Pointer Check
	// Self Pointer Check
	// Length Check
	if (cs.getLength() == 0) return *this;
	TCHAR *newString = (TCHAR *)malloc((this->length + cs.getLength() + 1) * sizeof(TCHAR));
	_tcscpy(newString, this->myString);
	_tcscat(newString, cs.getValue());
	CustomString ret(newString);
	free(newString);

	return ret;
}

CustomString& CustomString::operator+=(TCHAR *str) {
	if (str == nullptr) return *this;
	unsigned int strLength = this->length + _tcslen(str);
	TCHAR *newString = (TCHAR *)malloc((strLength + 1) * sizeof(TCHAR));
	if (this->length) {
		_tcscpy(newString, this->myString);
		free(this->myString);
		this->length = 0;
	}

	this->myString = (TCHAR *)malloc((strLength + 1) * sizeof(TCHAR));
	_tcscpy(this->myString, newString);
	_tcscat(this->myString, str);
	this->length = strLength;
	
	return *this;
}

CustomString& CustomString::operator+=(CustomString& cs) {
	if (&cs == this || &cs == nullptr) return *this;

	unsigned int strLength = this->length + cs.getLength();
	TCHAR *newString = (TCHAR *)malloc((strLength + 1) * sizeof(TCHAR));
	if (this->length) {
		_tcscpy(newString, this->myString);
		free(this->myString);
		this->length = 0;
	}

	this->myString = (TCHAR *)malloc((strLength + 1) * sizeof(TCHAR));
	_tcscpy(this->myString, newString);
	_tcscat(this->myString, cs.getValue());
	this->length = strLength;

	return *this;
}

bool CustomString::operator==(TCHAR *str) {
	if (str == nullptr) return false;
	unsigned int strLength = _tcslen(str);
	
	if (this->length != strLength) return false;
	else if (this->length == 0) return true;

	if (!_tcscmp(this->myString, str)) return true;
	else return false;
}

bool CustomString::operator==(CustomString& cs) {
	if (&cs == this) return true;
	if (&cs == nullptr) return false;

	return *this == cs.getValue();
}

bool CustomString::operator!=(TCHAR *str) {
	return !(*this == str);
}

bool CustomString::operator!=(CustomString& cs) {
	return !(*this == cs);
}

bool CustomString::operator>(TCHAR *str) {
	if (str == nullptr) return false;
	int res = _tcscmp(this->myString, str);
	if (res > 0) return true;
	else return false;
}

bool CustomString::operator>(CustomString& cs) {
	if (cs == nullptr || &cs == this) return false;
	return *this > cs.getValue();
}

bool CustomString::operator<(TCHAR *str) {
	if (str == nullptr) return false;
	int res = _tcscmp(str, this->myString);
	if (res > 0) return true;
	else return false;
}

bool CustomString::operator<(CustomString& cs) {
	if (cs == nullptr || &cs == this) return false;
	return *this < cs.getValue();
}

bool CustomString::operator<=(TCHAR *str) {
	return (*this == str || *this < str);
}

bool CustomString::operator<=(CustomString& cs) {
	return (*this == cs || *this < cs);
}

bool CustomString::operator>=(TCHAR *str) {
	return (*this == str || *this > str);
}

bool CustomString::operator>=(CustomString& cs) {
	return (*this == cs || *this > cs);
}


// Getter

TCHAR *CustomString::getValue() {
	if (this->length == 0) exit(1);
	return this->myString;
}

unsigned int CustomString::getLength() {
	return this->length;
}

void CustomString::setLength(unsigned int newLength) {
	this->length = newLength;
}