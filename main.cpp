#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


int main()
{
  const int MAX = 1e4+79;
  Mat image_to_encrypt ;
  double u = 3.94;
  vector< pair <double,int > > x;
  Vec < unsigned char, 3 > pixel; ///OpenCV Syntax, it's like Vec3B


  image_to_encrypt = imread("pinguini.png"); /// Insert here name of image u want to encrypt

  if ( !image_to_encrypt.data )
  {
    cout << "No image" << endl;
    return -1;
  }

  x.push_back( make_pair(0.4,0) );

  double temporar_col;
    for ( int i = 1; i <= image_to_encrypt.rows; ++i ){
      temporar_col= u*x[i-1].first* (1-x[i-1].first);
      x.push_back( make_pair(temporar_col,i) );
  }
  sort(x.begin(), x.end());

  imshow("Image",image_to_encrypt);
  /**

 BGR;
 image_to_encrypt.at<Vec3b>)(row,col)[0] blue
 image_to_encrypt.at<Vec3b>)(row,col)[1] green
 image_to_encrypt.at<Vec3b>)(row,col)[2] red

 */

 int N,i=0;
 for(int row = 0; row < image_to_encrypt.rows; ++row)
 {
    for(int col = 0; col < image_to_encrypt.cols; ++col)
    {
      if(i > image_to_encrypt.rows)
        i=1;
      N = x[i].first*MAX;
      N = N % 255;
      /// XOR Assignment
      image_to_encrypt.at<Vec3b>(row,col)[0] = image_to_encrypt.at<Vec3b>(row,col)[0]^N;
      image_to_encrypt.at<Vec3b>(row,col)[1] = image_to_encrypt.at<Vec3b>(row,col)[1]^N;
      image_to_encrypt.at<Vec3b>(row,col)[2] = image_to_encrypt.at<Vec3b>(row,col)[2]^N;

      i++;
    }
}

imshow("Image Encrypted", image_to_encrypt);

 i = 0;
 for(int row = 0; row < image_to_encrypt.rows; ++row)
 {
    for(int col = 0; col < image_to_encrypt.cols; ++col)
    {
      if(i > image_to_encrypt.rows)
        i=1;
      N = x[i].first*MAX;
      N = N % 255;

      image_to_encrypt.at<Vec3b>(row,col)[0] = image_to_encrypt.at<Vec3b>(row,col)[0]^N;
      image_to_encrypt.at<Vec3b>(row,col)[1] = image_to_encrypt.at<Vec3b>(row,col)[1]^N;
      image_to_encrypt.at<Vec3b>(row,col)[2] = image_to_encrypt.at<Vec3b>(row,col)[2]^N;

      i++;
    }
}
imshow("Image dec", image_to_encrypt);
waitKey(0);


  return 0;
}
