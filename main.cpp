#include <iostream>
using namespace std;
#include "Image.cpp"
// #include "Image.h"

int main(int argc, char **argv)
{

    Image test("test.jpg");
    // test.write("new.jpg");

    Image gray_avg = test;
    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.jpg");


    Image gray_lum = test;
    gray_lum.grayscale_lum();
    gray_lum.write("gray_lum.jpg");

    
    Image color_mask = test;
    color_mask.color_mask(0,1,1);
    color_mask.write("color_mask.jpg");



    // Image copy = test;            //create a copy of the original image
    // for (int i = 0; i < copy.w * copy.channels; ++i)
    // {
    //     copy.data[i] = 255;
    // }
    // copy.write("copy.jpg");

    // Image blank(100, 100, 3);     //create a new blank image
    // blank.write("blank.jpg");

    return 0;
}
