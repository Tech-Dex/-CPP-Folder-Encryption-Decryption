#include <dirent.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <cstdio>

using namespace std;
using namespace cv;

vector < string > files;


void read_files_names(){
  DIR *dir;
  struct dirent *it;
  string extension[] = {"txt", "jpg" ,"png"}; /// It works only for these files, but feel free to improve

  if ( (dir = opendir ("./ToEncryptFolder") ) != NULL ) ///Here you can change the path to another folder for scanning & modifying
  {
    while ( (it = readdir( dir )) != NULL )
    {
      if ( string(it->d_name).length() > 4)
        for ( int j = 0 ; j < 4 ; ++j)
          if ( string(it->d_name).substr(string(it->d_name).length()-3) == extension[j])
            files.push_back(string(it->d_name));
    }

    closedir (dir);
  }
  else
  cout <<"Invalid Folder";


}


void text_encrypt(string file_name){
  ifstream f( "./ToEncryptFolder/" + file_name );
  ofstream g(  "./ToEncryptFolder/clone-" + file_name );
  string file_content;

  char key[6] = {'D', 'E', 'X', 'T', 'E', 'R' }; /// XOR Key... sure you can change it

  while ( getline(f,file_content) && !f.eof() )
  {
    for ( int i = 0 ; i < file_content.size(); i++ )
    {
      file_content[i] = file_content[i] ^ key[ i % (sizeof(key)) ];
    }

    g << file_content << "\n";

  }

  remove ( ("./ToEncryptFolder/" + file_name).c_str() );
  rename ( ("./ToEncryptFolder/clone-" + file_name ).c_str() , ("./ToEncryptFolder/" + file_name).c_str() );
}


void image_encrypt (string image_name){
  int MAX = 1e4+79;
  Mat image_to_encrypt ;
  double u = 3.94;
  vector< pair <double,int > > x;
  Vec < unsigned char, 3 > pixel; ///OpenCV Syntax, it's like Vec3B


  image_to_encrypt = imread("./ToEncryptFolder/" + image_name);

  if ( !image_to_encrypt.data )
  {
    cout << "No image" << endl;
    return;
  }

  x.push_back( make_pair(0.5,0) );

  double temporar_col;
    for ( int i = 1; i <= image_to_encrypt.rows; ++i )
    {
      temporar_col= u*x[i-1].first* (1-x[i-1].first);
      x.push_back( make_pair(temporar_col,i) );
  }
  sort(x.begin(), x.end());

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

imwrite("./ToEncryptFolder/" + image_name, image_to_encrypt);

}
int main()
{
  read_files_names();

  cout << "Files below were modified: \n";
  for ( auto &it : files )
  {
    cout << it << "\n" ;
    if ( it.substr(it.length()-3) == "txt" )
      text_encrypt( it );
    else
      image_encrypt( it );
  }
}
