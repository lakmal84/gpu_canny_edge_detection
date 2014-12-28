/**
*
* Copyright (c) 2014 Lakmal Ranasinghe
* Distributed under the GNU GPL v2. For full terms see the file docs/COPYING.
*
*/

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>

using namespace std;
using namespace cv;
using namespace cv::gpu;

timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if camera open succeeded
        return -1;

    GpuMat edges;
    struct timespec start, end;

    namedWindow("edges",1);

    while(1)
    {
        Mat src_frame;
        GpuMat gpu_frame;
        cap >> src_frame; // get a new frame from camera
        gpu_frame.upload(src_frame); // copy camera frame to GPU
        clock_gettime(CLOCK_REALTIME, &start); // mark start time 

        gpu::cvtColor(gpu_frame, edges, CV_BGR2GRAY);
        gpu::GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        gpu::Canny(edges, edges, 0, 30, 3);

        clock_gettime(CLOCK_REALTIME, &end); // mark end time
        Mat dst_frame(edges);
        imshow("edges", dst_frame);
        printf("Execution latency = %lu.%lu\n", diff(start, end).tv_sec, diff(start, end).tv_nsec);
        if(waitKey(200) >= 0) break;
    }
    return 0;
}

