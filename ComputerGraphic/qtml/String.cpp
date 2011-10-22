#if !defined(_String_cpp_)
#define _String_cpp_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"
//#include "Exception.h"

/**
 *  Default String constructor
 */
String::String() {
	data = NULL;
	len=0;
}
/**
 *  Initialization String constructor
 */
String::String(const char *str) {
	data = NULL;
	len = 0;
	String::operator =(str);
}

String::String(const String &str) {
	data = NULL;
	len = 0;
	String::operator =(str.data);
}

String::~String() {
	if(data!=NULL)
		delete []data;
	data = NULL;
	len = 0;
}

/**
 *  Overload Operator
 */
String& String::operator = (const char *str) {
	if(str == NULL)
		return *this;

	if(data != NULL)
		delete data;

	len=strlen(str);
	data = new char[len+1];
	strcpy(data,str);

	return *this;
}

String& String::operator = (const String &str) {
	return String::operator =(str.data);
}

String String::operator + (const char *str) {
	String result(data);
	result += str;
	return result;
}

String String::operator + (const String &str) {
	return String::operator +(str.data);
}

void String::operator += (const char str) {
	len+=1;
	char *tmp = new char[len+1];

	if(data == NULL)
		tmp[len-1] = str;
	else {
		strcpy(tmp,data);
		tmp[len-1] = str;
		delete data;
	}
	tmp[len] = '\0';
	data = tmp;
}

void String::operator += (const char *str) {
	if(str == NULL)
		return;

	len+=strlen(str);
	char *tmp = new char[len+1];
	
	if(data == NULL)
		strcpy(tmp,str);
	else {
		strcpy(tmp,data);
		strcat(tmp,str);
		delete data;
	}
	data = tmp;
}

void String::operator += (const String &str) {
	String::operator +=(str.data);
}

/**
 *  Method
 */
char String::charAt(int index) {
	//assert(index>=0 && index<len);
	if(index < 0 || index >= len) {
		printf("Unbond String\n");
		println();
	}
	return data[index];
}

int String::length() {
	return len;
}

char *String::toCharArray() {
	if(data == NULL)
		return NULL;

	char *tmp = new char[len + 1];
	strcpy(tmp,data);
	return tmp;
}

void String::print() {
	if(data==NULL) return;
	printf("%s",data);
}

void String::println() {
	if(data==NULL) return;
	print();
	printf("\n");
}

String String::substring(int begin) {
	//assert(begin>=0 && begin<len);

	if(begin < 0 || begin > len) {
		printf("Unbond String start %d\n",begin);
		println();
	}

	char *tmp = new char[len-begin+1];
	int i;
	for(i=begin; i<len; i++) {
		tmp[i-begin] = data[i];
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
	int i;
	for(i=begin; i<end; i++) {
		tmp[i-begin] = data[i];
	}
	tmp[i-begin] = '\0';

	return String(tmp);
}

#endif