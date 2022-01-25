#include <iostream>
#include <string>


std::string ElapsedTime(long seconds) {
    if (seconds < 0) {
      return "seconds must be >= 0";
    }
    unsigned short int h, m;
    /* hours calculation */
    h = seconds/3600;
    seconds%=3600;
    /* minutes calculation */
    m = seconds/60;
    seconds%=60;
    return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(seconds);
}

int main () {
  std::cout<<"Test with 3680 s = "<<ElapsedTime(3680)<<"."<<std::endl;
  return 0;
}
