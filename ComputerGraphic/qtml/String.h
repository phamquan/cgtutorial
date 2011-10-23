#if !defined(_String_h_)
#define _String_h_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "smart_ptr.h"

class String {
public :
	String();
	String(const char *str);
	String(const char *str, int tab);
	String(const String &str);
	~String();
public:
	String& operator = (char *str);
	String& operator = (const String &str);
	String operator + (const char *str);
	String operator + (const String &str);
	void operator += (const char str);
	void operator += (const char *str);
	void operator += (const String &str);
	char operator [] (int index);
public:
	char charAt(int index);
	int compareTo(String str);
	int compareTo(const char *str);
	int compareToIgnoreCase(String str);
	String concat(String str);
	//boolean contentEquals(StringBuffer sb)
	static String copyValueOf(char *str);
	static String copyValueOf(char *data, int offset, int count);
	bool endsWith(String suffix);
	bool equals(String str);
	bool equalsIgnoreCase(String str);
	static String format(char *fmt, ...);
	//byte[] getBytes();
	//void getBytes(int srcBegin, int srcEnd, byte[] dst, int dstBegin)
	//byte[] getBytes(String charsetName)
	void getChars(int srcBegin, int srcEnd, char *dst, int dstBegin);
	//int hashCode();
	int indexOf(int ch);
	int indexOf(int ch, int fromIndex);
	//int indexOf(String str)
	//int indexOf(String str, int fromIndex)
	//String intern()
	//int lastIndexOf(int ch)
	//int lastIndexOf(int ch, int fromIndex)
	//int lastIndexOf(String str)
	//int lastIndexOf(String str, int fromIndex)
	int length();
	//boolean matches(String regex)
	//boolean regionMatches(boolean ignoreCase, int toffset, String other, int ooffset, int len)
	//boolean regionMatches(int toffset, String other, int ooffset, int len)
	//String replace(char oldChar, char newChar)
	//String replaceAll(String regex, String replacement)
	//String replaceFirst(String regex, String replacement)
	//String[] split(String regex)
	//String[] split(String regex, int limit)
	//boolean startsWith(String prefix)
	//boolean startsWith(String prefix, int toffset)
	//CharSequence subSequence(int beginIndex, int endIndex)
	String substring(int begin);
	String substring(int begin, int end);
	char *toCharArray();
	//String toLowerCase()
	//String toLowerCase(Locale locale)
	String toUpperCase();
	//String toUpperCase(Locale locale)
	//String trim()
	static String valueOf(bool b);
	static String valueOf(char c);
	static String valueOf(char* data);
	//static String valueOf(char[] data, int offset, int count);
	static String valueOf(double d);
	static String valueOf(int i);
	static String valueOf(long l);
	//static String valueOf(Object obj);
	void print();
	void println();
	
private :
	smart_ptr<char> data;
	int len;
};

#endif