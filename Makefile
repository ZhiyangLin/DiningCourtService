CC=g++
CFLAGS_OPENCV=-I/usr/include/opencv
LDFLAGS_OPENCV=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
CFLAGS_PI=-I/home/pi/git/robidouille/raspicam_cv
LDFLAGS_PI=-L/home/pi/git/robidouille/raspicam_cv -lraspicamcv -L/home/pi/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host
CFLAGS_MYSQL=-I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -g
LDFLAGS_MYSQL=-L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl
CFLAGS=-w -std=c++0x $(CFLAGS_OPENCV) $(CFLAGS_PI) $(CFLAGS_MYSQL)
LDFLAGS=$(LDFLAGS_OPENCV) $(LDFLAGS_PI) $(LDFLAGS_MYSQL)

CPP_FILES:=$(wildcard *.cpp)
OBJS=objs
OBJ_FILES:=$(addprefix $(OBJS)/, $(notdir $(CPP_FILES:.cpp=.o)))
TARGET=RaspiCamTest

all: $(TARGET)
	@echo All files are up-to-date.

$(TARGET): $(OBJ_FILES)
	@echo Linking object files...
	$(CC) -o $(TARGET) $(OBJ_FILES) $(CFLAGS) $(LDFLAGS)

$(OBJS)/%.o: %.cpp %.h
	@echo Compiling $@...
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	@echo Cleaning object files...
	rm -f $(OBJS)/*.o $(TARGETS)

run:
	./RaspiCamTest
