#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::stringFiller(long n) {
  string s;
  if (n < 10) {
    s = "0"+std::to_string(n);
  } else {
    s = std::to_string(n);
  }
  return s;
}

string Format::ElapsedTime(long seconds) {
    if (seconds < 0) {
      return "seconds must be >= 0";
    }
    unsigned short int h, m;
    string hS, mS, sS;
    /* hours calculation */
    h = seconds/3600;
    seconds%=3600;
    /* minutes calculation */
    m = seconds/60;
    seconds%=60;
    /* string tunning */
    hS = Format::stringFiller(h);
    mS = Format::stringFiller(m);
    sS = Format::stringFiller(seconds);
    return hS+":"+mS+":"+sS;
}
