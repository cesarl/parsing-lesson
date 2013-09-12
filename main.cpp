#include				<cstdlib>
#include				"ProducterStream.hpp"

int					main()
{
  ProducterStream			st;

  if (!st.loadFile("main.cpp"))
    {
      std::cout << "Fail to open main,cpp" << std::endl;
      return EXIT_FAILURE;
    }


  while (!st.isEndOfFile())
    {
      std::cout << st.nextString();
    }

  return EXIT_SUCCESS;
}
