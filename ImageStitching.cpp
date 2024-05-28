// ImageStitching.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include "Stitcher.h"

int main(int argc, char** argv)
{
	//if (argc == 3 && std::string(argv[1]) == "-first_image_path" && std::string(argv[3]) == "-second_image_path") {
		//char* first_image_path = argv[2];
		//char* second_image_path = argv[4];
		ImageStitcher Object;
		
		vector<string> ImagesPath;
		//ImagesPath.push_back(first_image_path);
		//ImagesPath.push_back(second_image_path);
		
		ImagesPath.push_back("DSC02930.jpg");
	    ImagesPath.push_back("DSC02931.jpg");
		ImagesPath.push_back("DSC02932.jpg");
		ImagesPath.push_back("DSC02933.jpg");
		ImagesPath.push_back("DSC02934.jpg");

		vector<Mat> images;
		string direction = "horizontal";

		for (int i = 0; i < ImagesPath.size(); i++)
		{
			Mat inImg = imread(ImagesPath[i]);
			Mat outImg;
			cv::resize(inImg, outImg, cv::Size(inImg.cols * 0.25, inImg.rows * 0.25), 0, 0);
			images.push_back(outImg);
		}

		Object.findGoodMatches(images, direction);
	//}
}


 