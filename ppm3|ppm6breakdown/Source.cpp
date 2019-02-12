#include <iostream>

#include "Image.h"

using namespace std;
using namespace myImage;

int main()
{
	Image *img1 = new Image(color{ 0, 0, 0 });
	//Image *img2 = new Image(color{ 128, 0, 0 });
	//Image img1(color{ 0, 0, 0 });
	//Image img2(color{ 128, 0, 0 });
	//Image difImg = img1.AbsDifference(img2);
	std::cout << "made it as far as beginning of readfrom file" << std::endl;
	img1->ReadFromFile("birdsNoCom.ppm");
	//img2 = img1.CircularShift();
	//Image difImg = img1.AbsDifference(img2);
	//Image difImg = img1->AbsDifference(*img2);
//	difImg.WriteAllB("output1.ppm");
	//difImg = img1.SpatialDifference();
//	difImg.WriteAllB("output2.ppm");

	return 0;
}