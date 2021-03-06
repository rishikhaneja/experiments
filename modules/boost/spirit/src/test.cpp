#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>


#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

///////////////////////////////////////////////////////////////////////////
//  Our number list parser
///////////////////////////////////////////////////////////////////////////
//[tutorial_numlist1
template <typename Iterator> bool parse_numbers(Iterator first, Iterator last) {
  using ascii::space;
  using qi::double_;
  using qi::phrase_parse;

  bool r = phrase_parse(first,                        /*< start iterator >*/
                        last,                         /*< end iterator >*/
                        double_ >> *(',' >> double_), /*< the parser >*/
                        space                         /*< the skip-parser >*/
  );
  if (first != last) // fail if we did not get a full match
    return false;
  return r;
}
//]
} // namespace client

using namespace std;
using namespace testing;

TEST(boost_spirit, basic) {
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tA comma separated list parser for Spirit...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n\n";

  std::cout << "Give me a comma separated list of numbers.\n";
  std::cout << "Type [q or Q] to quit\n\n";

  std::string str;
  while (getline(std::cin, str)) {
    if (str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    if (client::parse_numbers(str.begin(), str.end())) {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << str << " Parses OK: " << std::endl;
    } else {
      std::cout << "-------------------------\n";
      std::cout << "Parsing failed\n";
      std::cout << "-------------------------\n";
    }
  }

  std::cout << "Bye... :-) \n\n";
}