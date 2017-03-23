#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "機器學習.HPP"
#include "資料表.HPP"
#include "梯度提升.HPP"
#include "評價.HPP"

int wmain()
{
	setlocale(0, "");
	
	try
	{
		unsigned __int16 丶字串[256];
		類別_機器學習::顯視時間(L"程式開始執行！\n");

		auto 丶訓練資料表 = 類別_資料表::閱讀資料(L"train.csv");
		swprintf_s(丶字串, 256, L"已讀入%lld列%lld欄資料！\n", 丶訓練資料表->列數, 丶訓練資料表->欄數);
		類別_機器學習::顯視時間(丶字串);

		auto 丶測試資料表 = 類別_資料表::閱讀資料(L"test.csv");
		swprintf_s(丶字串, 256, L"已讀入%lld列%lld欄資料！\n", 丶測試資料表->列數, 丶測試資料表->欄數);
		類別_機器學習::顯視時間(丶字串);

		auto 丶參照資料表 = 類別_資料表::閱讀資料(L"reference.csv");
		swprintf_s(丶字串, 256, L"已讀入%lld列%lld欄資料！\n", 丶參照資料表->列數, 丶參照資料表->欄數);
		類別_機器學習::顯視時間(丶字串);


		auto 丶特征陣列 = new unsigned __int64[丶訓練資料表->欄數 - 2];
		for (auto 甲 = 0ULL; 甲 < 丶訓練資料表->欄數 - 2; 甲++)
			丶特征陣列[甲] = 甲 + 1;

		auto 丶標籤值陣列 = new double[丶訓練資料表->列數];
		for (auto 甲 = 0ULL; 甲 < 丶訓練資料表->列數; 甲++)
			丶標籤值陣列[甲] = 丶訓練資料表->資料[甲][257];

		類別_梯度提升模型 模型;
		類別_機器學習::顯視時間(L"決策樹訓練開始！\n");
		模型.訓練(丶訓練資料表, 丶標籤值陣列, 丶特征陣列, 255, 50, 0.1, 10, 0.01, 512, 0, 1);
		類別_機器學習::顯視時間(L"決策樹訓練結束！\n");
		delete[] 丶特征陣列;
		delete[] 丶標籤值陣列;

		auto 丶預測值陣列 = new double[丶測試資料表->列數];
		模型.預測(丶測試資料表, 丶預測值陣列);

		auto 丶參照值陣列 = new double[丶參照資料表->列數];
		for (auto 甲 = 0ULL; 甲 < 丶參照資料表->列數; 甲++)
			丶參照值陣列[甲] = 丶參照資料表->資料[甲][1];

		wprintf_s(L"%.12lf\n", 類別_評價::計算比較準確率(丶預測值陣列, 丶參照值陣列, 丶參照資料表->列數));

		std::wofstream 檔案輸出流("A.csv");
		for (auto 甲 = 0ULL; 甲 < 丶參照資料表->列數; 甲++)
			檔案輸出流 << 丶預測值陣列[甲] << std::endl;
		檔案輸出流.close();

		delete[] 丶預測值陣列;
		delete 丶訓練資料表;
		delete 丶測試資料表;
		delete 丶參照資料表;

		return 0;
	}
	catch (類別_異常 異常)
	{
		異常.輸出();
	}
}
