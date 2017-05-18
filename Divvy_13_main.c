
/*main.cpp*/
 
//
// Divvy Bike Ride Route Analysis, using AVL trees.
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
 
#include "avl.h"
#include "HW_13.c" 
 
 

 
//
// freeAVLNodeData
//
// Works with AVLFree() to free the data inside (key, value) pairs.
//
void freeAVLNodeData(AVLKey key, AVLValue value)
{
  //
  // what we free depends on what type of value we have:
  //
  if (value.Type == STATIONTYPE)
  {
     
  }
  else if (value.Type == TRIPTYPE)
  {
 
  }
  else if (value.Type == BIKETYPE)
  {
 
  }
  else
  {
    printf("**ERROR: unexpected value type in freeAVLNodeData!\n\n");
    exit(-1);
  }
}
 
 
//
// getFileName: 
//
// Inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);
 
  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):
 
  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }
 
  fclose(infile);
 
  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);
 
  return s;
}
 
 
//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);
 
  fgets(restOfLine, rolLength, stream);
}
 
 void PrintOneNode(AVLNode *cur)
{
  printf("(%d,%d)@%d ", cur->Key, cur->Value, cur->Height);
}

///////////////////////////////////////////////////////////////////////
//
// main:
//
int main()
{
  printf("** Welcome to Divvy Route Analysis **\n");
 
  //
  // get filenames from the user/stdin:
  //
  char  cmd[64];
  char *StationsFileName = getFileName();
  char *TripsFileName = getFileName();
 
  //
  // As an example, create some trees and insert some
  // dummy (key, value) pairs:
  //
  AVL *stations = AVLCreate();
  AVL *trips = AVLCreate();
  AVL *bikes = AVLCreate();
 
  //
  // Insert a new station:
  //
  FILE *infile ;
char line[300];
int linesize = sizeof(line) / sizeof(line[0]);
char *token;
infile=fopen(StationsFileName,"r");	
fgets(line, linesize,infile);	
fgets(line, linesize,infile);
while(!feof(infile)){
	
	AVLNode *node=(AVLNode*)malloc(sizeof(AVLNode));
	node->Value.Type=STATIONTYPE;
	
	token=strtok(line,",");
	
	node->Value.Station.StationID = atoi(token);
	node->Key=atoi(token);
	token=strtok(NULL,",");
	
	token[strcspn(token, "\r\n")] = '\0';
	char *cp = token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char * str=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str,cp);
	node->Value.Station.Name=str;
	
	token=strtok(NULL,",");
	node->Value.Station.latitude=atof(token);
	
	token=strtok(NULL,",");
	
	node->Value.Station.longitude = atof(token);
	
	token=strtok(NULL,",");
	node->Value.Station.dpcapacity=atoi(token);
	
	token=strtok(NULL,",");
	token[strcspn(token, "\r\n")] = '\0';
	cp = token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char * str_1=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str_1,cp);
	node->Value.Station.online_date=str_1;
	
	node->Left=NULL;
	node->Right=NULL;
	node->Height=0;
	node->Value.Station.tripcount=0;
	printf("station id: %d\n",node->Value.Station.StationID);
	printf("Data : %s\n" ,node->Value.Station.Name) ;
	printf("latitude: %f\n",node->Value.Station.latitude);
	printf("longtitude: %f\n",node->Value.Station.longitude);
	printf("capacity: %d\n",node->Value.Station.dpcapacity);
	printf("online date : %s\n",node->Value.Station.online_date);
	
	stations=AVLInsert(stations, node);
	fgets(line, linesize,infile);	
	
}

 AVLPrintPreorder(stations, PrintOneNode);
 fclose(infile);
 //starts building tree by trip id;
 infile=fopen(TripsFileName,"r");	
