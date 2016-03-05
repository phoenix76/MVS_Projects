#include "CalcInfoHandler.h"

const char* cCalcInfoHandler::GetExpression()
{
	return textHandler.GetExpressionText();
}
bool cCalcInfoHandler::assert(char symbol)
{
	//Если первый элемент - ноль и вводится не точка
	if(currentVal->size() == 1 && (*currentVal)[0] == '0' && symbol != '.' && symbol != 'C' && symbol != 'R')
		return false;

	//Если вводится ноль
	if(symbol == '0')
	{
		//Если первый элемент операнда ноль, и вводится ноль
		if(currentVal->size() == 1 && (*currentVal)[0] == '0')
			return false;
	}

	//Если вводится точка
	if(symbol == '.')
	{
		//Если ввод происходит в первый элемент
		if(currentVal->empty())
			return false;
		//Если точка уже присутствует
		if(floatlyModeIsActive == true)
			return false;
	}

	//Если вводится операция
	if(std::ispunct(symbol) && symbol != '.' && symbol != '=')
	{
		//Если операция уже введена
		if(calculateModeIsActive == true)
			return false;
		//Если первый операнд пустой и вводится операция
		if(val_1.empty())
			return false;
	}

	//Если вводится число
	if(std::isdigit(symbol))
	{
		//Если вводится число во второй элемент и первый равен '0'
		if(currentVal->size() == 1 && (*currentVal)[0] == '0')
			return false;
	}

	//Если вводится равно
	if(symbol == '=')
	{
		if(val_1.empty() || val_2.empty() || operationType == OT_NONE)
			return false;
	}

	//Стереть символ
	if(symbol == 'C')
	{
		if(val_1.empty())
			return false;
	}

	return true;
}
void cCalcInfoHandler::AddAction(char symbol)
{
	//Цифра или точка
	if(std::isdigit(symbol) || symbol == '.')
	{
		//Если точка - установить дробную систему
		if(symbol == '.')
			floatlyModeIsActive = true;

		*currentVal += symbol;
		textHandler.AddSymbol(symbol);
	}
	//Операция
	else if(std::ispunct(symbol) && symbol != '=')
	{
		if(symbol == '+')
			operationType = OT_SUM;
		else if(symbol == '-')
			operationType = OT_DIFFERENCE;
		else if(symbol == '*')
			operationType = OT_PRODUCT;
		else if(symbol == '/')
			operationType = OT_QUOTIENT;
		else if(symbol == '^')
			operationType = OT_POW;

		if(val_1[val_1.size() - 1] == '.')
		{
			val_1.erase(val_1.end() - 1);
			textHandler.RemoveSymbol();
		}

		calculateModeIsActive = true;
		SwapValue();
		textHandler.AddOperation(symbol);
	}
	//Результат
	else if(symbol == '=')
	{
		if(val_2[val_2.size() - 1] == '.')
		{
			val_2.erase(val_2.end() - 1);
			textHandler.RemoveSymbol();
		}
		FindResult();
	}
	//Стереть символ
	else if(symbol == 'C')
	{
		//Если стирается точка
		if(!currentVal->empty() && (*currentVal)[currentVal->size() - 1] == '.')
		{
			currentVal->erase(currentVal->end() - 1);
			textHandler.RemoveSymbol();
			floatlyModeIsActive = false;
			return;
		}
		//Если операнд не пустой просто стереть символ
		if(!currentVal->empty())
		{
			currentVal->erase(currentVal->end() - 1);
			textHandler.RemoveSymbol();
			if(val_1.empty())
				ResetAllInfo();
			return;
		}
		//Если операнд 2 активен и он пустой
		if(val_2_IsActive == true && val_2.empty())
		{
			SwapValue();
			operationType = OT_NONE;
			calculateModeIsActive = false;
			textHandler.RemoveSymbol();
			return;
		}	
	}
	//Стереть все
	else if(symbol == 'R')
	{
		ResetAllInfo();
		textHandler.RemoveAll();
	}
}
long double cCalcInfoHandler::StringToDouble(std::string str)
{
	std::string::size_type sz;
	return std::stold(str, &sz);

}
std::string cCalcInfoHandler::DoubleToChar(long double input)
{
	std::stringstream ss;
	ss.precision(20);
	ss << input;
	return ss.str();
}
void cCalcInfoHandler::FindResult()
{
	if(operationType == OT_SUM)
		result = StringToDouble(val_1) + StringToDouble(val_2);
	else if(operationType == OT_DIFFERENCE)
		result = StringToDouble(val_1) - StringToDouble(val_2);
	else if(operationType == OT_PRODUCT)
		result = StringToDouble(val_1) * StringToDouble(val_2);
	else if(operationType == OT_QUOTIENT)
		result = StringToDouble(val_1) / StringToDouble(val_2);
	else if(operationType == OT_POW)
		result = std::pow(StringToDouble(val_1), static_cast<int>(StringToDouble(val_2)));

	val_1.erase(val_1.begin(), val_1.end());
	val_2.erase(val_2.begin(), val_2.end());
	SwapValue();
	operationType = OT_NONE;
	calculateModeIsActive = false;
	*currentVal = DoubleToChar(result);
	for(unsigned int i = 0; i < currentVal->size(); i++)
	{
		if((*currentVal)[i] == '.')
		{
			floatlyModeIsActive = true;
			break;
		}
	}
	textHandler.SetResult(DoubleToChar(result));
}
void cCalcInfoHandler::SwapValue()
{
	if(val_1_IsActive == true && val_2_IsActive == false)
	{
		currentVal = &val_2;
		val_1_IsActive = false;
		val_2_IsActive = true;
		floatlyModeIsActive = false;
	}
	else if(val_1_IsActive == false && val_2_IsActive == true)
	{
		currentVal = &val_1;
		val_1_IsActive = true;
		val_2_IsActive = false;
		floatlyModeIsActive = false;
	}
}
void cCalcInfoHandler::ResetAllInfo()
{
	val_1.erase(val_1.begin(), val_1.end());
	val_2.erase(val_2.begin(), val_2.end());
	operationType = OT_NONE;
	currentVal = &val_1;
	val_1_IsActive = true;
	val_2_IsActive = false;
	calculateModeIsActive = false;
	floatlyModeIsActive = false;
	result = 0.0;
	textHandler.RemoveAll();
}

const char* cTextHandler::GetExpressionText()
{
	return str.c_str();
}
void cTextHandler::AddSymbol(char symbol)
{
	str += symbol;
}
void cTextHandler::AddOperation(char symbol)
{
	str = str + '\n' + symbol + '\n';
}
void cTextHandler::SetResult(std::string result)
{
	str = result;
}
void cTextHandler::RemoveSymbol()
{
	if(str.empty())
		return;
	else if(str[str.size() - 1] == '\n' && std::ispunct(str[str.size() - 2]) && str[str.size() - 3] == '\n')
	{
		str.erase(str.end() - 1);
		str.erase(str.end() - 1);
		str.erase(str.end() - 1);
	}
	else
		str.erase(str.end() - 1);
}
void cTextHandler::RemoveAll()
{
	if(str.empty())
		return;
	str.erase(str.begin(), str.end());
}