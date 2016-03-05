#ifndef _CALCINFOHANDLER_H_
#define _CALCINFOHANDLER_H_

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

enum eOperationType
{
	OT_SUM,
	OT_DIFFERENCE,
	OT_PRODUCT,
	OT_QUOTIENT,
	OT_POW,
	OT_NONE
};
class cTextHandler
{
public:
	const char* GetExpressionText();
	void AddSymbol(char);
	void AddOperation(char);
	void SetResult(std::string);
	void RemoveSymbol();
	void RemoveAll();

private:
	std::string str;

};
class cCalcInfoHandler
{
public:
	const char* GetExpression();
	void ResetAllInfo();
	bool assert(char);
	void AddAction(char);

private:
	long double StringToDouble(std::string);
	std::string DoubleToChar(long double);
	void FindResult();
	void SwapValue();
	void SetCalculateMode(bool);
	

	std::string val_1, val_2;
	std::string *currentVal;

	eOperationType operationType;

	bool val_1_IsActive, val_2_IsActive;
	bool calculateModeIsActive;
	bool floatlyModeIsActive;

	long double result;

	cTextHandler textHandler;
};

#endif