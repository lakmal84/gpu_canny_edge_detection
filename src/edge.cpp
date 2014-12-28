//
//  edge.cpp
//  TestOpenCV
//
//  Created by Lakmal on 20/12/14.
//  Copyright (c) 2014 NTU. All rights reserved.
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <stdio.h>

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
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    GpuMat edges;
    struct timespec start, end;	
    namedWindow("edges",1);
    for(int i=0; i<20; i++)
    {
	//clock_gettime(CLOCK_REALTIME, &start); /* mark start time */
        Mat frame;
	GpuMat gpu_frame;
        cap >> frame; // get a new frame from camera
	gpu_frame.upload(frame);
        clock_gettime(CLOCK_REALTIME, &start); /* mark start time */
	gpu::cvtColor(gpu_frame, edges, CV_BGR2GRAY);
        gpu::GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        gpu::Canny(edges, edges, 0, 30, 3);
	clock_gettime(CLOCK_REALTIME, &end);
	Mat dst_host(edges);
        imshow("edges", dst_host);
	//clock_gettime(CLOCK_REALTIME, &end);
	printf("Latency = %lu.%lu\n", diff(start, end).tv_sec, diff(start, end).tv_nsec);
        if(waitKey(200) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
