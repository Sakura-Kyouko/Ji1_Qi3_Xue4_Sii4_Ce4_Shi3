#pragma once

#include <algorithm>
#include <vector>

class 類別_評價
{
public:
	static double 計算比較準確率(std::vector<double>* 丶預測, std::vector<double>* 丶參照)
	{
		if (丶預測->size() != 丶參照->size())
			throw 類別_評價異常(L"計算排序準確率時出現異常：清單長度不一致！");

		auto 丶丶預測參照 = new 類別_預測參照*[丶預測->size()];
		auto 負樣本數 = 0, 正樣本數 = 0;
		for (auto 甲 = 0; 甲 < 丶預測->size(); 甲++)
		{
			丶丶預測參照[甲] = new 類別_預測參照(丶預測->at(甲), 丶參照->at(甲));
			if (丶參照->at(甲) == 0)
				負樣本數++;
			else if (丶參照->at(甲) == 1)
				正樣本數++;
			else
				throw 類別_評價異常(L"計算排序準確率時出現異常：參照向量中有非0非1的值！");
		}

		if (正樣本數 == 0)
			throw 類別_評價異常(L"計算比較準確率時出現異常：沒有負樣本！");
		if (負樣本數 == 0)
			throw 類別_評價異常(L"計算比較準確率時出現異常：沒有正樣本！");

		qsort_s
		(
			丶丶預測參照
			, 丶預測->size()
			, sizeof(void*)
			, [](void* 子, const void* 丶甲, const void* 丶乙) -> __int32
			{
				auto 預測甲 = (*reinterpret_cast<類別_預測參照**>(const_cast<void*>(丶甲)))->預測;
				auto 預測乙 = (*reinterpret_cast<類別_預測參照**>(const_cast<void*>(丶乙)))->預測;
				if (預測甲 > 預測乙)
					return 1;
				if (預測甲 == 預測乙)
					return 0;
				return -1;
			}
			, 0
		);

		auto 當前值 = 丶丶預測參照[0]->預測;
		auto 剩餘正樣本數 = 正樣本數;
		auto 當前值正樣本數 = 0.0;
		auto 當前值負樣本數 = 0.0;
		auto 比較正確數 = 0.0;
		for (auto 甲 = 0; 甲 < 丶預測->size(); 甲++)
		{
			if (丶丶預測參照[甲]->預測 != 當前值)
			{
				比較正確數 += 當前值負樣本數 * (0.5 * 當前值正樣本數 + 剩餘正樣本數);
				當前值 = 丶丶預測參照[甲]->預測;
				當前值正樣本數 = 0;
				當前值負樣本數 = 0;
			}

			if (丶丶預測參照[甲]->參照 == 0)
				當前值負樣本數++;
			else
			{
				當前值正樣本數++;
				剩餘正樣本數--;
			}
		}
		比較正確數 += 當前值負樣本數 * (0.5 * 當前值正樣本數 + 剩餘正樣本數);

		for (auto 甲 = 0; 甲 < 丶預測->size(); 甲++)
			delete 丶丶預測參照[甲];
		delete[] 丶丶預測參照;

		return 比較正確數 / 正樣本數 / 負樣本數;
	}

private:
	class 類別_預測參照
	{
	public:
		double 預測;
		double 參照;

		類別_預測參照(double 預, double 參) : 預測(預), 參照(參)
		{
		}
	};

public:
	class 類別_評價異常 : std::exception
	{
	public:
		類別_評價異常(std::wstring 異常字串) : exception(std::string(異常字串.begin(), 異常字串.end()).c_str())
		{

		}
	};
};
