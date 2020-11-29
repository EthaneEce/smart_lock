CCP=g++
CCC=gcc
CFLAGS=-I/usr/local/include/
LFLAGS=-L/usr/local/lib/ 
CV_FLAGS= -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect -lopencv_photo -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_face
PI_CAM_FLAGS = -lraspicam -lraspicam_cv
PTHREAD_FLAGS = -lpthread
WIRING_PI_FLAGS = -lwiringPi


all: face_reco train ultrasonic smart_lock

face_reco: ./features/face_reco.cpp
	$(CCP) $(CFLAGS) $(LFLAGS) -o ./features/face_reco ./features/face_reco.cpp $(PI_CAM_FLAGS) $(CV_FLAGS) $(PTHREAD_FLAGS)

train: ./features/train.cpp
	$(CCP) $(CFLAGS) $(LFLAGS) -o ./features/train ./features/train.cpp $(CV_FLAGS)

ultrasonic: ./features/ultrasonic.c
	$(CCC) $(CFLAGS) $(LFLAGS) -o ./features/ultrasonic ./features/ultrasonic.c $(WIRING_PI_FLAGS)
	
smart_lock: smart_lock.c
	$(CCC) $(CFLAGS) $(LFLAGS) -o smart_lock smart_lock.c $(WIRING_PI_FLAGS) $(PTHREAD_FLAGS) -lpython3.7m
