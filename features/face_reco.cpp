
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

#include "../lib/pthread.h"
#include <thread>
#include <unistd.h>

using namespace cv;
using namespace cv::face;
using namespace std;

int z = 0, f = 0;
string bouf="0";

void testStart(){
    for(;;){
    ifstream myfile("readUlt.txt");
    getline(myfile,bouf);
    myfile.close();
    if(bouf=="1"){
        sleep(10);
        bouf = "0";
        string const nomFichier("resReco.txt");
    ofstream monFlux(nomFichier.c_str());

    cout << "c fini maggle" << endl;
    if (z > f)
    {
        cout << "qqun a été reconnu" << endl;
        cout << "qqun est sortie: " << z << endl;
        monFlux << "1" << endl;
        z=0;
        f=0;
    }
    else
    {
        cout << "personne a été reconnu" << endl;
        cout << "inconnu est sortie: " << f << endl;
        monFlux << "0" << endl;
        z=0;
        f=0;
    }
    }
  }

}


void stopPredi()
{
    string const nomFichier("resReco.txt");
    ofstream monFlux(nomFichier.c_str());

    cout << "c fini maggle" << endl;
    if (z > f)
    {
        cout << "qqun a été reconnu" << endl;
        cout << "qqun est sortie: " << z << endl;
        monFlux << "1" << endl;
    }
    else
    {
        cout << "personne a été reconnu" << endl;
        cout << "inconnu est sortie: " << f << endl;
        monFlux << "0" << endl;
    }

    
}

int main()
{
    std::thread t1(testStart); 

    raspicam::RaspiCam_Cv Camera;

    Camera.set(CAP_PROP_FRAME_WIDTH, 320);
    Camera.set(CAP_PROP_FRAME_HEIGHT, 240);
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);

    map<int, string> labels;

    ifstream infile("./recognizer/labels.txt");

    int a;
    string b;
    while (infile >> a >> b)
    {
        labels[a] = b;
        cout << labels[a] << endl;
    }

    if (!Camera.open())
    {
        cerr << "Error opening the camera" << endl;
        return -1;
    }

    CascadeClassifier classifier;
    classifier.load("./cascades/lbpcascade_frontalface.xml");

    Ptr<LBPHFaceRecognizer> recognizer = createLBPHFaceRecognizer(2, 2, 7, 7, 17);
    recognizer->load("./recognizer/embeddings.xml");

    Mat windowFrame;
    namedWindow("edges", 1);
    int numframes = 0;
    time_t timer_begin, timer_end;
    time(&timer_begin);

    for(;;){
        if(bouf=="1"){
             Mat frame;
        Camera.grab();
        Camera.retrieve(frame);
        cvtColor(frame, windowFrame, CV_BGR2GRAY);
        vector<Rect> faces;
        classifier.detectMultiScale(frame, faces, 1.1, 3);
        for (size_t i = 0; i < faces.size(); i++)
        {
            rectangle(frame, faces[i], Scalar(0, 255, 0));
            Mat face = windowFrame(faces[i]);
            double confidence = 0.0;
            int predicted = recognizer->predict(face);
            cout << labels[predicted] << endl;
            recognizer->predict(face, predicted, confidence);
            if (labels.find(predicted) == labels.end() || confidence > 30)
            {
                putText(frame, "Unknown", Point(faces[i].x, faces[i].y - 5), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 1);
            }
            else
            {
                putText(frame, labels[predicted], Point(faces[i].x, faces[i].y - 5), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 1);
            }
            cout << "ID: " << predicted << " | Confidence: " << confidence << endl;
            if (predicted == -1)
            {
                f++;
            }else{
                z++;
            }
        }
        imshow("edges", frame);
        waitKey(30);
        numframes++;

        //if(waitKey(30) >=0) break;
        }
    }

    Camera.release();
    time(&timer_end);

    return 0;
}
