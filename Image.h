#include <stdint.h>
// #include<cstdio>
enum ImageType
{
    PNG,
    JPG,
    TGA,
    BMP
};

class Image
{

public:
    uint8_t *data = NULL;
    size_t size = 0;

    int h;
    int w;
    int channels;

    // constructor

    //  Image();
    Image(const char *filename);
    Image(int w, int h, int channels);
    Image(const Image &img);

    // destructor

    ~Image();

    bool read(const char *filename);
    bool write(const char *filename);

    ImageType getFileType(const char *filename);

    Image &grayscale_avg();
    Image &grayscale_lum();
    Image &color_mask(float r, float g, float b);
};
