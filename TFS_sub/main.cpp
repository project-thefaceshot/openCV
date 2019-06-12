#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


/*String face_cascade = "C:/Program Files/OpenCV3.4.2/sources/data/haarcascades/haarcascade_frontalface_alt.xml";

CascadeClassifier face;*/


int main() {

	cout << "Hello, openCV!" << endl;
	cout << "<<< TheFaceShot >>>" << endl;


	Mat img;

	img = imread("face1.jpg", 0);

	resize(img, img, Size(30, 30));

	imshow("img", img);

	waitKey(0);

	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			cout << "img.at<uchar>(" << j << ", " << i << "): "  << img.at<uchar>(j, i) << endl;
		}
	}

	imshow("img", img);

	waitKey(0);





	/* 얼굴 영역 추출 코드 삽입 */
	/*
	if (!face.load(face_cascade)) {
		cout << "Cascade 파일 열기 실패" << endl;
		return -1;
	}

	double angle;

	Mat img;
	Mat gray;
	vector<Rect> face_pos;	//얼굴 위치 저장
	Rect rect;
	Mat faceROI;			//얼굴 영역

	Mat rot, faceROI_rot;	//회전 정보, 회전 영상
	Point2f point_center;	//회전 중심점

	String input_name, output_name;	//영상 풀네임
	String input_path, output_path, output_inv_path;	//영상 경로
	String emotion;
	String extension;	//영상 확장자

	//데이터 증대 영상 경로
	String output_5d_path, output_10d_path, output_15d_path;
	String output_m5d_path, output_m10d_path, output_m15d_path;

	//데이터 증대 영상 경로(반전)
	String output_5d_inv_path, output_10d_inv_path, output_15d_inv_path;
	String output_m5d_inv_path, output_m10d_inv_path, output_m15d_inv_path;

	emotion = "joy";

	input_path = "C:/Users/hansung/Desktop/ct/ppt/joy";
	output_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_gray";

	extension = ".jpg";

	output_5d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_5d";				
	output_10d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_10d";				
	output_15d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_15d";				
	output_m5d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m5d";				
	output_m10d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m10d";			
	output_m15d_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m15d";	

	output_5d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_5d_inv";		
	output_10d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_10d_inv";		
	output_15d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_15d_inv";		
	output_m5d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m5d_inv";		
	output_m10d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m10d_inv";	
	output_m15d_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_m15d_inv";	


	output_inv_path = "C:/Users/hansung/Desktop/ct/ppt/joy_face_inv (";




	input_name = input_path + extension;
	output_name = output_path + extension;

	img = imread(input_name);

	if (img.empty()) {
		cout << "이미지 파일 열기 실패" << endl;
		return -1;
	}

	//	얼굴검출

	cvtColor(img, gray, CV_RGB2GRAY);

	face.detectMultiScale(gray, face_pos, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));	//얼굴 검출

	//얼굴 영역 표시
	for (int i = 0; i < (int)face_pos.size(); i++) {
		rect = face_pos[i];
	}

	if (0 <= rect.x
		&& 0 <= rect.width
		&& rect.x + rect.width <= img.cols
		&& 0 <= rect.y
		&& 0 <= rect.height
		&& rect.y + rect.height <= img.rows) {

		faceROI = img(rect);	//얼굴 추출 영역

		cvtColor(faceROI, faceROI, CV_RGB2GRAY);

		imwrite(output_name, faceROI);

	}
	else {
		imwrite(output_name, gray);
	}

	//사이즈 조정

	resize(faceROI, faceROI, Size(96, 96), 0, 0, CV_INTER_LINEAR);

	imshow("Input Image", img);
	imshow("Output Image", faceROI);

	waitKey(0);


	//데이터 증대
		
		//imwrite(output_name, img);

		angle = 5;

		point_center.x = faceROI.cols / 2.0;
		point_center.y = faceROI.rows / 2.0;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(faceROI, faceROI_rot, rot, faceROI.size());
		output_name = output_5d_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_10d_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_15d_path + extension;
		imwrite(output_name, faceROI_rot);


		angle = -5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(faceROI, faceROI_rot, rot, faceROI.size());
		output_name = output_m5d_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_m10d_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_m15d_path + extension;
		imwrite(output_name, faceROI_rot);

		//좌우반전
		flip(faceROI, faceROI, 1);
		output_name = output_inv_path + extension;
		imwrite(output_name, faceROI);

		angle = 5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(faceROI, faceROI_rot, rot, faceROI.size());
		output_name = output_5d_inv_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_10d_inv_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_15d_inv_path + extension;
		imwrite(output_name, faceROI_rot);


		angle = -5;

		rot = getRotationMatrix2D(point_center, angle, 1.0);

		warpAffine(faceROI, faceROI_rot, rot, faceROI.size());
		output_name = output_m5d_inv_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_m10d_inv_path + extension;
		imwrite(output_name, faceROI_rot);

		warpAffine(faceROI_rot, faceROI_rot, rot, faceROI.size());
		output_name = output_m15d_inv_path + extension;
		imwrite(output_name, faceROI_rot);
		*/

}