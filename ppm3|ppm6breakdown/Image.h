#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>

struct color
{
//public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

//600 x 400y
namespace myImage
{


	class Image
	{
	public:
		//Image();
		Image(color c);
		//Image(const Image& s);
		void WriteAll(std::string filename);
		void WriteAllB(std::string filename);
		Image AbsDifference(const Image& source);
		//You need to implement
		void ReadFromFile(std::string filename);
		Image CircularShift();
		Image SpatialDifference();
	private:
		
	std::vector< std::vector<color> > vect;
	};

}

#endif