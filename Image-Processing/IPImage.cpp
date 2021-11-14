#include "cv.h" //main opencv header
#include "highgui.h" //GUI header

int main(int argc, char* argv[])
{
	IplImage* img;

	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);



	if (!img) {

		printf("Could not load image file %s\n", argv[1]);

		return -1;

	}



	int width = img->width;

	int height = img->height;

	int widthstep = img->widthStep;

	int channels = img->nChannels;



	printf("Width: %d\n", width);

	printf("Height: %d\n", height);

	printf("Width Step: %d\n", widthstep);

	printf("No of channels: %d\n", channels);

	uchar* data = (uchar*)img->imageData;



	int i = 100; //y axis

	int j = 100; //x axis



	int b = data[i * widthstep + j * channels];

	int g = data[i * widthstep + j * channels + 1];

	int r = data[i * widthstep + j * channels + 2];



	printf("Blue: %d\n", b);

	printf("Green: %d\n", g);

	printf("Red: %d\n", r);

	data[i * widthstep + j * channels] = 255;

	data[i * widthstep + j * channels + 1] = 255;

	data[i * widthstep + j * channels + 2] = 255;

	for (int a = 0; a <= 100; a++) {

		for (int b = 0; b <= 100; b++) {

			data[a * widthstep + b * channels] = 0;

			data[a * widthstep + b * channels + 1] = 0;

			data[a * widthstep + b * channels + 2] = 0;

		}

	}

	IplImage* gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	uchar* graydata = (uchar*)gray->imageData;

	int grayWS = gray->widthStep;

	int grayCh = gray->nChannels;

	for (int a = 0; a < height; a++) {

		for (int b = 0; b < width; b++) {

			graydata[a * grayWS + b * grayCh] = data[a * widthstep + b * channels] * 0.1140 + data[a * widthstep + b * channels + 1] * 0.5870 + data[a * widthstep + b * channels + 2] * 0.2989;

		}

	}

	for (int a = 0; a < height; a++) {

		for (int b = 0; b < width; b++) {

			if (graydata[a * grayWS + b * grayCh] > 150)

				graydata[a * grayWS + b * grayCh] = 255;

			else

				graydata[a * grayWS + b * grayCh] = 0;

		}

	}

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			data[i * widthstep + j * channels] = 255 - data[i * widthstep + j * channels];

			data[i * widthstep + j * channels + 1] = 255 - data[i * widthstep + j * channels + 1];

			data[i * widthstep + j * channels + 2] = 255 - data[i * widthstep + j * channels + 2];

		}

	}

	IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);



	uchar* dataB = (uchar*)blue->imageData;

	uchar* dataG = (uchar*)green->imageData;

	uchar* dataR = (uchar*)red->imageData;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			dataB[i * widthstep + j * channels] = data[i * widthstep + j * channels];

			dataB[i * widthstep + j * channels + 1] = 0;

			dataB[i * widthstep + j * channels + 2] = 0;



			dataG[i * widthstep + j * channels] = 0;

			dataG[i * widthstep + j * channels + 1] = data[i * widthstep + j * channels + 1];

			dataG[i * widthstep + j * channels + 2] = 0;



			dataR[i * widthstep + j * channels] = 0;

			dataR[i * widthstep + j * channels + 1] = 0;

			dataR[i * widthstep + j * channels + 2] = data[i * widthstep + j * channels + 2];

		}

	}

	cvNamedWindow("Image");

	cvShowImage("Image", img);

	cvNamedWindow("Gray");

	cvShowImage("Gray", gray);

	cvNamedWindow("Blue");

	cvShowImage("Blue", blue);

	cvNamedWindow("Green");

	cvShowImage("Green", green);

	cvNamedWindow("Red");

	cvShowImage("Red", red);

	cvWaitKey(0);

	cvDestroyAllWindows();

	return 0;

}
