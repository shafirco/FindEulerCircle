#ifndef INVALID_INPUT_EXCEPTION
#define INVALID_INPUT_EXCEPTION
#include <string>
class InvalidInputException
{
	std::string invalidInputString = "invalid input";
public:
	std::string Message() { return invalidInputString; }
};
#endif // !INVALID_INPUT_EXCEPTION

