/*avl.c*/

//



#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "avl.h"


//
// AVLCreate:
//
// Dynamically creates and returns an empty AVL tree.
//
AVL *AVLCreate()
{
  AVL *tree;

  tree = (AVL *)malloc(sizeof(AVL));
  tree->Root = NULL;
  tree->Count = 0;

  return tree;
}


//
// AVLFree:
//
// Frees the memory associated with the tree: the handle and the nodes.
// The provided function pointer is called to free the memory that
// might have been allocated as part of the key or value.
//
int _AVLFree(AVLNode*Node){
	if (Node==NULL){
		
		return 0;
	}
	else if (Node->Value.Type == STATIONTYPE)
  {	free(Node->Value.Station.Name);
     free(Node->Value.Station.online_date);
	 
  }
  else if (Node->Value.Type == TRIPTYPE)
  {	free(Node->Value.Trip.from_station_name);
free(Node->Value.Trip.to_station_name);
 free(Node->Value.Trip.starttime);
 free(Node->Value.Trip.stoptime);
  }


	free(Node);
	_AVLFree(Node->Left);
	_AVLFree(Node->Right);
	
	
	return 1;
	
}
	
	

void AVLFree(AVL *tree)
{
_AVLFree(tree->Root)	;

free(tree);
 

}


//
// AVLCompareKeys: 
//
// Compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int AVLCompareKeys(AVLKey key1, AVLKey key2)
{
  if (key1 < key2)
    return -1;
  else if (key1 == key2)
    return 0;
  else
    return 1;
}
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  //
  // Reference: http://www8.nau.edu/cvm/latlon_formula.html
  //
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:
 
  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;
 
  double dist = earth_rad * acos(
    (cos(lat1_rad)*cos(long1_rad)*cos(lat2_rad)*cos(long2_rad))
    +
    (cos(lat1_rad)*sin(long1_rad)*cos(lat2_rad)*sin(long2_rad))
    +
    (sin(lat1_rad)*sin(lat2_rad))
  );
 
  return dist;
}
 

//
// AVLCount:
//
// Returns # of nodes in the tree.
//
int AVLCount(AVL *tree)
{
  return tree->Count;
}


//
// AVLHeight: 
//
// Returns the overall height of the AVL tree.
//
int AVLHeight(AVL *tree)
{
  if (tree->Root == NULL)
    return -1;
  else
    return tree->Root->Height;
}

int Height(AVLNode * node){
 
if(node==NULL){

 return -1;  
 
}
else{
      return node->Height;
}
}

int _max(int x,int y){
   return (x>y) ? x : y;
}


AVLNode *RotateLeft(AVLNode *k1)
{
 AVLNode *k2=k1->Right;
   //Rotatation occurs//
  if( k1->Right!=NULL && k1->Left!=NULL){

AVLNode *x=k2->Left;
 k1->Right=x;
 k2->Left=k1;
}

else{
   AVLNode *x=k2->Left;
    k1->Right=x;
     k2->Left=k1;
 
   
}
//Updates Heights//

int newH=1+_max(Height(k1->Left),Height(k1->Right));
  k1->Height=newH;
 newH=1+_max(Height(k2->Right),Height(k2->Left));
  
  
  k2->Height=newH;
   
  
  return k2;
}

AVLNode *RotateRight(AVLNode *k2)
{
AVLNode *k1=k2->Left;

 //Rotation occures//
 if( k1->Right!=NULL && k1->Left!=NULL){

AVLNode *y=k1->Right;
  
 k1->Right=k2;
 k2->Left=y;
 }
 else{
    AVLNode *y=k1->Right;
    k1->Right=k2;
  
     k2->Left=y;
 }
   
 //Heights are updated//

int newH=1+_max(Height(k2->Right),Height(k2->Left));
  k2->Height=newH;
newH=1+_max(Height(k1->Left),Height(k1->Right));
  k1->Height=newH;
return k1;
}

AVLNode * AVLSearchCopy_stations(AVLNode* Node,AVLNode* New_node){
	
	AVLNode* curr=Node;
	while (curr!=NULL){
		
		if (AVLCompareKeys(curr->Key,New_node->Value.Trip.from_station_id)<0){
			curr=curr->Right;

		}
		else if (AVLCompareKeys(curr->Key,New_node->Value.Trip.from_station_id)>0){
			curr=curr->Left;
			
		}
		
		else if (AVLCompareKeys(curr->Key,New_node->Value.Trip.from_station_id)==0 ) {
			++curr->Value.Station.tripcount;
		
			break;
			
		}

	}
	
	AVLNode*curr_1=Node;	
	while(curr_1!=NULL){
		
		if (AVLCompareKeys(curr_1->Key,New_node->Value.Trip.to_station_id)<0){
			curr_1=curr_1->Right;

		} 	
			
		else if (AVLCompareKeys(curr_1->Key,New_node->Value.Trip.to_station_id)>0){
			curr_1=curr_1->Left;
			
		}	
			
		else if (AVLCompareKeys(curr_1->Key,New_node->Value.Trip.to_station_id)==0){
		
			++curr_1->Value.Station.tripcount;
			
			break;
		}	
	}
	
	return Node;
}

