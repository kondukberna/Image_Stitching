#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
class ImageStitcher {
	Mat firstImageDes, secondImageDes;
	Mat firstImageGray, secondImageGray;
	vector<KeyPoint> firstImageKP, secondImageKP;
	vector<DMatch> GoodMatches;
	Mat HomographyMatrix;
public:
	ImageStitcher();
	~ImageStitcher();
	void findKeypointsDescriptors(int i, vector<Mat>& images);
	void findGoodMatches(vector<Mat>& images, string direction);
	void findHomographyMatrix();
	vector<int> getCornerPoints(Mat img);
	Rect getCropPointsHorizontal(vector<int> pointsFirst, vector<int> pointsSecond);
	Rect getCropPointsVertical(vector<int> pointsFirst, vector<int> pointsSecond);
	void createPanoramicImage(int j, vector<Mat>& images, string direction);
};
