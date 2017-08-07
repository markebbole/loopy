#ifndef LOOPY_NODE_EXCEPTIONS
#define LOOPY_NODE_EXCEPTIONS

#include <iostream>
#include <exception>
#include <string>
using namespace std;

struct MissingRequiredParameterException : public exception {
private:
   string msg;
public:
   MissingRequiredParameterException(string parameterName) : exception()
   {
      msg = "Missing required parameter: " + parameterName;
   }
   const char* what () const throw () {
      return msg.c_str();
   }
};

struct WrongParameterTypeException : public exception {
private:
   string msg;
public:
   WrongParameterTypeException(string parameterName) : exception()
   {
      msg = "Parameter has wrong type: " + parameterName;
   }
   const char* what () const throw () {
      return msg.c_str();
   }
};

#endif