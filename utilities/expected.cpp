/*
    x86-64 gcc 11.2
    -std=c++20

    https://godbolt.org/z/va5fzx11f
*/
#include <algorithm>
#include <charconv>
#include <concepts>
#include <ranges>
#include <string_view>
#include <iostream>
#include <fmt/ranges.h>
#include <https: //raw.githubusercontent.com/TartanLlama/expected/master/include/tl/expected.hpp>

#include <boost/date_time.hpp>
#include <iostream>
#include <string>
using std::cout, std::endl;
using namespace boost::posix_time;
using namespace std::literals;

using time_expected = tl::expected<boost::posix_time::ptime, std::string>;
using void_expected = tl::expected<void, std::string>;
using int_expected = tl::expected<int, std::string>;

time_expected from_iso_str(std::string time)
{
   try
   {
      ptime t = boost::posix_time::from_iso_string(time);
      return t;
   }
   catch (std::exception &e)
   {
      return tl::make_unexpected(e.what() + " str was: "s + time);
   }
}

// for use with and_then
time_expected previous_day(boost::posix_time::ptime t)
{
   return t - boost::gregorian::days(1);
}

// for use with transform
ptime next_day(boost::posix_time::ptime t)
{
   return t + boost::gregorian::days(1);
}
// for use with or_else
void print_error(std::string error)
{
   cout << error << endl;
}
int_expected square(int x)
{
   return x * x;
}
int_expected by_two(int x)
{
   return 2 * x;
}
int_expected int_error(int x)
{
   return tl::make_unexpected(fmt::format("error: {}", x));
}

void_expected doit(int v)
{
   cout << "do it " << v << endl;
   if (v < 5)
      return {}; // void return
   return tl::make_unexpected(fmt::format("V must be less than 5 passed {}", v));
}
void_expected doit2()
{
   cout << "do it2 " << endl;
   return {};
}

int main()
{
   {
      auto res = square(2).and_then(by_two).and_then(square);
      cout << *res << endl; // 256
      res = square(2).and_then(int_error).or_else(print_error);
      // cout << res.error() << endl;
      // res = int_error( 2 ).or_else( print_error );
   }
   {
      auto res = doit(1);
      if (res)
      {
         cout << "1 good\n";
      }
      res = doit(5);
      if (!res)
      {
         cout << res.error() << endl;
      }
   }
   { // void expected
      auto res = doit(1).and_then(doit2);
      res = doit(1).or_else(print_error);
      res = doit(5).or_else(print_error);
      // not allowed res = doit(5).transform(doit(5));
      // not allowed res = doit(5).value_or({});
   }
   const std::string ts("20210726T000000");
   {
      auto res = from_iso_str(ts).transform(to_iso_extended_string);
      if (res)
      {
         cout << *res << endl;
      }
   }
   {
      auto res = from_iso_str(ts);
      if (res)
      {
         cout << res->date() << endl;
      }
   }
   const std::string bad_ts("F0210726T000000");
   auto bad_res = from_iso_str(bad_ts);
   if (!bad_res)
   {
      cout << bad_res.error() << endl;
   }
   {
      auto d = from_iso_str(ts).and_then(previous_day);
      cout << *d << endl;
   }
   {
      // before
      auto d = from_iso_str(ts);
      if (d)
      {
         ptime t2 = next_day(*d);
      }
      else
      {
         print_error(d.error());
      }
      cout << "transform:" << *d << endl;
      d = from_iso_str(bad_ts).transform(next_day);
      // oh oh d = from_iso_str ( bad_ts ).transform( next_day ).or_else( print_error ) ;
      if (!d.has_value())
      {
         cout << d.error() << endl;
      }
   }
   {

      auto d = from_iso_str(ts)
                   .or_else(print_error)
                   .transform(next_day);
      cout << "transform:" << *d << endl;
      d = from_iso_str(bad_ts).transform(next_day);
      // oh oh d = from_iso_str ( bad_ts ).transform( next_day ).or_else( print_error ) ;
      if (!d.has_value())
      {
         cout << d.error() << endl;
      }
   }
   {
      auto d = from_iso_str(bad_ts).or_else(print_error);
      d = from_iso_str(ts).or_else(print_error);
      cout << *d << endl;
   }

   // existing
   ptime nadt;
   auto t = from_iso_str(bad_ts).value_or(nadt);
   cout << t << endl; // not-a-date-time

   return 0;
}
