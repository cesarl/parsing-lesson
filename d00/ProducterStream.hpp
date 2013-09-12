#ifndef					PRODUCTERSTREAM_HPP_
# define				PRODUCTERSTREAM_HPP_

# include				<string>
# include				<iostream>
# include				<fstream>
# include				<stdexcept>
# include				<exception>

class					ProducterStream
{
public:
  ProducterStream(void) : mode_(1)
  {}
  ~ProducterStream()
  {
    if (file_.is_open())
      file_.close();
  }

  std::string				nextString(void)
  {
    if (mode_ == 1)
      {
	if (!file_.is_open())
	  throw std::runtime_error("File not opened.");

	file_.read(ret_, 16);
	ret_[file_.gcount()] = '\0';
	if (file_.gcount() == 0)
	  {
	    throw std::runtime_error("End of file.");
	  }
	return ret_;
      }
    else if (mode_ == 2 || mode_ == 3)
      {
	if (mode_ == 3)
	  {
	    throw std::runtime_error("End of stdin.");
	  }
	mode_ = 3;
	return str_;
      }
    else
      {
	throw std::runtime_error("");
      }
  }

  bool					loadFile(const char *path)
  {
    mode_ = 1;
    // A file is already open
    if (file_.is_open())
      file_.close();

    file_.open(path, std::fstream::in);
    if (!file_.good())
      return false;

    if (file_.is_open())
      return true;
    return false;
  }

  bool					loadStdin(void)
  {
    std::getline(std::cin, str_);
    return true;
  }

private:
  std::fstream file_;
  int mode_;
  char ret_[16];
  std::string str_;
};


#endif					/* !PRODUCTERSTREAM_HPP_ */
