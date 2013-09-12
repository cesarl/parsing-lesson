#ifndef				__PRODUCTER_STREAM_HPP__
# define			__PRODUCTER_STREAM_HPP__

#include			<iostream>
#include			<fstream>
#include			<istream>
#include			<string>
#include			<exception>
#include			<stdexcept>

class				ProducterStream
{
public:
  ProducterStream()
  {}

  virtual ~ProducterStream()
  {
  }

  std::string			nextString()
  {
    std::string			res;

    if (buf_.size() == 0)
      {
	throw std::runtime_error("File problem");
      }
    res = buf_[0];
    buf_ = &buf_[1];
    return res;
  }

  bool				loadFile(const char *path)
  {
    std::ifstream		f(path, std::ifstream::in);

    if (!f.is_open())
      return false;
    buf_ = std::string((std::istreambuf_iterator<char>(f)),
		       std::istreambuf_iterator<char>());    
    f.close();
    return true;
  }

  bool				isEndOfFile()
  {
    return buf_.size() == 0;
  }

private:
  std::string			buf_;
};

# endif				// __PRODUCTER_STREAM_HPP__
