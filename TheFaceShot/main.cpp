#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


String face_cascade = "C:/Program Files/OpenCV3.4.2/sources/data/haarcascades/haarcascade_frontalface_alt.xml";

CascadeClassifier face;


/*
//Mat�� CSV ���Ϸ� ��ȯ �� ����
void writeCSV(string filename, Mat m) {
	ofstream myfile;
	myfile.open(filename.c_str());
	myfile << format(m, Formatter::FMT_CSV) << endl;
	myfile.close();
}

//RGB�� �̿��� �Ǻλ� ���� ����
Mat getHandMaskWithBGR(const Mat& image) {
	Mat mask(image.size(), CV_8U, Scalar(0));
	const int nr = image.rows;
	const int nc = image.cols;

	for (int i = 0; i < nr; i++) {
		const Vec3b* data = image.ptr<Vec3b>(i);
		for (int j = 0; j < nc; j++) {
			uchar R = data[j][2];
			uchar G = data[j][1];
			uchar B = data[j][0];
			if (R > 95 && G > 40 && B > 20 && max(R, max(G, B)) - min(R, min(G, B)) > 15 && abs(R - G) > 15 && R > G && R > B)
				mask.at<uchar>(i, j) = 255;
		}
	}

	return mask;
}

//HSV�� �̿��� �Ǻλ� ���� ����
void detectHScolor(const Mat& image, double minHue, double maxHue, double minSat, double maxSat, Mat& mask) {
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels);

	Mat mask1;
	threshold(channels[0], mask1, maxHue, 255, THRESH_BINARY_INV);

	Mat mask2;
	threshold(channels[0], mask2, minHue, 255, THRESH_BINARY);

	Mat hueMask;
	if (minHue < maxHue)
		hueMask = mask1 & mask2;
	else
		hueMask = mask1 | mask2;

	threshold(channels[1], mask1, maxSat, 255, THRESH_BINARY_INV);
	threshold(channels[1], mask2, minSat, 255, THRESH_BINARY);

	Mat satMask;
	satMask = mask1 & mask2;

	mask = hueMask & satMask;
}
*/


