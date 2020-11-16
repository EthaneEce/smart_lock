#ifndef MACLASSE_H 
#define MACLASSE_H 
  
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <raspicam/raspicam_cv.h>

#include <iostream>
#include <ctime>
#include <fstream>
#include <map>
#include <csignal>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void stopPredi(int signum);
int start_reco();

#endif