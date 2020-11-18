CC=g++
CFLAGS=-I/usr/local/include/
LFLAGS=-L/usr/local/lib/ 
CV_FLAGS= -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect -lopencv_photo -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_face
PI_CAM_FLAGS = -lraspicam -lraspicam_cv
PTHREAD_FLAGS = -lpthread


all: face_reco train

face_reco: face_reco.cpp
	$(CC) $(CFLAGS) $(LFLAGS) -o face_reco face_reco.cpp $(PI_CAM_FLAGS) $(CV_FLAGS) $(PTHREAD_FLAGS)

train: train.cpp
	$(CC) $(CFLAGS) $(LFLAGS) -o train train.cpp $(CV_FLAGS)