int main() {

	cout << "Hello, openCV!" << endl;
	cout << "<<< TheFaceShot >>>" << endl;


	/* �� ���� ���� �ڵ� ���� */
	
	if (!face.load(face_cascade)) {
		cout << "Cascade ���� ���� ����" << endl;
		return -1;
	}

#pragma region �� ���� �ݺ�

	Mat img;
	Mat gray;
	vector<Rect> face_pos;	//�� ��ġ ����
	Rect rect;
	Mat faceROI;			//�� ����
	Mat rot, faceROI_rot;	//ȸ�� ����, ȸ�� ����
	Point2f point_center;	//ȸ�� �߽���

	String input_name, output_name;	//���� Ǯ����
	String input_path, dataAug_input_path, output_path, output_inv_path;	//���� ���
	String emotion;
	String extension;	//���� Ȯ����

	//������ ���� ���� ���
	String output_5d_path, output_10d_path, output_15d_path;
	String output_m5d_path, output_m10d_path, output_m15d_path;

	//������ ���� ���� ���(����)
	String output_5d_inv_path, output_10d_inv_path, output_15d_inv_path;
	String output_m5d_inv_path, output_m10d_inv_path, output_m15d_inv_path;

	//ppt�� ���
	String ppt_path = "C:/Users/hansung/Desktop/ct/ppt/joy.jpg";

	char img_num[5];	//���� ��ȣ
	int num = 1;		//���� ���� ��ȣ

	double angle;

	emotion = "angry";	//���� _ joy, amazing, fear, blank, sad, disgust, angry

	input_path = "InputImage/" + emotion + "/" + emotion + " (";							//	=>  "InputImage/joy/joy ("
	dataAug_input_path = "InputImage/" + emotion + "/" + emotion + "_face (";							//	=>  "InputImage/joy/joy_face ("
	output_path = "OutputImage/" + emotion + "/" + emotion + "_face (";						//	=>  "InputImage/joy/joy_face ("
	output_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_inv (";				//	=>  "InputImage/joy/joy_face_inv ("		
	extension = ").jpg";

	output_5d_path = "OutputImage/" + emotion + "/" + emotion + "_face_5d (";				//	=>  "OutputImage/joy/joy_face_5d (";
	output_10d_path = "OutputImage/" + emotion + "/" + emotion + "_face_10d (";				//	=>  "OutputImage/joy/joy_face_10d (";
	output_15d_path = "OutputImage/" + emotion + "/" + emotion + "_face_15d (";				//	=>  "OutputImage/joy/joy_face_15d (";
	output_m5d_path = "OutputImage/" + emotion + "/" + emotion + "_face_m5d (";				//	=>  "OutputImage/joy/joy_face_m5d (";
	output_m10d_path = "OutputImage/" + emotion + "/" + emotion + "_face_m10d (";			//	=>  "OutputImage/joy/joy_face_m10d (";
	output_m15d_path = "OutputImage/" + emotion + "/" + emotion + "_face_m15d (";			//	=>  "OutputImage/joy/joy_face_m15d (";

	output_5d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_5d_inv (";		//	=>  "OutputImage/joy/joy_face_5d_inv (";
	output_10d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_10d_inv (";		//	=>  "OutputImage/joy/joy_face_10d_inv (";
	output_15d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_15d_inv (";		//	=>  "OutputImage/joy/joy_face_15d_inv (";
	output_m5d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_m5d_inv (";		//	=>  "OutputImage/joy/joy_face_m5d_inv (";
	output_m10d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_m10d_inv (";	//	=>  "OutputImage/joy/joy_face_m10d_inv (";
	output_m15d_inv_path = "OutputImage/" + emotion + "/" + emotion + "_face_m15d_inv (";	//	=>  "OutputImage/joy/joy_face_m15d_inv (";

	while(true) {

		sprintf_s(img_num, "%d", num);

		//input_name = input_path + img_num + extension;
		input_name = dataAug_input_path + img_num + extension;
		output_name = output_path + img_num + extension;

		img = imread(input_name);

		if (img.empty()) {// || num > ??
			cout << "�̹��� ���� ���� ����" << endl;
			cout << "�̹��� ���� = " << num << endl;
			//break;
			return -1;
		}

		//	�󱼰���
	
		//imshow("Original_Image", img);

		cvtColor(img, gray, CV_RGB2GRAY);

		//������׷� ����ȭ
		//equalizeHist(gray, gray);

		face.detectMultiScale(gray, face_pos, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));	//�� ����


		//�� ���� ǥ��
		for (int i = 0; i < (int)face_pos.size(); i++) {

			//rectangle(img, face_pos[i], Scalar(147,20,255), 2);
			rect = face_pos[i];
		}

		if (0 <= rect.x
			&& 0 <= rect.width
			&& rect.x + rect.width <= img.cols
			&& 0 <= rect.y
			&& 0 <= rect.height
			&& rect.y + rect.height <= img.rows) {

			faceROI = img(rect);	//�� ���� ����

			cvtColor(faceROI, faceROI, CV_RGB2GRAY);

			imwrite(output_name, faceROI);

		}
		else {
			imwrite(output_name, gray);
		}


		//������ ����
		/*
		imwrite(output_name, img);

		angle = 5;

		point_center.x = img.cols / 2.0;
		point_center.y = img.rows / 2.0;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(img, faceROI_rot, rot, img.size());
		output_name = output_5d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_10d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_15d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);


		angle = -5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(img, faceROI_rot, rot, img.size());
		output_name = output_m5d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_m10d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_m15d_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		//�¿����
		flip(img, img, 1);
		output_name = output_inv_path + img_num + extension;
		imwrite(output_name, img);

		angle = 5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(img, faceROI_rot, rot, img.size());
		output_name = output_5d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_10d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_15d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);


		angle = -5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(img, faceROI_rot, rot, img.size());
		output_name = output_m5d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_m10d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, img.size());
		output_name = output_m15d_inv_path + img_num + extension;
		imwrite(output_name, faceROI_rot);
		*/

		num++;
	}

#pragma endregion

	//������ ���� �� csv ���� ����
	/*
	resize(img1, img1, Size(48, 48), 0, 0, CV_INTER_LINEAR);

	imshow("image1", img1);

	waitKey(0);

	writeCSV("face1_csv", img1);
	cout << "Mat -> CSV save" << endl;
	*/
}