int AVLSearchCopy_Bike(AVLNode* Node, AVLNode* New_node){
	AVLNode* curr=Node;
	while (curr!=NULL){
		if (AVLCompareKeys(curr->Key,New_node->Key)<0){
			curr=curr->Right;

		}
		else if (AVLCompareKeys(curr->Key,New_node->Key)>0){
			curr=curr->Left;
			
		}
		else if (AVLCompareKeys(curr->Key,New_node->Key)==0 ) {
			++curr->Value.Bike.tripcount;
			return 1;
		}
	}
	return 0;
}
Array * _Distance_function(AVLNode* root,double longt, double lat,Array *array,int *index){
	
	
	if (root==NULL){
		return array;
		
	}
	else{
	
		
		array[*index].distance=distBetween2Points(lat,longt,root->Value.Station.latitude,root->Value.Station.longitude);
		array[*index].Key=root->Key;
		
		
		++(*index);
		array=_Distance_function(root->Left,longt,lat,array,index);
		array=_Distance_function(root->Right,longt,lat,array,index);
		return array;
	}
	
	
	
}
void Distance_function(AVL* tree,double longt, double lat, double Distance){
	int *index=(int*)malloc(sizeof(int*));
	Array *array = (Array*) malloc(tree->Count * sizeof(Array));
	*index=0;
	int indexSmallest;
	int i;
	int j;
	Array temp;
	
	array=_Distance_function(tree->Root,longt,lat,array,index);
	for (i = 0; i < tree->Count-1; ++i) {
      
   // Find index of smallest remaining element
   indexSmallest = i;
   for (j = i + 1; j < tree->Count-1; ++j) {
      
      if (array[j].distance < array[indexSmallest].distance) {
         indexSmallest = j;
      }
   }
      
   // Swap array[i] and array[indexSmallest]
   temp = array[i];
   array[i] = array[indexSmallest];
   array[indexSmallest] = temp;
}
for (i=0; i< tree->Count-1;++i){
   if(array[i].distance<Distance){
	printf("Station %d: distance %lf miles\n",array[i].Key,array[i].distance);
   }
}

	
}
int AVLSearch(AVLNode* Node, int key){
	AVLNode* curr=Node;
	while (curr!=NULL){
		if (AVLCompareKeys(curr->Key,key)<0){
			curr=curr->Right;

		}
		else if (AVLCompareKeys(curr->Key,key)>0){
			curr=curr->Left;
			
		}
		else   {
			if (curr->Value.Type==STATIONTYPE){
				printf("**Station %d: \n",curr->Key);
				printf("Name: '%s'\n",curr->Value.Station.Name);
				printf("Location: (%f,%f)\n",curr->Value.Station.latitude,curr->Value.Station.longitude);
				printf("Capacity: %d\n",curr->Value.Station.dpcapacity);
				printf("Trip Count: %d\n",curr->Value.Station.tripcount);
				return 1;
			}
			else if(curr->Value.Type==TRIPTYPE){
				printf("**Trip %d: \n",curr->Key);
				printf("Bike: %d\n",curr->Value.Trip.bikeid);
				printf("From: %d\n",curr->Value.Trip.from_station_id);
				printf("To: %d\n",curr->Value.Trip.to_station_id);
				int minutes=(curr->Value.Trip.tripduration/60);
				int seconds=curr->Value.Trip.tripduration-(60*minutes);
				printf("Duration: %d min, %d secs\n",minutes,seconds);
				return 1;
			}
			else if (curr->Value.Type==BIKETYPE){
				printf("**Bike: %d\n",curr->Key);
				printf("Trip count: %d\n",curr->Value.Bike.tripcount);
				return 1;
				
			}
			
		}
	}
printf("**not found\n");	
return 0;

	
	
}
AVLNode *_AVLInsert(AVLNode* Node, AVLNode* New_node){

	if (Node==NULL){
		
		Node=New_node;
		
		
	}
	else if(AVLCompareKeys(Node->Key,New_node->Key)<0){
		
		Node->Right=_AVLInsert(Node->Right,New_node);
		if(abs(Height(Node->Left)-Height(Node->Right))==2){
		
			if (AVLCompareKeys(New_node->Key,Node->Right->Key)>0){
				Node=RotateLeft(Node);
				
			}
			else{
				Node->Right=RotateRight(Node->Right);
				Node=RotateLeft(Node);
			}
			
		}
	}
	else if(AVLCompareKeys(Node->Key,New_node->Key)>0){
	
		Node->Left=_AVLInsert(Node->Left,New_node);
		if (abs(Height(Node->Left)-Height(Node->Right))==2){
		
			if (AVLCompareKeys(New_node->Key,Node->Left->Key)<0){
				Node=RotateRight(Node);
				
			}
			else{
				Node->Left=RotateLeft(Node->Left);
				Node=RotateRight(Node);
			}
		}
		
		
	}
	
	Node->Height=1+_max(Height(Node->Left),Height(Node->Right));
	
	return Node;
}
AVL * AVLInsert(AVL *tree, AVLNode* new_node){
	printf("entered the main\n");
	if (new_node->Value.Type==BIKETYPE){
		if(AVLSearchCopy_Bike(tree->Root,new_node)){
			return tree;
		}
	}
	
	tree->Root=_AVLInsert(tree->Root,new_node);
	++tree->Count;
	return tree;
}
	


