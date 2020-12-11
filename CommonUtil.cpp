#include "pch.h"

#include "CommonUtil.h"

#include <sstream>
#include <string>
#include <iomanip>
#include <numeric>
#include <chrono>
#include <codecvt>

using namespace std;
using namespace chrono;

string algorithm::utf8StrToAsciiStr(const char* utf8Str)
{
	size_t i;
	locale::global(locale("chs"));
	wstring wstr(L"你好");
	const wchar_t* _source = wstr.c_str();
	size_t _dsize = 2 * wstr.size() + 1;
	char* _dest = new char[_dsize];
	memset(_dest, 0x0, _dsize);
	wcstombs_s(&i, _dest, _dsize, _source, _dsize);
	string result = _dest;
	delete[] _dest;
	return asciiStr;
}

std::wstring algorithm::utf8StrToUnicodeStr(const char * utf8Str)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
	return utf16conv.from_bytes(utf8Str);
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