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
	String concat(String str);
	static String copyValueOf(char* str);
	static String format(char* fmt, ...);
	int length();
	char *toCharArray();
	void print();
	void println();
	String substring(int begin);
	String substring(int begin, int end);
	String toUpperCase();
	
/*
 int 	compareToIgnoreCase(String str)
          Compares two strings lexicographically, ignoring case differences.
 boolean 	contentEquals(StringBuffer sb)
          Returns true if and only if this String represents the same sequence of characters as the specified StringBuffer.
static String 	copyValueOf(char[] data, int offset, int count)
          Returns a String that represents the character sequence in the array specified.
 boolean 	endsWith(String suffix)
          Tests if this string ends with the specified suffix.
 boolean 	equals(Object anObject)
          Compares this string to the specified object.
 boolean 	equalsIgnoreCase(String anotherString)
 byte[] 	getBytes()
 void 	getBytes(int srcBegin, int srcEnd, byte[] dst, int dstBegin)
          Deprecated. This method does not properly convert characters into bytes. As of JDK 1.1, the preferred way to do this is via the the getBytes() method, which uses the platform's default charset.
 byte[] 	getBytes(String charsetName)
          Encodes this String into a sequence of bytes using the named charset, storing the result into a new byte array.
 void 	getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin)
          Copies characters from this string into the destination character array.
 int 	hashCode()
          Returns a hash code for this string.
 int 	indexOf(int ch)
          Returns the index within this string of the first occurrence of the specified character.
 int 	indexOf(int ch, int fromIndex)
          Returns the index within this string of the first occurrence of the specified character, starting the search at the specified index.
 int 	indexOf(String str)
          Returns the index within this string of the first occurrence of the specified substring.
 int 	indexOf(String str, int fromIndex)
          Returns the index within this string of the first occurrence of the specified substring, starting at the specified index.
 String 	intern()
          Returns a canonical representation for the string object.
 int 	lastIndexOf(int ch)
          Returns the index within this string of the last occurrence of the specified character.
 int 	lastIndexOf(int ch, int fromIndex)
          Returns the index within this string of the last occurrence of the specified character, searching backward starting at the specified index.
 int 	lastIndexOf(String str)
          Returns the index within this string of the rightmost occurrence of the specified substring.
 int 	lastIndexOf(String str, int fromIndex)
          Returns the index within this string of the last occurrence of the specified substring, searching backward starting at the specified index.
 boolean 	matches(String regex)
          Tells whether or not this string matches the given regular expression.
 boolean 	regionMatches(boolean ignoreCase, int toffset, String other, int ooffset, int len)
          Tests if two string regions are equal.
 boolean 	regionMatches(int toffset, String other, int ooffset, int len)
          Tests if two string regions are equal.
 String 	replace(char oldChar, char newChar)
          Returns a new string resulting from replacing all occurrences of oldChar in this string with newChar.
 String 	replaceAll(String regex, String replacement)
          Replaces each substring of this string that matches the given regular expression with the given replacement.
 String 	replaceFirst(String regex, String replacement)
          Replaces the first substring of this string that matches the given regular expression with the given replacement.
 String[] 	split(String regex)
          Splits this string around matches of the given regular expression.
 String[] 	split(String regex, int limit)
          Splits this string around matches of the given regular expression.
 boolean 	startsWith(String prefix)
 boolean 	startsWith(String prefix, int toffset)
 CharSequence 	subSequence(int beginIndex, int endIndex)
 String 	toLowerCase()
          Converts all of the characters in this String to lower case using the rules of the default locale.
 String 	toLowerCase(Locale locale)
 String 	toUpperCase()
          Converts all of the characters in this String to upper case using the rules of the default locale.
 String 	toUpperCase(Locale locale)
 String 	trim()
          Returns a copy of the string, with leading and trailing whitespace omitted.*/

private :
	smart_ptr<char> data;
	int len;
};

#endif