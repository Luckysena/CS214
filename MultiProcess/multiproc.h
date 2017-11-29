#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/
typedef enum _boolean bool;

typedef struct _sorterInput{
	char* sortingCol;
	char* file;
	char* dirout;
}sorterInput;

typedef struct _processDirInput{
	DIR* dirName;
	char* _dirName;
	char* dirOut;
}processdirInput;

typedef struct _data
{
	char* color; //Color
	char* dirName; //Director Name
	char* critCount; //Critic counts i
	char* durMin; //Duration in minutes 
	char* dirFB; //Director Facebook likes i
	char* act3FB; //Actor 3 facebook likes i
	char* act2Name; //Actor 2's Name
	char* act1FB; //Actor 1 Facebook likes
	char* gross; // Gross 
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

typedef struct _node{
	int entries;
	data * dataVal;
}Node;

typedef struct _arraylist{
	size_t size;
	int capacity;
	Node ** nodeList;
}ArrayList;

typedef struct _heap{
	ArrayList * list;
	size_t size;
}Heap;

bool compareString(char* A, char* B);

void toString(data* ori);

void fileSorter(char* sortingCol, char* file, char* dirout);

void strip_ext(char *fname);

char *strtok_new(char * string, char const* delimiter);

void split(data *array, int left, int right,int comp_ptr);

void mergeData(data *array,int left , int middle , int right, int comp_ptr);

bool compare(data leftArr, data rightArr, int comp_ptr);

char *getCurrentDir(void);

void processDir(DIR* dirName, char* _dirName ,char* dirOut, char* _sortingCol, int *counter);

int isCSV(const char* str);

int isFile(const char* name);

int checkIfCSV(char *filename);

char *append(char *str, char ch);
