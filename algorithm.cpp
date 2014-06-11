#include "algorithm.h"

/* add salt to image
*/
void salt(Mat &image, int n){
	for (int k = 0; k < n; ++k){
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1){
			image.at<uchar>(j, i) = 255;		
		}
		else if (image.channels() == 3){
			image.at<Vec3b>(j, i)[0] = 255;
			image.at<Vec3b>(j, i)[1] = 255;
			image.at<Vec3b>(j, i)[2] = 255;
		}
	}
}

// color reduction algorithm
void colorReduce(Mat &image, int div, bool normal, bool module, bool bitwise){
	int nl = image.rows;		// number of lines
	int nc = image.cols * image.channels();
	
	uchar mask = 0xFF << div; // for bitwise == true

	for (int j = 0; j < nl; ++j){
		// get the address of row j
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; ++i){
			// process each pixel
			if (normal){
				data[i] = data[i] / div * div + div / 2;
			}
			else if (module){
				data[i] = data[i] - data[i] % div + div / 2;		
			}
			else if (bitwise){
				data[i] = (data[i] & mask) + div / 2;
			}
			
			// end of pixel processing
		}
	}

}