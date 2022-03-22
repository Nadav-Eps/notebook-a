#include <iostream>
#include <string.h>
#include "Direction.hpp"
using ariel::Direction;
using namespace std;

namespace ariel {
   class Notebook{
      public :
int read(int page ,int col,int row,Direction d,int len);
int write(int page, int col, int row, Direction d,string s);
int erase(int page ,int col,int row,Direction d,int len);
void show(int page);
   };
   }