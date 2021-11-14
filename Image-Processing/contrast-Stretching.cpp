#include "opencv2/opencv.hpp"

#include "opencv2/highgui.hpp"

#include "opencv2/core.hpp"



using namespace cv;

using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], 1);



	if (!img.data) {

		cout << "Could not find the image!" << endl;

		return -1;

	}



	int height = img.rows;

	int width = img.cols;

	int widthstep = img.step;

	int ch = img.channels();





	Mat gray(height, width, CV_8UC1, Scalar(0));

	cvtColor(img, gray, COLOR_BGR2GRAY);



	Mat new_image = gray.clone();



	int v;

	int output;



	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			v = (int)gray.at<uchar>(y, x);

			if (v >= 0 && v <= 105) {

				output = int((5 / 105) * v);

			}

			else if (v > 105 && v <= 240) {

				output = int((245 / 135) * (v - 105) + 5);

			}

			else if (v > 240 && v <= 255) {

				output = int((5 / 15) * (v - 240) + 250);

			}

			new_image.at<uchar>(y, x) = (uchar)output;

		}

	}



	namedWindow("Image");

	imshow("Image", img);

	namedWindow("Gray");

	imshow("Gray", gray);

	namedWindow("New Image");

	imshow("New Image", new_image);



	waitKey(0);

	return 0;

}