#include "FString.h"
#include <set>
#include <cassert>

namespace Str
{
	// map str, cnt
	std::set<std::string> Strings;

	FString::FString(const char* _Str)
		: Str(nullptr)
	{
		operator=(_Str);
	}
	FString::FString(const FString& _Other)
		: Str(nullptr)
	{
		operator=(_Other);
	}
	FString::FString(FString&& _Other) noexcept
		: Str(nullptr)
	{
		if (_Other.Str)
		{
			Str = _Other.Str;
			_Other.Reset();
		}
	}
	FString& FString::operator=(const char* _Str)
	{
		if (_Str == nullptr)
			assert(0);
		
		auto iter = Strings.find(_Str);
		if (iter == Strings.end())
		{
			auto i = Strings.insert(_Str);
			auto it = i.first;
			Str = &(*it);
		}
		else
		{
			Str = &(*iter);
		}
		return *this;
	}
	FString& FString::operator=(const FString& _Other)
	{
		if (_Other.Str)
		{
			Str = _Other.Str;
		}
		return *this;
	}

	FString& FString::operator=(FString&& _Other) noexcept
	{
		if (_Other.Str)
		{
			Str = _Other.Str;
			_Other.Reset();
		}
		return *this;
	}

	FString::~FString()
	{
	}

	FString& FString::operator+=(const FString& _Other)
	{
		operator = ((*Str + *_Other.Str).c_str());
		return *this;
	}

	char FString::operator[](size_t index) const
	{
		return (*Str)[index];
	}

	void FString::Reset()
	{
		auto iter = Strings.find("");
		if (iter == Strings.end())
		{
			auto i = Strings.insert("");
			auto it = i.first;
			Str = &(*it);
		}
		else
		{
			Str = &(*iter);
		}
	}

	bool operator<(const FString& _Str1, const FString& _Str2)
	{
		return *_Str1.Str < *_Str2.Str;
	}

	bool operator>(const FString& _Str1, const FString& _Str2)
	{
		return *_Str1.Str > *_Str2.Str;
	}

	bool operator==(const FString& _Str1, const FString& _Str2)
	{
		return _Str1.Str == _Str2.Str;
	}

	bool operator!=(const FString& _Str1, const FString& _Str2)
	{
		return _Str1.Str != _Str2.Str;
	}

	FString operator+(const FString& _Str1, const FString& _Str2)
	{
		std::string NewStr = *_Str1.Str + *_Str2.Str;
		return FString(NewStr.c_str());
	}


	std::ostream& operator<<(std::ostream& os, const FString& str)
	{
		os << *str.Str;
		return os;
	}
}