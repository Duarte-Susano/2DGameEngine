#include <exception>
#include <string>
#include <SDL.h>

class InitError : public std::exception {
public:
	//Sends the error
	InitError();
	InitError(const std::string&);
	virtual ~InitError() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};