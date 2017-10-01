
#ifndef Sorter_H
#define	Sorter_H
#include <time.h>
//typedef enum _boolean bool;

typedef struct _data
{
	char* color; //Color
	char* dirName; //Director Name
	int critCount; //Critic counts i
	int durMin; //Duration in minutes  *****we could just use an int val? -M i
	int dirFB; //Director Facebook likes i
	int act3FB; //Actor 3 facebook likes i
	char* act2Name; //Actor 2's Name
	int act1FB; //Actor 1 Facebook likes
	int gross; // Gross (could be long int)
	char* genre; // genere char* of char*
	char* act1Name; // Actor name
	char* title; // Title
	int numVoted; // number user voted
	int totalFB; // Total Facebook likes
	char* act3Name; // Actor 3's Name
	int faceNum; // Face number in poster
	char* keyWord; // keywords
	char* link; // link to website
	int	numReview; // number of user reviews
	char* lang; // language
	char* country; // country
	char* rated; // rating
	int budget; // budget
	int year; // year created
	int act2FB; // Actor 2's Facebook like
	double score; // movie score out of 10
	double ratio; // aspect ratio
	int movieFB; // Movie facebook likes
 int size;// size of data struct
}data;


//void resize(String * ori); // resizes array if the original aribitrary size is too small
void mergeData(const void* A,int left , int middle , int right) ; // Merges the two arrays together returns a combined array
void split(const void* array, int left, int right,int comp_ptr);// splits the original array returning one array that is split upper half and only keeping the lower half of the array
bool compareString(char* A, char* B);
void toString(data* ori);
#endif
