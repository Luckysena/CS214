
#ifndef Sorter_H
#define	Sorter_H
#include <time.h>
//typedef enum _boolean bool;
typedef struct _string
{
	int size;
	char* data;
}String;

typedef struct _data
{
	String color; //Color
	String dirName; //Director Name
	int critCount; //Critic counts
	time_t durMin; //Duration in minutes  *****we could just use an int val? -M
	int dirFB; //Director Facebook likes
	int act3FB; //Actor 3 facebook likes
	String act2Name; //Actor 2's Name
	int act1FB; //Actor 1 Facebook likes
	float gross; // Gross (could be long int)
	String genre; // genere char * of char *
	String act1Name; // Actor name
	String title; // Title
	int numVoted; // number user voted
	int totalFB; // Total Facebook likes
	String act3Name; // Actor 3's Name
	int faceNum; // Face number in poster
	String keyWord; // keywords
	String link; // link to website
	int	numReview; // number of user reviews
	String lang; // language
	String country; // country
	String rated; // rating
	float budget; // budget
	int year; // year created
	int act2FB; // Actor 2's Facebook like
	float score; // movie score out of 10
	float ratio; // aspect ratio
	int movieFB; // Movie facebook likes
 int comp_ptr[28];//how to sort/ compare
 int size;// size of data struct
}data;


void resize(String * ori); // resizes array if the original aribitrary size is too small
void mergeData(const void* A,int left , int middle , int right) ; // Merges the two arrays together returns a combined array
void split(const void* array, int left, int right,int comp_ptr);// splits the original array returning one array that is split upper half and only keeping the lower half of the array
bool compareString(char* A, char* B);
void toString(data* ori);
#endif
