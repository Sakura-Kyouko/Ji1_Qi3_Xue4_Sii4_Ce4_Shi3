#pragma once

#include <cstdlib>
#include <string>
#include <ctime>
#include <unordered_map>
#include <vector>

class 類別_資料表
{
public:
	std::vector<double*> 資料;
	unsigned __int64 欄數 = 0;

	virtual ~類別_資料表()
	{
		for (auto 甲 = 0; 甲 < 資料.size(); 甲++)
			delete[] 資料[甲];
	}

	static 類別_資料表* 閱讀資料(unsigned __int16* 丶檔案名, unsigned __int16* 丶分割字串 = L",", bool 有標題否 = true, unsigned __int16* 丶空字串 = L"NA")
	{
		_iobuf* 丶檔案 = 0;
		_wfopen_s(&丶檔案, 丶檔案名, L"r");

		auto 丶資料表 = new 類別_資料表();

		auto 丶字串 = new unsigned __int16[4096];
		if (-1 == fwscanf_s(丶檔案, L"%ws", 丶字串, 4096))
			goto 讀取結束;
				
		if (有標題否)
		{
			auto 丶字串甲 = 丶字串;
			for (auto 甲 = 0; ; 甲++)
			{			
				unsigned __int16* 丶字串乙;
				if (wcstok_s(丶字串甲, 丶分割字串, &丶字串乙) == 0)
					break;

				丶字串甲 = 丶字串乙;
				丶資料表->欄數++;
			}
		}
		else
		{
			std::vector<double> 資料向量;

			auto 丶字串甲 = 丶字串;
			for (auto 甲 = 0; ; 甲++)
			{
				unsigned __int16* 丶字串乙;
				if (wcstok_s(丶字串甲, 丶分割字串, &丶字串乙) == 0)
					break;

				資料向量.push_back(_wtof(丶字串甲));
				丶字串甲 = 丶字串乙;
				丶資料表->欄數++;
			}
			
			auto 資料陣列 = new double[丶資料表->欄數];
			for (auto 甲 = 0; 甲 < 丶資料表->欄數; 甲++)
				資料陣列[甲] = 資料向量[甲];
			丶資料表->資料.push_back(資料陣列);
		}

		for (auto 子 = 0; ; 子++)
		{
			if (-1 == fwscanf_s(丶檔案, L"%ws", 丶字串, 4096))
				goto 讀取結束;

			auto 資料陣列 = new double[丶資料表->欄數];

			auto 丶字串甲 = 丶字串;
			for (auto 甲 = 0; 甲 < 丶資料表->欄數; 甲++)
			{
				unsigned __int16* 丶字串乙;
				wcstok_s(丶字串甲, 丶分割字串, &丶字串乙);
				資料陣列[甲] = _wtof(丶字串甲);
				丶字串甲 = 丶字串乙;
			}

			丶資料表->資料.push_back(資料陣列);
		}

	讀取結束:
		delete[] 丶字串;
		fclose(丶檔案);
		return 丶資料表;
	}

	class 類別_資料表異常 : std::exception
	{
	public:
		類別_資料表異常(std::wstring 異常字串) : exception(std::string(異常字串.begin(), 異常字串.end()).c_str())
		{

		}
	};
};
