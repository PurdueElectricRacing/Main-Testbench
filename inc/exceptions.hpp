#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <exception>
#include <string>

// likely going to add a bunch of exceptions here
class CanSocketException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while opening a CAN socket.\n";
  }
} CanSocketException;

class CanDataException : public std::exception
{
  virtual const char *what() const throw()
  {
    return "An error occurred while attempting to read / write from CAN device.\n";
  }
} CanDataException;


#endif