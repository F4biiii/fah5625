#include <iostream>
using namespace std;

class ImageFile
{
private:
    string name;
    // other attributes omitted, e.g. path, access rights, ...
    int height;
    int width;
    int bits;
public:
    ImageFile(const string pName, const int pHeight,
              const int pWidth, const int pBits)
    {
        name = pName;
        height = pHeight;
        width = pWidth;
        bits = pBits;       // bits per pixel
    }
    string getName() const { return name;}
    int fsize() const { return height * width * bits; }
};

class TextFile
{
private:
    string name;
    // other attributes omitted, e.g. path, access rights, ...
    int chars;              // number of characters in file
    int bytes;              // bytes per character
public:
    TextFile(const string pName, const int pChars,
             const int pBytes)
    {
        name = pName;
        chars = pChars;
        bytes = pBytes;
    }
    string getName() const { return name;}
    int fsize() const { return chars * bytes * 8; }
};

int main()
{
    ImageFile ifile("image.bmp", 480, 640, 16);
    cout << ifile.getName() << " " << ifile.fsize() << '\n';
    TextFile tfile("text.txt", 1000, 2);
    cout << tfile.getName() << " " << tfile.fsize() << '\n';
}
