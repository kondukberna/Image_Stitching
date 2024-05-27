#include <iostream>
#include "Stitcher.h"

int main(int argc, char** argv)
{
  if (argc < 4) {
    cout << "Usage: " << argv[0] << " -resize <resize_factor> -direction <horizontal/vertical> -images_paths <image_paths...>" << endl;
    return -1;
  }

  ImageStitcher Object;	
	vector<string> ImagesPath;
  vector<Mat> images;
  string resizeFlag = argv[1];
  string direction = argv[4];
  
  if(resizeFlag == "-resize")
  {
    float resizeValue = atof(argv[2]);

    for(int i=6;i<argc;i++)
    {
     char* image_path = argv[i];
     ImagesPath.push_back(image_path);
    }

    for(int j=0;j<ImagesPath.size();j++)
    {
      Mat inImg = imread(ImagesPath[j]);

      if (inImg.empty()) {
        cout << "Error loading image: " << ImagesPath[j] << endl;
        return -1;
      }

		  Mat outImg;
		  resize(inImg, outImg, cv::Size(inImg.cols * resizeValue, inImg.rows * resizeValue), 0, 0);
		  images.push_back(outImg);
    }

    if (images.size() < 2) {
        cout << "Need at least two images for stitching." << endl;
        return -1;
    }
  }
  else{
    cout << "You have to use -resize flag." << endl;
  }

	Object.findGoodMatches(images, direction);

}


 
