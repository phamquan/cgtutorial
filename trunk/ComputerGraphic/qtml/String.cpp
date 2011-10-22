#if !defined(_String_cpp_)
#define _String_cpp_

#include "String.h"

String::String() {
	len = 0;
	char *tmp = new char[1];
	tmp[0] = '\0';
	data = smart_ptr<char>(tmp);
}

String::String(const char *str) {
	len = strlen(str);

	char *tmp = new char[len+1];
	strcpy(tmp,str);

	data = smart_ptr<char>(tmp);
}

String::String(const char *str, int tab) {
	len = strlen(str)+tab;
	
	char *tmp = new char[len+1];

	for(int i=0; i<tab; i++)
		tmp[i]='\t';
	tmp[i]='\0';

	strcat(tmp,str);

	data = smart_ptr<char>(tmp);
}

String::String(const String &str) {
	String::operator =(str);
}

String::~String() {}

String& String::operator = (char *str) {
	len=strlen(str);
	char *tmp = new char[len+1];
	strcpy(tmp,str);

	data = smart_ptr<char>(tmp);
	return *this;
}

String& String::operator = (const String &str) {
	len=strlen(str.data.get());
	data = str.data;

	return *this;	;
}

String String::operator + (const char *str) {
	String result(data.get());
	result += str;
	return result;
}

String String::operator + (const String &str) {
	return String::operator +(str.data.get());
}

void String::operator += (const char str) {
	len+=1;
	char *tmp = new char[len+1];

	strcpy(tmp,data.get());
	tmp[len-1] = str;
	tmp[len] = '\0';

	String::operator =(tmp);
}

void String::operator += (const char *str) {
	len+=strlen(str);
	char *tmp = new char[len+1];

	strcpy(tmp,data.get());
	strcat(tmp,str);
	
	String::operator =(tmp);
}

void String::operator += (const String &str) {
	String::operator +=(str.data.get());
}

char String::operator [](int index) {
	assert(index>=0 && index<len);
	return (data.get())[index];
}

/**
 *  Method
 */
char String::charAt(int index) {
	return String::operator [](index);
}

int String::compareTo(String str) {
	if(len != str.len)
		return len - str.len;

	for(int i=0; i<len; i++) {
		if(charAt(i) != str.charAt(i))
			return charAt(i)-str.charAt(i);
	}
	return 0;
}

String String::concat(String str) {
	return String(*this)+str;
}

String String::copyValueOf(char *str) {
	int len1 = strlen(str);
	char *tmp = new char[len1+1];
	strcpy(tmp,str);

	return String(tmp);
}


String String::format(char *fmt, ...) {
	char buff[1024];

	va_list ap;
	va_start(ap, fmt);
	vsprintf(buff, fmt, ap);
	va_end(ap);

	return String(buff);
}

int String::length() {
	return len;
}

char *String::toCharArray() {
	char *tmp = new char[len + 1];
	strcpy(tmp,data.get());
	return tmp;
}

void String::print() {
	printf("%s %d",data.get(),len);
}

void String::println() {
	print();
	printf("\n");
}

String String::substring(int begin) {
	assert(begin>=0 && begin<len);

	char *tmp = new char[len-begin+1];
	for(int i=begin; i<len; i++) {
		tmp[i-begin] = (data.get())[i];
	}
	tmp[i-begin] = '\0';

	return String(tmp);
}

String String::substring(int begin, int end) {
	//assert(begin >= 0 && end >= begin && end < len);
	if(begin < 0 || begin > end || end > len){
		printf("Unbond String start %d end %d len %d\n",begin,end,len);
		println();
	}
	char *tmp = new char[end-begin+1];
	for(int i=begin; i<end; i++) {
		tmp[i-begin] = (data.get())[i];
	}
	tmp[i-begin] = '\0';

	return String(tmp);
}

String String::toUpperCase() {
	char *tmp = new char[len+1];
	for (int i=0; i<=len; i++) {
		char t = (data.get())[i];
		tmp[i] = (t>96 && t<123)?t-32:t;
	}
	return String(tmp);
}

#endif