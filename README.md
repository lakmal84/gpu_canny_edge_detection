gpu_canny_edge_detection
========================

GPU accelerated Canny Edge Detection using OpenCV. 

Port the application to your environment:
>	$ aclocal 
>	$ autoheader 
>	$ autoconf
>	$ libtoolize --automake
>	$ automake --add-missing
>	$ ./configure

Build the radius application:
	$ make

Run the application
	$ cd bin
	$ ./edge_detection

You need a web cam to run this application. This has been tested on Nvidia Jetson TK1 platform with Logitech C270 web cam.  
