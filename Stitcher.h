#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
class Image {
protected:
	vector<Mat> images;
public:
	Image();
	~Image();
	vector<string> setImagesPath();
	void readImages();
	void showImages();
	vector<Mat> getImages();
};

class Points : public Image{
	int imageRank=0;
	vector<Point2f> perspectivePoints;
	vector<Mat> perspectiveImages;
public:
	Points();
	~Points();
	void setImageRank(int Rank);
	int getImageRank();
	vector<int> getPoints(Mat img);
	void findPerspectivePoints();
	vector<Mat> getPerspectiveImage();
};

class Points {
	int imageRank = 0;
	vector<Point2f> perspectivePoints;
	vector<Mat> perspectiveImages;
public:
	Points();
	~Points();
	void setImageRank(int Rank);
	int getImageRank();
	vector<int> getPoints(Mat img);
	void findPerspectivePoints();
	vector<Mat> getPerspectiveImage();
};*/

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
	vector<int> getPoints(Mat img);
	Rect getCropPointsHorizontal(vector<int> pointsFirst, vector<int> pointsSecond);
	Rect getCropPointsVertical(vector<int> pointsFirst, vector<int> pointsSecond);
	void createPanoramicImage(int j, vector<Mat>& images, string direction);
};

/*
class ImageStitcher {
	Points imageObject;
	bool perspective = false;
	vector<Mat> Images;
	vector<Mat> imageDes;
	vector<Mat> imageGray;
	vector<vector<KeyPoint>> imageKeypoint;
	vector<vector<DMatch>> GoodMatches;
	vector<Mat> HomographyMatrix;
public:
	ImageStitcher();
	~ImageStitcher();
	void setPerspective(bool Perspective);
	bool getPerspective();
	void findKeypointsDescriptors();
	void findGoodMatches();
	void findHomographyMatrix();
	void createPanoramicImage();
};
*/