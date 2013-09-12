#ifndef				__CONSUMER_PARSER_HPP__
# define			__CONSUMER_PARSER_HPP__

#include			<cstring>
#include			<map>
#include			"ProducterStream.hpp"

class ConsumerParser
{
private:
  typedef std::string::iterator strIt;
public:
  ConsumerParser(ProducterStream &prod) :
    prod_(prod)
  {
    it_ = tot_.end();
  }

  virtual ~ConsumerParser()
  {}

  inline bool			peekChar(char c)
  {
    try
      {
	if (tot_.empty())
	  {
	    buf_ = prod_.nextString();
	    tot_ += buf_;
	    it_ = tot_.begin();
	  }
	else if (buf_.empty() || it_ == tot_.end())
	  {
	    buf_ = prod_.nextString();
	    tot_ += buf_;
	    // it_ = buf_.begin();
	  }
      }
    catch (std::exception)
      {
	return false;
      }
    if (it_ == tot_.end())
      return false;
    std::cout << *it_ << std::endl;
    if (*it_ == c)
      return true;
    return false;
  }

  inline bool			readChar(char c)
  {
    if (peekChar(c))
      {
	++it_;
	return true;
      }
    return false;
  }

  inline bool			readRange(char begin, char end)
  {
    for (char i = begin; i <= end; ++i)
      {
	if (readChar(i))
	  return true;
      }
    return false;
  }

  bool				readText(char *text)
  {
    strIt			save;

    save = it_;
    for (unsigned int i = 0, l = std::strlen(text); i < l; ++i)
      {
	if (!readChar(text[i]))
	  {
	    it_ = save;
	    return false;
	  }
      }
    return true;
  }

  bool				readEOF()
  {
    try
      {
	if (buf_.empty() || it_ == tot_.end())
	  {
	    buf_ = prod_.nextString();
	    std::cout << buf_ <<std::endl;
	    tot_ += buf_;
	  }
      }
    catch (std::exception)
      {
	return true;
      }
    if (it_ == tot_.end())
      return true;
    return false;
  }

  bool				readUntil(char c)
  {
    strIt			save;

    save = it_;
    while (!readChar(c) && !readEOF())
      ++it_;
    if (readEOF())
      {
	it_ = save;
	return false;
      }
    return true;
  }

  bool				readUntilEOF()
  {
    if (!readEOF())
      {
	++it_;
	return false;
      }
    return true;
  }

  bool				readInteger()
  {
    if (readRange('0', '9'))
      {
	while (readRange('0', '9'))
	  ;
	return true;
      }
    return false;
  }

  bool				readIdentifier()
  {
    if (readRange('a', 'z') || readRange('A', 'Z') || readChar(' '))
      {
	while (readRange('0', '9') || readRange('a', 'z') || readRange('A', 'Z') || readChar(' '))
	  ;
	return true;
      }
    return false;
  }

  inline bool			beginCapture(const std::string &tag)
  {
    captures_[tag] = it_;
    return true;
  }

  inline bool			endCapture(const std::string &tag, std::string &out)
  {
    if (captures_.find(tag) == captures_.end())
      return false;
    out = std::string(captures_[tag], it_);
    return true;
  }
private:
  ProducterStream		&prod_;
  std::string			buf_;
  std::string			tot_;
  strIt				it_;
  std::map<std::string, strIt>	captures_;		
};

#endif				//__CONSUMER_PARSER_HPP__
