
#ifndef Sorter_H
#define	Sorter_H
#include <time.h>
typedef enum _boolean bool;

typedef struct _data
{
	char* color; //Color
	char* dirName; //Director Name
	char* critCount; //Critic counts i
	char* durMin; //Duration in minutes  *****we could just use an char* val? -M i
	char* dirFB; //Director Facebook likes i
	char* act3FB; //Actor 3 facebook likes i
	char* act2Name; //Actor 2's Name
	char* act1FB; //Actor 1 Facebook likes
	char* gross; // Gross (could be long char*)
	char* genre; // genere char* of char*
	char* act1Name; // Actor name
	char* title; // Title
	char* numVoted; // number user voted
	char* totalFB; // Total Facebook likes
	char* act3Name; // Actor 3's Name
	char* faceNum; // Face number in poster
	char* keyWord; // keywords
	char* link; // link to website
	char* numReview; // number of user reviews
	char* lang; // language
	char* country; // country i i
	char* rated; // rating
	char* budget; // budget
	char* year; // year created
	char* act2FB; // Actor 2's Facebook like
	char* score; // movie score out of 10
	char* ratio; // aspect ratio
	char* movieFB; // Movie facebook likes
 char* size;// size of data struct
}data;


//void resize(String * ori); // resizes array if the original aribitrary size is too small
void mergeData(data* A,int left , int middle , int right, int comp_ptr) ; // Merges the two arrays together returns a combined array
void split(data* array, int left, int right,int comp_ptr);// splits the original array returning one array that is split upper half and only keeping the lower half of the array
bool compareString(char* A, char* B);
void toString(data* ori,int size);
#endif
