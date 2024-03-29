#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <time.h>

using namespace std;
using namespace cv;
using namespace cv::gpu;

CascadeClassifier_GPU cascade_gpu;
string faces_source = "/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

int main(int argc, char **argv) {


  try{

      clock_t start, end;
      start = clock();
      if(!cascade_gpu.load(faces_source)){
        cout << "Error : No se pudo cargar el archivo xml" << endl;
        return -1;
      }
      char *imageName = argv[1];
      GpuMat faces;

      //Cargando la imagen
      Mat src_host = imread(imageName, 1);
      GpuMat dst, src, gray;
      if(argc != 2 || !src_host.data){
        cout << "No Image Data" << endl;
        return -1;
      }

      //Copiando imagen del host a la gpu
      src.upload(src_host);

      //convirtiendo a escala de grises en la gpu
      cv::gpu::cvtColor(src, gray, CV_BGR2GRAY);
      cv::gpu::equalizeHist(gray, gray);

      //haciendo la detección facial en la gpu
      int num_faces = cascade_gpu.detectMultiScale(gray, faces, 1.2, 3);


      Mat obj_host;
     
      faces.colRange(0, num_faces).download(obj_host);
      Rect *cfaces = obj_host.ptr<Rect>();
      

      // recuperando las caras y dibujando los rectangulos
      for(int i = 0; i < num_faces; ++i) {
         Point pt1 = cfaces[i].tl();
         Size sz = cfaces[i].size();
         Point pt2(pt1.x+sz.width, pt1.y+sz.height);
         rectangle(src_host, pt1, pt2, CV_RGB(0, 255, 0));
       }
         
       end = clock();

       //mostrando el tiempo
       printf("Tiempo GPU: %f\n",(double)(end - start)/CLOCKS_PER_SEC);

       //Mostrando el resultado
       /*imshow("Detection_GPU",src_host);
       waitKey();*/

     }

     catch(const Exception& ex){
       cout << "Error: " << ex.what() << endl;
     }
  return 0;
}
