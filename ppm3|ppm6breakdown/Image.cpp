#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <set>
#include <map>
#include <experimental/iterator>
#include "Image.h"


namespace myImage
{
	
	Image::Image(color c)
	{
		vect.clear();
	}
/*
	Image Image::AbsDifference(const Image& so)
	{
		Image loc(color{ 0, 0, 0 });
		for (int row = 0; row < NROWS; row++)
		{
			for (int col = 0; col < NCOLS; col++)
			{
				color c;
				c.r = abs(arr[row][col].r - so.arr[row][col].r);
				c.g = abs(arr[row][col].g - so.arr[row][col].g);
				c.b = abs(arr[row][col].b - so.arr[row][col].b);
				loc.arr[row][col] = c;
			}
		}
		return loc;
	}

	void Image::WriteAll(std::string filename)
	{
		//std::string name = "out.ppm";
		//ofstream fout;
		//fout.open(name);
		std::ofstream fout(filename);
		fout << "P3" << std::endl;
		fout << NCOLS << " " << NROWS << std::endl;
		fout << 255 << std::endl;
		for (int row = 0; row < NROWS; row++)
		{
			for (int col = 0; col < NCOLS; col++)
			{
				fout << static_cast<unsigned int>(arr[row][col].r) << " " << static_cast<unsigned int>(arr[row][col].g) << " " << static_cast<unsigned int>(arr[row][col].b) << " ";
			}
			fout << std::endl;
		}
		fout << std::endl;
		fout.close();
	}

	/*
	void Image::WriteAllB(std::string filename)
	{
		//std::ofstream fout("outB.ppm", std::ios::out | std::ios::binary);
		std::ofstream fout(filename, std::ios::out | std::ios::binary);
		fout << "P6" << std::endl;
		fout << NCOLS << " " << NROWS << std::endl;
		fout << 255 << std::endl;
		for (int row = 0; row < NROWS; row++)
		{
			for (int col = 0; col < NCOLS; col++)
			{
				fout << arr[row][col].r << arr[row][col].g << arr[row][col].b;
			}
		}
		fout.close();
	}
	*/

	void Image::ReadFromFile(std::string filename){
			std::string header;
			std::string s2;
			std::ifstream ifs;
			unsigned  int w,h,rgb,garbagecollection;  //width//height//rgb type
			garbagecollection = '_';
			ifs.open(filename, std::ios::binary);
			std::cout << "we made it past definitions" << std::endl;

			if(ifs.fail()){
				throw("can't open input file");
			}
			ifs >> header;
			//if(strcmp(header.c_str(), "P6") != 0) {
			//	throw("cant read input file");
			//}
			
			//std::cout << "garbage collection" << std::endl;
			//while(garbagecollection != '\n'){
				//ifs >> garbagecollection;
			//}

			std::cout << "made it past garbage collection and head reader"<< std::endl;
			std::cout << header << std::endl;
			std::cout << "this is our out code" << std::endl;
			ifs >> w >> h>> rgb;
			std::cout << w << std::endl;
			std::cout << h << std::endl;
			std::cout << rgb << std::endl;
			
			std::cout << "-------------------" << std::endl;
			std::cout<<"reading to a temp vector to push into 2d" << std::endl;
				std::vector<color> tempvec;
				color temp;
				std::string _R,_G,_B;
				unsigned char R,G,B;

			if(strcmp(header.c_str(), "P3") == 0){
				std::cout<< "post from p3" <<std::endl;
				for (unsigned int j=0; j < h; j++){
				tempvec.clear();
			for (unsigned int i =0; i < w; i++){
				ifs >> _R >>_G >>_B;
				std::cout<<"before stirng reinterprets" << std::endl;
				//std::string Red(reinterpret_cast<char*>(_R));
				//std::string Green(reinterpret_cast<char*>(_G));
				//std::string Blue(reinterpret_cast<char*>(_B));
				temp.r = static_cast<unsigned char>(std::stoi(_R,nullptr,10));
				temp.g = static_cast<unsigned char>(std::stoi(_G,nullptr,10));
				temp.b = static_cast<unsigned char>(std::stoi(_B,nullptr,10));
				std::cout << static_cast<int>(temp.r) << " " << static_cast<int>(temp.b) << " " << static_cast<int>(temp.g) << std::endl;
				
				tempvec.push_back(temp);
			 }
			   vect.push_back(tempvec);
			}
			}else {
				std::cout << "posting from p6" << std::endl;
			for (unsigned int j=0; j < h; j++){
				tempvec.clear();
			for (unsigned int i =0; i < w; i++){
				ifs >> R >>G >>B;
				temp.r = R; 
				temp.g = G;
				temp.b = B;
				std::cout << static_cast<int>(temp.r) << " " << static_cast<int>(temp.b) << " " << static_cast<int>(temp.g) << std::endl;
				tempvec.push_back(temp);
			 }
			   vect.push_back(tempvec);
			}
		}

		

			ifs.close();
			std::cout << "out lay of vector to map" << std::endl;
			std::vector<unsigned char> storagevec;
			std::cout<<"averaging static cast ints" << std::endl;
			storagevec.clear();
			for (unsigned int j=0; j < h; j++){
			for (unsigned int i =0; i < w; i++){
			int pushvalue = 0;
			//std::cout << static_cast<int>(vect[j][i].r)  << " " << static_cast<int>(vect[j][i].g) << " " << static_cast<int>(vect[j][i].b) << std::endl;
			pushvalue = (static_cast<int>(vect[j][i].r) + static_cast<int>(vect[j][i].g) + static_cast<int>(vect[j][i].b))/3;
			storagevec.push_back(pushvalue);
			}
		}	

		std::cout<<"setting to a set then to a map" << std::endl;
		std::set<unsigned char> setter(storagevec.begin(),storagevec.end());
		std::map<unsigned char,int> mapper;
		unsigned int count =0;
		for(std::set<unsigned char>::iterator it=setter.begin(); it !=setter.end();it++){
			count = 0;
			for(std::vector<unsigned char>::const_iterator vit = storagevec.begin(); vit != storagevec.end(); vit++){
					if(*it == *vit) ++count;
			}
			mapper.insert(std::pair<unsigned char, unsigned int>(*it, count));
		}
		std::cout<<"opening stream" << std::endl;
		std::ofstream stream("output.txt");
		for(auto elem : mapper)
		{
  			 stream << static_cast<int>(elem.first) << " " << static_cast<int>(elem.second)<< "\n";
		}
		stream.close();
	}
}