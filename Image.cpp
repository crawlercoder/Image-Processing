#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
using namespace std;

// constructors

Image::Image(const char *filename)
{

    if (read(filename))
    {
        cout << "Read " << filename << endl;
        size = w * h * channels;
    }
    else
    {
        cout << "failes to read " << filename << endl;
    }
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels)
{

    size = w * h * channels;
    data = new uint8_t[size];
}
Image::Image(const Image &img) : Image(img.w, img.h, img.channels)
// :w(img.w) , h(img.h) , channels(img.channels)
{

    memcpy(data, img.data, size);
}

// destructor
Image::~Image()
{

    stbi_image_free(data);
}

bool Image::read(const char *filename)
{

    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

// write contents of a file

bool Image::write(const char *filename)
{

    ImageType type = getFileType(filename);
    int success;
    switch (type)
    {

    case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w * channels);
        break;
    case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;
    case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
    case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    }
    return success != 0;
}

// to extract extension type

ImageType Image ::getFileType(const char *filename)
{

    const char *ext = strrchr(filename, '.');

    if (ext != nullptr)
    {
        if (strcmp(ext, ".png") == 0)
        {
            return PNG;
        }
        else if (strcmp(ext, ".jpg") == 0)
        {
            return JPG;
        }
        else if (strcmp(ext, ".bmp") == 0)
        {
            return BMP;
        }
        else if (strcmp(ext, ".tga") == 0)
        {
            return TGA;
        }
    }
    return PNG;
}

// grayscale an image

Image &Image::grayscale_avg()
{

    if (channels < 3)
    {
        cout << "Image " << this << "has less than three channels, it is already assumed to be in grayscale " << endl;
    }
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            //(r+g+b)/3
            int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
            memset(data + i, gray, 3);
        }
    }
    return *this;
}

Image &Image::grayscale_lum()
{
    if (channels < 3)
    {
        cout << "Image " << this << "has less than three channels, it is already assumed to be in grayscale " << endl;
    }
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            // reference from wikipedia

            int gray = (0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2]);
            memset(data + i, gray, 3);
        }
    }
    return *this;
}

// color grading

Image &Image ::color_mask(float r, float g, float b)
{
    if(channels<3){
        cout<<"color Mask requires 3 channels, but the image has only "<<channels<<" channels"<<endl;
    }else{
        for(int i=0;i<size;i+=channels){
            data[i] *=r;
            data[i+1] *=g;
            data[i+2] *=b;
        }
    }
    return *this;
}