/////////
////////
////////
AVLNode*_AVLSearch(AVLNode* Node,int tripID){
	
	AVLNode* curr=Node;
	while (curr!=NULL){
		if (AVLCompareKeys(curr->Key,tripID)<0){
			curr=curr->Right;

		}
		else if (AVLCompareKeys(curr->Key,tripID)>0){
			curr=curr->Left;
			
		}
		else {
			printf("match foudnd %d\n",Node->Key);
			return curr;
		}
	}
}
double _latitude(AVLNode *Node,int ID){
	if (Node==NULL){
		return -1;
		
	}
	else if (Node->Key==ID){
		return Node->Value.Station.latitude;
		
	}
	else if (Node->Key> ID){
		return _latitude(Node->Left,ID);
	}
	else{
		return _latitude(Node->Right,ID);
		
	}
}
double _longitude(AVLNode* Node,int ID){
	if (Node==NULL){
		return -1;
		
	}
	else if (Node->Key==ID){
		return Node->Value.Station.longitude;
		
	}
	else if (Node->Key> ID){
		return _longitude(Node->Left,ID);
	}
	else{
		return _longitude(Node->Right,ID);
		
	}
	
}

int _final_recursive(AVLNode* root,AVLNode*Stations, AVLNode* Starting ,AVLNode* Destination,double Distance){

	
	if (root==NULL){
		return 0;
	}
	
	else{	
		printf("station id %d",root->Value.Trip.from_station_id);
		printf("lati and long retrived from start trip %lf %lf\n",_latitude(Stations,root->Value.Trip.from_station_id),_longitude(Stations,root->Value.Trip.from_station_id));
		printf("lati and long retrived from end trip %lf %lf\n",_latitude(Stations,root->Value.Trip.to_station_id),_longitude(Stations,root->Value.Trip.to_station_id));
	 double Start=distBetween2Points(_latitude(Stations,root->Value.Trip.from_station_id),_longitude(Stations,root->Value.Trip.from_station_id),Starting->Value.Station.latitude, Starting->Value.Station.longitude);
	  double End=distBetween2Points(_latitude(Stations,root->Value.Trip.to_station_id), _longitude(Stations,root->Value.Trip.to_station_id),Destination->Value.Station.latitude, Destination->Value.Station.longitude);

	if (Start<=Distance && End<=Distance){
		printf("match %lf %lf\n",Start,End);
		return 1+_final_recursive(root->Left,Stations,Starting,Destination,Distance)+_final_recursive(root->Right,Stations,Starting,Destination,Distance);
		
	}
	else {
		
		return _final_recursive(root->Left,Stations,Starting,Destination,Distance)+_final_recursive(root->Right,Stations,Starting,Destination,Distance);
	}
	//printf("finally %d %d\n",starting,destination);
	
	}
	
}


		
int Route_Function(AVL*tree,AVL* Stations_tree, int tripID,double Distance){
	
	AVLNode* Match=_AVLSearch(tree->Root,tripID);
	printf("key %d\n",Match->Key);
	printf("beginning station %d\n",Match->Value.Trip.from_station_id);
	AVLNode*Final_1=_AVLSearch(Stations_tree->Root,Match->Value.Trip.to_station_id);
	
	printf("final %d\n",Final_1->Key);
	
	
	AVLNode*Final=_AVLSearch(Stations_tree->Root,Match->Value.Trip.from_station_id);
	printf("final %d\n",Final->Key);	
	
	

		

	
	
		int  finalcount=_final_recursive(tree->Root,Stations_tree->Root,Final,Final_1,Distance);
		printf("** Route: from station #%d to station #%d\n ",Final->Key,Final_1->Key);
		printf("** Trip count: %d\n",finalcount);
		double numerator=finalcount;
		double denominator=tree->Count;
		
	   printf("** Percentage: %lf %%\n",(numerator/denominator)*100);
return 0;
	
	
}


 

 
void _AVLPrintPreorder(AVLNode *root, void(*pf)(AVLNode*))
{
  if (root == NULL)  // base case: empty tree
    return;
  else  // recursive case: non-empty tree
  {
    pf(root);
    _AVLPrintPreorder(root->Left, pf);
    _AVLPrintPreorder(root->Right, pf);
  }
}

void AVLPrintPreorder(AVL *tree, void(*pf)(AVLNode*))
{
  printf(">>AVL Preorder: %d node(s)\n", tree->Count);

  _AVLPrintPreorder(tree->Root, pf);

  printf(">><<\n");
}
