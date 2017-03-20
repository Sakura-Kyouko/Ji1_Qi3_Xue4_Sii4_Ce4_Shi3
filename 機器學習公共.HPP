#pragma once

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
