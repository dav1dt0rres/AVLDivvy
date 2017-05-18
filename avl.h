
/*avl.h*/

// make sure this header file is #include exactly once:
#pragma once
 
 
//
// AVL type declarations:
//
typedef int  AVLKey;
 
typedef struct STATION
{
  int  StationID;
  char * Name;
  double latitude;
double longitude;
int dpcapacity;
 char* online_date;
 int tripcount;
} STATION;
 
typedef struct TRIP
{
char *starttime;				
char *stoptime;	
int tripduration;
int bikeid;
int from_station_id;
char *from_station_name;
int to_station_id;
char *to_station_name;
 int  TripID;

 
} TRIP;
 
typedef struct BIKE
{
  int  BikeID;
  int  tripcount;
 
} BIKE;
 
enum UNIONTYPE
{
  STATIONTYPE,
  TRIPTYPE,
  BIKETYPE
};
 
typedef struct AVLValue
{
  enum UNIONTYPE Type;  // Station, Trip, or Bike:
  union
  {
    STATION  Station;   // union => only ONE of these is stored:
    TRIP     Trip;
    BIKE     Bike;
  };
} AVLValue;
 
typedef struct AVLNode
{
  AVLKey    Key;
  AVLValue  Value;
  struct AVLNode  *Left;
  struct AVLNode  *Right;
  int       Height;
} AVLNode;
 
typedef struct AVL
{
  AVLNode *Root;
  int      Count;
} AVL;
 
typedef struct Array{
	double distance;
	int Key;
}Array;
 
//
// AVL API: function prototypes
//
AVL *AVLCreate();
void AVLFree(AVL *tree);
 
int      AVLCompareKeys(AVLKey key1, AVLKey key2);
int AVLSearchCopy_Bike(AVLNode* Node, AVLNode* New_node);
AVLNode* AVLSearchCopy_stations(AVLNode* Node,AVLNode* New_node);
AVLNode * _AVLInsert(AVLNode *Node,AVLNode* New_node);
AVL *AVLInsert(AVL *tree, AVLNode*New_node); 
 int AVLHeight(AVL *tree);
 int AVLSearch(AVLNode* Node, int key);
 AVLNode* _AVLSearch(AVLNode* Node, int key);
int  AVLCount(AVL *tree);
int max(int x,int y);
int Height(AVLNode * node);
void AVLPrintPreorder(AVL *tree, void(*pf)(AVLNode*));
void _AVLPrintPreorder(AVLNode *root, void(*pf)(AVLNode*));
double distBetween2Points(double lat1, double long1, double lat2, double long2);
Array * _Distance_function(AVLNode* root,double longt, double lat, Array *array,int *index);
void Distance_function(AVL* tree,double longt, double lat, double distance);
Array* _route_function(AVLNode*root,AVLNode* match, Array *Starting_array,int *index);
int Route_Function(AVL*tree,AVL* Stations_tree, int tripID,double Distance);
int _final_recursive(AVLNode* root,AVLNode* Stations, AVLNode* starting, AVLNode* destination,double Distance);
double _latitude(AVLNode *Node,int ID);
double _longitude(AVLNode* Node,int ID);

