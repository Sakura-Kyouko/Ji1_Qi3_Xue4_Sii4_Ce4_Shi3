#pragma once

#include <vector>

#include "決策樹.HPP"
#include "評價.HPP"

class 類別_梯度提升模型
{
private:
	std::vector<類別_決策樹模型*> 決策樹模型向量;

public:	
	virtual ~類別_梯度提升模型()
	{
		for (auto 甲 = 0; 甲 < 決策樹模型向量.size(); 甲++)
			delete 決策樹模型向量[甲];
	}

	void 訓練
	(
		類別_資料表* 丶資料表
		, double 丶標籤值陣列[]
		, unsigned __int64 丶特征欄索引陣列[] = 0
		, unsigned __int64 特征數 = 0ULL
		, unsigned __int64 迭代次數 = 16
		, double 步長 = 0.1
		, double 最大深度 = 10.0
		, double 最小均方根誤差 = 0.01
		, double 最小葉樣本數 = 512.0
		, double γ = 0.0
		, double λ = 0.0
		, void 扌梯海函式(double*, double*, double*, double*, unsigned __int64) = 類別_機器學習::計算對數損失梯海值
		, __int32 執行緒數 = 4
	)
	{
		auto 丶預測值陣列 = new double[丶資料表->資料.size()]{ 0 };
		auto 丶當前標籤值陣列 = new double[丶資料表->列數];

		for (auto 甲 = 0; 甲 < 丶資料表->列數; 甲++)
			丶當前標籤值陣列[甲] = 丶標籤值陣列[甲];

		auto 丶梯度值陣列 = new double[丶資料表->資料.size()]{ 1e300 * 1e300 * 0 };
		auto 丶海森值陣列 = new double[丶資料表->資料.size()]{ 1e300 * 1e300 * 0 };

		for (auto 甲 = 0; 甲 < 迭代次數; 甲++)
		{
			auto 丶決策樹模型 = new 類別_決策樹模型();
			丶決策樹模型->訓練(丶資料表, 丶當前標籤值陣列, 丶特征欄索引陣列, 特征數, 丶梯度值陣列, 丶海森值陣列, 最大深度, 最小均方根誤差, 最小葉樣本數, γ, λ, 執行緒數);
			
			auto 丶當前預測值陣列 = new double[丶資料表->資料.size()];
			丶決策樹模型->預測(丶資料表, 丶當前預測值陣列);

			for (auto 甲 = 0; 甲 < 丶資料表->列數; 甲++)
				丶預測值陣列[甲] += 丶當前預測值陣列[甲];

			delete[] 丶當前預測值陣列;

			扌梯海函式(丶預測值陣列, 丶標籤值陣列, 丶梯度值陣列, 丶海森值陣列, 丶資料表->列數);
			for (auto 甲 = 0; 甲 < 丶資料表->列數; 甲++)
				丶當前標籤值陣列[甲] = -丶梯度值陣列[甲] * 步長;


			決策樹模型向量.push_back(丶決策樹模型);
			wprintf_s(L"第%d輪迭代 %lf\n", 甲 + 1, 類別_評價::計算比較準確率(丶預測值陣列, 丶標籤值陣列, 丶資料表->資料.size()));
		}

		delete[] 丶梯度值陣列;
		delete[] 丶海森值陣列;
		delete[] 丶預測值陣列;
		delete[] 丶當前標籤值陣列;
	}

	void 預測(類別_資料表* 丶資料表, double 丶預測陣列[])
	{
		for (auto 乙 = 0; 乙 < 丶資料表->列數; 乙++)
			丶預測陣列[乙] = 0;

		for (auto 甲 = 0; 甲 < 決策樹模型向量.size(); 甲++)
		{
			auto 丶當前預測陣列 = new double[丶資料表->列數];
			決策樹模型向量[甲]->預測(丶資料表, 丶當前預測陣列);
			for (auto 乙 = 0; 乙 < 丶資料表->列數; 乙++)
				丶預測陣列[乙] += 丶當前預測陣列[乙];

			delete[] 丶當前預測陣列;
		}
	}
};

