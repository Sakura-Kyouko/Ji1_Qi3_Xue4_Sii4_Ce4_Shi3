#pragma once

class 類別_機器學習
{
public:
	static void 顯視時間(std::wstring 字串)
	{
		unsigned __int16 丶時間字串[256];
		auto 時間 = time(0);
		tm 時間甲;
		localtime_s(&時間甲, &時間);
		wcsftime(丶時間字串, sizeof(丶時間字串), L"%H:%M:%S ", &時間甲);
		wprintf_s(L"%ws %ws", 丶時間字串, 字串);
	}

	static void 計算均方誤差梯海值(double 丶預測值陣列[], double 丶標籤值陣列[], double 丶梯度值陣列[], double 丶海森值陣列[], unsigned __int64 長度)
{
	for (auto 甲 = 0ULL; 甲 < 長度; 甲++)
	{
		丶梯度值陣列[甲] = 丶標籤值陣列[甲] - 丶預測值陣列[甲];
		丶海森值陣列[甲] = 1;
	}
}

	static void 計算對數損失梯海值(double 丶預測值陣列[], double 丶標籤值陣列[], double 丶梯度值陣列[], double 丶海森值陣列[], unsigned __int64 長度)
	{
		for (auto 甲 = 0ULL; 甲 < 長度; 甲++)
		{
			auto 預測 = 丶預測值陣列[甲];
			auto 標籤 = 丶標籤值陣列[甲];
	
			丶梯度值陣列[甲] = 預測 - 標籤;
			丶海森值陣列[甲] = 預測 * (1 - 預測);
		}
	}
};

class 類別_異常
{
public:
	unsigned __int16* 異常字串;

	類別_異常(unsigned __int16* 異)
	{
		異常字串 = 異;
	}

	void 輸出()
	{
		wprintf_s(L"%ws\n", 異常字串);
	}
};
