#include "Stitcher.h"
#include "Stitcher.h"

ImageStitcher::ImageStitcher() {
	cout << "Image Stitcher Constructed." << endl;
}

ImageStitcher::~ImageStitcher() {
	cout << "Image Stitcher Deconstructed." << endl;
}

void ImageStitcher::findKeypointsDescriptors(int i, vector<Mat>& Images) {

	Ptr<SIFT> Sift = SIFT::create();

	Mat emptyImage;
	vector<KeyPoint> emptyKeypoint;


	cvtColor(Images[i], firstImageGray, COLOR_BGR2GRAY);
	Sift->detectAndCompute(firstImageGray, noArray(), firstImageKP, firstImageDes);
	cvtColor(Images[i + 1], secondImageGray, COLOR_BGR2GRAY);
	Sift->detectAndCompute(secondImageGray, noArray(), secondImageKP, secondImageDes);

}

void ImageStitcher::findGoodMatches(vector<Mat>& Images, string direction)
{

	for (int i = 0; i < Images.size() - 1; i++) {

		findKeypointsDescriptors(i, Images);

		BFMatcher BF_Matcher;

		vector<vector<DMatch>> InitialMatches;

		BF_Matcher.knnMatch(firstImageDes, secondImageDes, InitialMatches, 2);


		for (int i = 0; i < InitialMatches.size(); ++i)
		{
			if (InitialMatches[i][0].distance < 0.5 * InitialMatches[i][1].distance)
			{

				GoodMatches.push_back(InitialMatches[i][0]);
			}
		}
		std::cout << "number of Matched Feature: " << GoodMatches.size() << std::endl;

		vector<Mat> matchImgRefined;

		Mat emptyMatchImgRefined;

		drawMatches(firstImageGray, firstImageKP, secondImageGray, secondImageKP, GoodMatches, emptyMatchImgRefined, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		matchImgRefined.push_back(emptyMatchImgRefined);

		cv::imwrite("matchedImage.png", emptyMatchImgRefined);

		findHomographyMatrix();
		createPanoramicImage(i, Images, direction);
		GoodMatches.clear();
		firstImageKP.clear();
		secondImageKP.clear();
		Mat empty;
		HomographyMatrix = empty;
		firstImageDes = empty;
		secondImageDes = empty;
		firstImageGray = empty;
		secondImageGray = empty;
	}
}

void ImageStitcher::findHomographyMatrix() {

	vector<Point2f> emptyPointsFirst;
	vector<Point2f> emptyPointsSecond;

	for (int i = 0; i < GoodMatches.size(); i++)
	{
		cv::DMatch Match = GoodMatches[i];
		emptyPointsFirst.push_back(firstImageKP[Match.queryIdx].pt);
		emptyPointsSecond.push_back(secondImageKP[Match.trainIdx].pt);
	}
	if (emptyPointsFirst.size() >= 4 && emptyPointsSecond.size() >= 4) {
		HomographyMatrix = findHomography(emptyPointsSecond, emptyPointsFirst, cv::RANSAC, (4.0));
	}
	else
	{
		cout << "Not enough points to compute homography. Image size can be increased." << endl;
	}
}

vector<int> ImageStitcher::getCornerPoints(Mat img) {

	vector<int>imgPoints;
	int min_y = img.rows;
	int max_x = 0;
	int max_y = 0;
	int min_x = img.cols;
	int max_2x = 0;
	int max_2y = 0;
	int min_2x = img.cols;
	int min_2y = img.rows;

	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			Vec3b pixel = img.at<Vec3b>(j, i);

			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			if (red != 0 || green != 0 || blue != 0)
			{
				if (i <= min_x && j >= max_y)
				{
					min_x = i;
					max_y = j;
				}
				if (i >= max_x && j <= min_y)
				{
					max_x = i;
					min_y = j;
				}
				if (i >= max_2x && j >= max_2y)
				{
					max_2y = j;
					max_2x = i;
				}
				if (i <= min_2x && j <= min_2y)
				{
					min_2x = i;
					min_2y = j;
				}
			}
		}
	}
	imgPoints.push_back(min_y);
	imgPoints.push_back(max_x);
	imgPoints.push_back(max_y);
	imgPoints.push_back(min_x);
	imgPoints.push_back(max_2x);
	imgPoints.push_back(max_2y);
	imgPoints.push_back(min_2x);
	imgPoints.push_back(min_2y);

	return imgPoints;
}

Rect ImageStitcher::getCropPointsHorizontal(vector<int> pointsFirst, vector<int> pointsSecond) {

	int result_x1, result_x2, result_y1, result_y2;

	if (pointsFirst[6] > pointsFirst[3])
	{
		result_x1 = pointsFirst[6];
	}
	else
	{
		result_x1 = pointsFirst[3];
	}

	if (pointsFirst[7] > pointsSecond[0])
	{
		result_y1 = pointsFirst[7];
	}
	else
	{
		result_y1 = pointsSecond[0];
	}

	if (pointsSecond[1] < pointsSecond[4])
	{
		result_x2 = pointsSecond[1];
	}
	else
	{
		result_x2 = pointsSecond[4];
	}

	if (pointsFirst[2] < pointsSecond[5])
	{
		result_y2 = pointsFirst[2];
	}
	else
	{
		result_y2 = pointsSecond[5];
	}

	int width = result_x2 - result_x1;
	int height = result_y2 - result_y1;

	Rect rect(result_x1, result_y1, width, height);
	return rect;
}


Rect ImageStitcher::getCropPointsVertical(vector<int> pointsFirst, vector<int> pointsSecond) {

	int result_x1, result_x2, result_y1, result_y2;

	if (pointsFirst[6] > pointsSecond[3])
	{
		result_x1 = pointsFirst[6];
	}
	else
	{
		result_x1 = pointsSecond[3];
	}

	if (pointsFirst[7] > pointsFirst[0])
	{
		result_y1 = pointsFirst[7];
	}
	else
	{
		result_y1 = pointsFirst[0];
	}

	if (pointsFirst[1] < pointsSecond[4])
	{
		result_x2 = pointsFirst[1];
	}
	else
	{
		result_x2 = pointsSecond[4];
	}

	if (pointsSecond[5] < pointsSecond[2])
	{
		result_y2 = pointsSecond[5];
	}
	else
	{
		result_y2 = pointsSecond[2];
	}

	int width = result_x2 - result_x1;
	int height = result_y2 - result_y1;

	Rect rect(result_x1, result_y1, width, height);
	return rect;
}

void ImageStitcher::createPanoramicImage(int j, vector<Mat>& Images, string direction) {

	Mat result;
	warpPerspective(Images[j+1], result, HomographyMatrix, Size(Images[j].cols + Images[j + 1].cols, Images[j].rows + Images[j + 1].rows));

	vector<int> rectPointsSecond = getCornerPoints(result);

	Mat half(result, Rect(0, 0, Images[j].cols, Images[j].rows));
	Images[j].copyTo(half);

	vector<int> rectPoints = getCornerPoints(result);

	if (direction == "horizontal")
	{
		Rect rect = getCropPointsHorizontal(rectPoints, rectPointsSecond);
		result = result(rect);
	}
	else if (direction == "vertical")
	{
		
		Rect rect = getCropPointsVertical(rectPoints, rectPointsSecond);
		result = result(rect);
	}

	Images[j + 1] = result;

	imwrite("StitchedImage.jpg", result);
}
