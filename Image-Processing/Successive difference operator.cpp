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



	int r = img.at<Vec3b>(1, 1)[0];

	int g = img.at<Vec3b>(1, 1)[1];

	int b = img.at<Vec3b>(1, 1)[2];



	/*cout << r << endl;

	cout << g << endl;

	cout << b << endl;*/

	cout << "r=" << r << "\ng=" << g << "\nb=" << b << endl;



	Mat gr(height, width, CV_8UC1, Scalar(0));

	cvtColor(img, gr, COLOR_BGR2GRAY);



	Mat output = gr.clone();


	//	Mat output2(height, width, CV_8UC3, Scalar(255, 0, 0));
	Mat output2 = gr.clone();
	Mat output3 = gr.clone();



	int gx = 0;

	int gy = 0;

	int G = 0;



	//int T = atoi(argv[2]);



	/*

	//Successive Difference Operator

	for (int i = 0; i < height - 1; i++) {

		for (int j = 0; j < width - 1; j++) {

			gx = gr.at<uchar>(i, j) + (-gr.at<uchar>(i, j + 1));

			gy = gr.at<uchar>(i, j) + (-gr.at<uchar>(i + 1, j));

			G = abs(gx) + abs(gy);



			if (G >= T)

				output.at<uchar>(i, j) = 255;

			else

				output.at<uchar>(i, j) = 0;

		}

	}*/

	/*

	//Sobel Operator

	for (int i = 1; i < height - 1; i++) {

		for (int j = 1; j < width - 1; j++) {



			gx = -gr.at<uchar>(i - 1, j - 1) + -2 * gr.at<uchar>(i - 1, j) + -1 * gr.at<uchar>(i - 1, j + 1) + 1 * gr.at<uchar>(i + 1, j - 1) + 2 * gr.at<uchar>(i + 1, j) + 1 * gr.at<uchar>(i + 1, j + 1);

			gy = -gr.at<uchar>(i - 1, j - 1) + -2 * gr.at<uchar>(i, j - 1) - gr.at<uchar>(i + 1, j - 1) + gr.at<uchar>(i - 1, j + 1) + 2 * gr.at<uchar>(i, j + 1) + 1 * gr.at<uchar>(i + 1, j + 1);

			G = abs(gx) + abs(gy);



			if (G >= T) {

				//output.at<uchar>(i, j) = 255;

				output2.at<Vec3b>(i, j) = Vec3b(0, 0, 255);

			}

			else {

				//output.at<uchar>(i, j) = 0;

				output2.at<Vec3b>(i, j) = Vec3b(255, 0, 0);

			}



		}

	}
	*/

	/*
	 __________________________        __________________________                  ____________________
	|i-1,y-1 | i-1,j | i-1,j+1 |      |   0    |  -1   |    0    |                |  -1  |  -1  |  -1  |
	|________|_______|_________|      |________|_______|_________|                |______|______|______|
	| i,j-1  |  i,j  |  i,j+1  |      |   -1   |   4   |   -1    |    or          |  -1  |   8  |  -1  |
	|________|_______|_________|      |________|_______|_________|                |______|______|______|
	|i+1,j-1 | i+1,j | i+1,j+1 |      |   0    |  -1   |    0    |                |  -1  |  -1  |  -1  |
	|________|_______|_________|      |________|_______|_________|                |______|______|______|


	*/


	for (int i = 1; i < height - 1; i++) {

		for (int j = 1; j < width - 1; j++) {


			G = -gr.at<uchar>(i - 1, j) + -gr.at<uchar>(i, j - 1) + 4 * gr.at<uchar>(i, j) + -gr.at<uchar>(i, j + 1) + -gr.at<uchar>(i + 1, j);

			//	G = -gr.at<uchar>(i - 1, j) + -gr.at<uchar>(i, j - 1) + 8 * gr.at<uchar>(i, j) + -gr.at<uchar>(i, j + 1) + -gr.at<uchar>(i + 1, j) + -gr.at<uchar>(i - 1, j-1)
			+-gr.at<uchar>(i - 1, j + 1) + -gr.at<uchar>(i + 1, j - 1) + -gr.at<uchar>(i + 1, j + 1);




			if (G < 0) {

				output2.at<uchar>(i, j) = 0;


			}

			else {

				output2.at<uchar>(i, j) = 255;

				//output2.at<Vec3b>(i, j) = Vec3b(0, 0, 0);

			}



		}

	}
	/*for (int y = 0; y < height - 1; y++) {

		for (int x = 0; x < width - 1; x++) {


				G = -gr.at<uchar>( x, y-1) + -gr.at<uchar>(x-1, y) + 4 * gr.at<uchar>(x, y) + -gr.at<uchar>(x+1, y) +  -gr.at<uchar>(x ,y+1);

			//G = -gr.at<uchar>(i - 1, j) + -gr.at<uchar>(i, j - 1) + 8 * gr.at<uchar>(i, j) + -gr.at<uchar>(i, j + 1) + -gr.at<uchar>(i + 1, j) + -gr.at<uchar>(i - 1, j - 1)
				//+ -gr.at<uchar>(i - 1, j + 1) + -gr.at<uchar>(i + 1, j - 1) + -gr.at<uchar>(i + 1, j + 1);

			if (G == 0) {

				output2.at<uchar>(x, y) = 0;


			}

			else {

				output2.at<uchar>(x, y) = 255;

				//output2.at<Vec3b>(i, j) = Vec3b(0, 0, 0);

			}



		}

	}*/
	// Declare the variables we are going to use
	Mat src, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	Mat abs_dst;
	Laplacian(output3, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	// converting back to CV_8U
	convertScaleAbs(dst, abs_dst);


	namedWindow("Gray Image");

	imshow("Gray Image", gr);

	//namedWindow("Output Image");

	//imshow("Output Image", output);

	namedWindow("Output Image2");

	imshow("Output Image2", output2);

	namedWindow("Output Image3");

	imshow("Output Image3", abs_dst);

	waitKey(0);

	return 0;

}