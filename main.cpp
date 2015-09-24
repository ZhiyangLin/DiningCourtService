#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "sql.h"
#include "detector.h"
using namespace std;

#define DEBUG

int main(int argc, char * argv[]) {
  Database *database = new Database();
  delete database;
//return 0;
  double thresholdLow = 0.1;
  double thresholdHigh = 0.3;
  Detector * d = new Detector(thresholdLow, thresholdHigh);
  delete d;

  return 0;
}
#if 0
void detectAndDisplay( Mat frame )
{
   

  /* if(framecount%10==0){
        count_in(sensor_id,3);
       printf("framecount:%d framecount%10:%d",framecount,framecount%10);
        }*/
    int detect_profile=0;//profile not detected
	std::vector<Rect> faces;
    std::vector<Rect> face_group;
    if(framecount!=0){
	
        framecount++;
           }
    totalFrame++;
    if(!face_group.empty()){
        printf("empty vecotr!\n");
        face_group.clear();
    }
	// Detect faces
    resize(frame,frame,Size(),0.4,0.4,INTER_LINEAR);
    //frame size 192*256
   
    //     GaussianBlur( frame, frame, Size(9, 9), 2, 2 );
      cvtColor( frame, frame, CV_BGR2GRAY );
      equalizeHist( frame, frame );
	face_cascade.detectMultiScale( frame, faces, 1.15, 1, 0|CASCADE_SCALE_IMAGE,Size(20,20),Size(50,50));
    
	for ( size_t i = 0; i < faces.size(); i++ )
	{

        if(framecount==0){
            framecount++;
            row=frame.rows;
            col=frame.cols;
            printf("frame size: %d %d\n",row,col);
        }
        detection_count++;
        printf("frontal width:%d height:%d\n",faces[i].width,faces[i].height);
		Point leftTop(faces[i].x,faces[i].y);//left top coordinate of the face
		Point rightBot(faces[i].x+faces[i].width,faces[i].y+faces[i].height);//right bottom coordinate of the face
		
        face_group.push_back(faces[i]);
        
        
        //rectangle(frame,leftTop,rightBot,Scalar(255),1,8,0);// draw a rectangle around face
		
	}
    //right profile face
            face_cascade_profile.detectMultiScale( frame, faces, 1.15, 1, 0|CASCADE_SCALE_IMAGE,Size(17,30),Size(40,60));
    // face_cascade_profile.detectMultiScale( frame, faces, 1.2, 1, 0|CASCADE_SCALE_IMAGE,Size(20,20));
    for ( size_t i = 0; i < faces.size(); i++ )
	{
        if(framecount==0){
            framecount++;
            row=frame.rows;
            col=frame.cols;
            printf("frame size: %d %d\n",row,col);        }
        // printf("top x:%d top y:%d\n",faces[i].x,faces[i].y);
        printf("right profile width:%d height:%d\n",faces[i].width,faces[i].height);
        
        detection_count_profile++;
       /*faces[i].x-=20;
		Point leftTop(faces[i].x,faces[i].y);//left top coordinate of the face
		Point rightBot(faces[i].x+faces[i].width,faces[i].y+faces[i].height-45);//right bottom coordinate of the face
        detect_profile=1;*/
        
        
        
        Point leftTop(faces[i].x,faces[i].y);//left top coordinate of the face
		Point rightBot(faces[i].x+faces[i].width,faces[i].y+faces[i].height);//right bottom coordinate of the face
        face_group.push_back(Rect(Point(faces[i].x,faces[i].y),Size(faces[i].width,faces[i].height)));
		//rectangle(frame,leftTop,rightBot,Scalar(255),1,8,0);// draw a rectangle around face
		
		
	}
    //left frofile face
    if(detect_profile==0){
    flip(frame,frame,1);
        face_cascade_profile.detectMultiScale( frame, faces, 1.15, 1, 0|CASCADE_SCALE_IMAGE,Size(10,10));
     
    for ( size_t i = 0; i < faces.size(); i++ )
	{
        
        if(framecount==0){
            framecount++;
            row=frame.rows;
            col=frame.cols;
            printf("frame size: %d %d\n",row,col);        }
        
    
        // printf("top x:%d top y:%d\n",faces[i].x,faces[i].y);
        printf("left profile width:%d height:%d\n",faces[i].width,faces[i].height);
        
        detection_count_profile_flip++;
       /* faces[i].x-=20;
		Point leftTop(faces[i].x,faces[i].y);//left top coordinate of the face
		Point rightBot(faces[i].x+faces[i].width,faces[i].y+faces[i].height-45);//right bottom coordinate of the face
          face_group.push_back(Rect(Point(faces[i].x,faces[i].y),Size(faces[i].width,faces[i].height-45)));*/
		
      
		Point leftTop(faces[i].x,faces[i].y);//left top coordinate of the face
		Point rightBot(faces[i].x+faces[i].width,faces[i].y+faces[i].height);//right bottom coordinate of the face
        face_group.push_back(Rect(Point(faces[i].x,faces[i].y),Size(faces[i].width,faces[i].height)));
		//rectangle(frame,leftTop,rightBot,Scalar(255),1,8,0);// draw a rectangle around face
		
        
	}
       flip(frame,frame,1);//useless in non-graphic mode
        int group_size=face_group.size();
                for(int i=0;i<group_size;i++){
           
            face_group.push_back(face_group[i]);
           
        }
       
 line(frame, Point(130,0), Point(130,256), Scalar(255));
        groupRectangles(face_group, 1, 0.2);
        for ( size_t i = 0; i < face_group.size(); i++ ){
            printf("%d %d %d %d\n",face_group[i].x,face_group[i].y,face_group[i].width,face_group[i].height);
            rectangle(frame,Point(face_group[i].x,face_group[i].y),Point(face_group[i].x+face_group[i].width,face_group[i].y+face_group[i].height),Scalar(255),1,8,0);
            if(faces[i].x<120 ) {
              //  printf("in!\n");
                if(flag==1&&faces[i].x<120 ) {
                //    printf("1 Person came in!\n");
                    //peoplecount++;
                   // count_in(sensor_id,1);
                    flag=0;
                }
            } else flag=1;
            
        }
        

        
    
    
    
    }
}
#endif
