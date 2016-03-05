#include "CalcInfoHandler.h"

const char* cTextHandler::GetExpressionText()
{
	return expressionStr.c_str();
}
void cTextHandler::AddSymbol(char symbol)
{
	expressionStr += symbol;
}
void cTextHandler::AddOperation(char symbol)
{
	expressionStr = expressionStr + '\n' + symbol + '\n';
}
void cTextHandler::SetResult(char *result)
{
	expressionStr = result;
}
void cTextHandler::RemoveSymbol()
{
	if(expressionStr.empty())
		return;
	if((expressionStr.end() - 1 == '\n'))
}