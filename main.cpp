#include				<cstdlib>
#include				"ProducterStream.hpp"
#include				"ConsumerParser.hpp"

int					main()
{
  ProducterStream			st;
  ConsumerParser			parser(st);

  if (!st.loadFile("main.cpp"))
    {
      std::cout << "Fail to open main,cpp" << std::endl;
      return EXIT_FAILURE;
    }

  while (!parser.readUntil('j'))
    ;

  return EXIT_SUCCESS;
}
