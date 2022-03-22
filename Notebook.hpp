#include <iostream>
#include <string.h>
#include "Direction.hpp"
using ariel::Direction;
using namespace std;

namespace ariel {
   class Notebook{
      public :
static int read(int page ,int col,int row,Direction d,int len);
static int write(int page, int col, int row, Direction d,const string &s);
static int erase(int page ,int col,int row,Direction d,int len);
static void show(int page);
   };
   }