#ifndef _CALCINFOHANDLER_H_
#define _CALCINFOHANDLER_H_

#include <string>
#include <cctype>

class cCalcInfoHandler
{

};
class cTextHandler
{
public:
	const char* GetExpressionText();
	void AddSymbol(char);
	void AddOperation(char);
	void SetResult(char*);
	void RemoveSymbol();

private:
	std::string expressionStr;
};
#endif