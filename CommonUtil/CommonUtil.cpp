#include "pch.h"

#include "CommonUtil.h"

#include <sstream>
#include <string>
#include <iomanip>
#include <numeric>
#include <chrono>

using namespace std;
using namespace chrono;

string algorithm::utf8StrToAsciiStr(const char* utf8Str)
{
	wstring unicodeStr = utf8StrToUnicodeStr(utf8Str);
	int strLen = ::WideCharToMultiByte(CP_ACP, 0, unicodeStr.c_str(), unicodeStr.size(), NULL, 0, NULL, NULL);
	char* str = new char[strLen + 1];
	::WideCharToMultiByte(CP_ACP, 0, unicodeStr.c_str(), unicodeStr.size(), str, (int)strlen(str), NULL, NULL);
	string asciiStr(str);
	// 删除分配的存储空间
	delete[] str;
	// 将指针所指向地址置为空
	str = nullptr;
	// 返回编码后的字符串
	return asciiStr;
}

std::wstring algorithm::utf8StrToUnicodeStr(const char * utf8Str)
{
	// 预转换，计算所需空间的大小;
	int wstrLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8Str, (int)strlen(utf8Str), NULL, 0);
	// 动态分配字符串存储空间，需要将计算得到的空间大小加1，用于存储 ‘\0’
	wchar_t* wstr = new wchar_t[wstrLen + 1];
	// 转换字符串编码
	::MultiByteToWideChar(CP_UTF8, NULL, utf8Str, (int)strlen(utf8Str), wstr, wstrLen);
	// 添加字符串结束符
	wstr[wstrLen] = '\0';
	// 获取编码后的字符串
	wstring unicodeStr(wstr);
	// 删除分配的存储空间
	delete[] wstr;
	// 将指针所指向地址置为空
	wstr = nullptr;
	return unicodeStr;
}

std::string algorithm::getNowDateStr()
{
	auto time = system_clock::to_time_t(system_clock::now());

	//转为字符串
	stringstream stream;
	string timeStr;
	stream << put_time(localtime(&time), "%Y-%m-%d");
	stream >> timeStr;

	return timeStr;
}

string algorithm::getNowTimeStr()
{
	auto time = system_clock::to_time_t(system_clock::now());

	//转为字符串
	stringstream stream;
	string timeStr;
	stream << put_time(localtime(&time), "%Y-%m-%d-%H:%M:%S");
	stream >> timeStr;

	return timeStr;
}

string algorithm::parseDateTimeToString(const int& date, const int& time)
{
	return parseDateToString(date) + "-" + parseTimeToString(time);
}

std::string algorithm::parseDateToString(const int & date)
{
	stringstream sstream;
	string dateStr;

	// 写入时间
	sstream << date;
	sstream >> dateStr;
	sstream.clear();

	sstream << dateStr.substr(0, 4) << "-";
	sstream << dateStr.substr(4, 2) << "-";
	sstream << dateStr.substr(6, 2);
	
	dateStr.clear();
	sstream >> dateStr;
	sstream.clear();

	return dateStr;
}

string algorithm::parseTimeToString(const int& time)
{
	stringstream sstream;
	string timeStr;

	sstream << time;
	sstream >> timeStr;
	sstream.clear();

	// 判断小时部分是否为两位数，如10点则为10，9点则为9
	if (timeStr.size() == 9) {
		// 获取小时部分
		sstream << timeStr.substr(0, 2) << ":";
		// 获取分钟部分
		sstream << timeStr.substr(2, 2) << ":";
		// 获取秒部分
		sstream << timeStr.substr(4, 2) << ":";
		// 获取秒部分
		sstream << timeStr.substr(6, 3);
	}
	else {
		sstream << timeStr.substr(0, 1) << ":";
		sstream << timeStr.substr(1, 2) << ":";
		sstream << timeStr.substr(3, 2) << ":";
		sstream << timeStr.substr(5, 3);
	}

	timeStr.clear();
	sstream >> timeStr;
	sstream.clear();

	return timeStr;
}

int algorithm::subTime(int time, int seconds)
{
	// 减去当前时间的毫秒值
	time -= time % 1000;
	// 将要减去的描述转换为毫秒单位
	seconds *= 1000;

	// 计算当前时间的分钟值部分
	int minute = time / 100000 % 100;
	// 判断是否为整点
	if (minute == 0) {
		// 减去59分钟的值
		return time - (40 + 1) * 100000;
	}
	// 减去一分钟的值
	return time - 100000;
}

string algorithm::getRelativePath(const string & filePath)
{
	size_t splitPos = filePath.find_last_of('\\');
	return filePath.substr(splitPos + 1);
}

double algorithm::percentageConvert(const double & percentage)
{
	return percentage / 100;
}