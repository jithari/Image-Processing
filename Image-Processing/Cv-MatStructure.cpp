#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!!" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	printf("height: %d, width: %d, widthstep: %d, channels: %d\n", height, width, widthstep, ch);

	img.at<uchar>(10, 10) = 255;
	//B.at<Vec3b>(10,10)[0] = 

	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat copy(height, width, CV_8UC3, Scalar(0, 0, 0));
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			copy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}
	int hist[256];

	//initialize "0" to all array values
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	//count one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)] + 1;

		}
	}

	for (int i = 0; i < 256; i++) {
		cout << i << " : " << hist[i] << endl;
	}

	//create an image to display an histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0));

	//find max number of pixels
	int max = hist[0];
	for (int i = 0; i < 256; i++) {
		if (max < hist[i]) {
			max = hist[i];
		}
	}

	//normalize the histogram between 0 and histogram height
	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max) * histImage.rows;
	}

	//draw the lines of histogram.
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - hist[i]), Scalar(255), 1, 8, 0);
	}
	//line(histImage, Point pt1, Point pt2, color, thickness, lineType, shift);

	namedWindow("Image");
	imshow("Image", img);

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Copy");
	imshow("Copy", copy);

	namedWindow("Histogram");
	imshow("Histogram", histImage);

	waitKey(0);
	return 0;

}
