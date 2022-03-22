#include "doctest.h"
#include "Notebook.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
using namespace ariel;

 ariel :: Notebook notebook;

TEST_CASE("good write and read"){
CHECK(notebook.write(1,2,10,Direction::Horizontal,"hello")==0);
CHECK(notebook.read(1,2,10,Direction::Horizontal,5)==0);//should read hello
CHECK(notebook.write(1,2,9,Direction::Vertical,"bye")==0);
CHECK(notebook.read(1,2,9,Direction::Horizontal,3)==0);//should read bhe

//now well see what happens if a message runs over another

CHECK(notebook.write(1,2,11,Direction::Vertical,"nadav")==0);
CHECK(notebook.read(1,2,10,Direction::Horizontal,5)==0);//the 'n' took over 'e' spot in the "hello" so we'll get hnllo
CHECK(notebook.read(1,2,11,Direction::Vertical,5)==0);//should read "nadav" 

//now well try to write to diffrent pages

CHECK(notebook.write(2,3,3,Direction::Horizontal,"ice-cream")==0);
CHECK(notebook.read(2,3,6,Direction::Horizontal,6)==0);// should read "-cream"
CHECK(notebook.read(2,3,3,Direction::Horizontal,3)==0);//should read "ice"
CHECK(notebook.write(3,14,15,Direction::Vertical,"CPP")==0);
CHECK(notebook.read(3,14,15,Direction::Vertical,3)==0);//should read "CPP"

//now well try large pages numbers

CHECK(notebook.write(1000,14,15,Direction::Vertical,"C++")==0);
CHECK(notebook.read(1000,14,15,Direction::Vertical,3)==0);//should read "C++"
CHECK(notebook.write(5000,114,17,Direction::Vertical,"Barca")==0);
CHECK(notebook.read(5000,114,17,Direction::Vertical,5)==0);//should read "Barca"

//now well check the erase function 
CHECK(notebook.erase(1000,14,15,Direction::Vertical,3)==0);
CHECK(notebook.read(1000,14,15,Direction::Vertical,3)==0);// should read "~~~"
CHECK(notebook.erase(2,3,6,Direction::Horizontal,6)==0);
CHECK(notebook.read(2,3,6,Direction::Horizontal,6)==0);// should read "~~~~~~"
CHECK(notebook.write(5,14,15,Direction::Vertical,"C++")==0);
CHECK(notebook.erase(5,14,15,Direction::Vertical,1)==0);
CHECK(notebook.read(5,14,15,Direction::Vertical,3)==0);// should read "~++"

//Show function
CHECK(notebook.write(6,1,1,Direction::Horizontal,"C++")==0);
CHECK(notebook.write(1,2,1,Direction::Vertical,"hello")==0);
CHECK_NOTHROW(notebook.show(6));//should look like that:
//C + + 
//h 
//e
//l
//l
//o

}
TEST_CASE("Negative inputs"){
    CHECK_THROWS(notebook.write(-100,-1,10,Direction::Horizontal,"hey"));//cannot use negative page and negative row together to write
    CHECK_THROWS(notebook.write(100,-1,10,Direction::Horizontal,"hey"));//cannot use negative row to write
    CHECK_THROWS(notebook.write(-100,1,10,Direction::Horizontal,"hey"));//cannot use negative page to write
    CHECK_THROWS(notebook.read(100,100,10,Direction::Horizontal,-5));//cannot read negative number of cells
    CHECK_THROWS(notebook.read(-100,-1,10,Direction::Horizontal,3));//cannot use negative pages and negative rows&cols together to read
    CHECK_THROWS(notebook.read(100,-1,-10,Direction::Horizontal,3));//cannot use negative col to read
    CHECK_THROWS(notebook.read(-100,1,-10,Direction::Horizontal,3));//cannot use negative row to read
    CHECK_THROWS(notebook.read(10,5,-10,Direction::Horizontal,4));//cant read from a negetive col
    CHECK_THROWS(notebook.read(-100,-1,10,Direction::Horizontal,-3));
    CHECK_THROWS(notebook.read(-100,100,10,Direction::Horizontal,-30));
    CHECK_THROWS(notebook.read(100,-1,10,Direction::Horizontal,-13));
    
}
TEST_CASE("Out of line inputs"){
    CHECK_THROWS(notebook.write(100,1,100,Direction::Horizontal,"hey"));//each row lenght is 100 
    CHECK_THROWS(notebook.write(10,31,99,Direction::Horizontal,"hey"));
    CHECK_THROWS(notebook.write(3,11,104,Direction::Horizontal,"hey"));
    CHECK_THROWS(notebook.write(100,1,200,Direction::Vertical,"hey"));
    CHECK_THROWS(notebook.write(100,1,111,Direction::Vertical,"hey"));
    CHECK_THROWS(notebook.write(100,1,90,Direction::Horizontal,"123456789123"));
    CHECK_THROWS(notebook.write(100,1,80,Direction::Horizontal,"123456789123123456789123"));
    

}