#include <iostream>
#include <cassert>

class Image
{
public:
    int data;
};

class Video
{
public:
    double data;
};

enum ERR
{
    FILE_NOT_FOUND = 0,
    FILE_ALREADY_EXISTS
};

void func() {
    //something
    throw std::exception();
}

int main()
{
    try
    {
    //nopurposelines
    Video* vid{};
    Image* img = reinterpret_cast<Image*>(vid);

    double* data = new double[10];

    char carray[100]{};
    carray[101] = 'C';

    img = new Image();
    assert(img == nullptr);

    delete[] data;
    double val = data[0];

    }
    catch (const std::exception&)
    {
        return ERR::FILE_NOT_FOUND;
    }

    try {}
    catch(const std::exception&){}
}