fgets(line, linesize,infile);	
fgets(line, linesize,infile);
 while(!feof(infile)){
	AVLNode *trip_node=(AVLNode*)malloc(sizeof(AVLNode));
	trip_node->Value.Type=TRIPTYPE;
	
	token=strtok(line,",");
	
	trip_node->Value.Trip.TripID = atoi(token);
	trip_node->Key=atoi(token);
	token=strtok(NULL,",");
	//
	token[strcspn(token, "\r\n")] = '\0';
	char *cp = token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char * str_2=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str_2,cp);
	trip_node->Value.Trip.starttime=str_2;	
	//
	token=strtok(NULL,",");
	token[strcspn(token, "\r\n")] = '\0';
	cp=token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char*str_3=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str_3,cp);
	trip_node->Value.Trip.stoptime=str_3;
	
	AVLNode *bike_node=(AVLNode*)malloc(sizeof(AVLNode));
	bike_node->Value.Type=BIKETYPE;
	token=strtok(NULL,",");
	bike_node->Value.Bike.BikeID=atoi(token);
	bike_node->Key=atoi(token);
	bike_node->Value.Bike.tripcount=1;
	bike_node->Left=NULL;
	bike_node->Right=NULL;
	bike_node->Height=0;
	printf("bike node key %d\n",bike_node->Value.Bike.BikeID);
	printf("trip node key %d\n",trip_node->Value.Trip.TripID);
	
	trip_node->Value.Trip.bikeid=atoi(token);
	token=strtok(NULL,",");
	trip_node->Value.Trip.tripduration = atoi(token);
	
	token=strtok(NULL,",");
	trip_node->Value.Trip.from_station_id=atoi(token);

	trip_node->Left=NULL;
	trip_node->Right=NULL;
	trip_node->Height=0;
	
	token=strtok(NULL,",");
	token[strcspn(token, "\r\n")] = '\0';
	cp=token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char*str_4=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str_4,cp);
	trip_node->Value.Trip.from_station_name=str_4;
	
	token=strtok(NULL,",");
	trip_node->Value.Trip.to_station_id=atoi(token);
	
	token=strtok(NULL,",");
	cp=token;
	while(*cp == ' '|| *cp == '\t'){
		++cp;
	}
	char*str_5=(char*)malloc((strlen(cp)+1)*sizeof(char));
	strcpy(str_5,cp);
	trip_node->Value.Trip.to_station_name=str_5;
	
	
	
	bikes=AVLInsert(bikes,bike_node);
	printf("exot \n");
	trips=AVLInsert(trips,trip_node);
	
	stations->Root=AVLSearchCopy_stations(stations->Root,trip_node); 
fgets(line, linesize,infile);	 
 }
 

 AVLPrintPreorder(trips, PrintOneNode);
 printf("count %d\n",trips->Count);
 AVLPrintPreorder(bikes, PrintOneNode);
  printf("count %d\n",bikes->Count);
 fclose(infile);
  
  //
  // now interact with user:
  //

  printf("** Ready **\n");
 
  scanf("%s", cmd);
 
  while (strcmp(cmd, "exit") != 0)
  {
    if (strcmp(cmd, "stats") == 0)
    {
      //
      // Output some stats about our data structures:
      //
      printf("** Trees:\n");
 
      printf("   Stations: count = %d, height = %d\n",
        AVLCount(stations), AVLHeight(stations));
      printf("   Trips:    count = %d, height = %d\n",
        AVLCount(trips), AVLHeight(trips));
      printf("   Bikes:    count = %d, height = %d\n",
        AVLCount(bikes), AVLHeight(bikes));
    }
	else if (strcmp(cmd, "station") == 0){
		int k;
		
		scanf("%d", &k);
		AVLSearch(stations->Root,k);
		
		
		
	}
	else if (strcmp(cmd, "trip") == 0){
		int a;
		scanf("%d", &a);
		AVLSearch(trips->Root, a);
	}
	else if(strcmp(cmd, "bike") == 0){
		int b;
		scanf("%d", &b);
		AVLSearch(bikes->Root, b);
		
		
	}
	else if(strcmp(cmd, "find") == 0){
		double longt,lat,distance;
		scanf("%lf %lf %lf",&lat, &longt, &distance);
		Distance_function(stations,longt,lat,distance);
	}
	else if(strcmp(cmd, "route") == 0){
		int tripID;
		double distance;
		scanf("%d %lf" , &tripID, &distance);
		Route_Function(trips,stations,tripID,distance);
	
		
	}
    else
    {
      printf("**unknown cmd, try again...\n");
    }
 
    scanf("%s", cmd);
  }
 
   
  
  
  return 0;
}