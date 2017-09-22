/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function
typedef String
struct _string
{
	int size;
	char* data[];
};
struct _data
{
	String dirName; //Director Name
	int critCount; //Critic counts
	int durMin; //Duration in minutes
	int dirFB; //Director Facebook likes
	int act3FB; //Actor 3 facebook likes 
	String act2Name; //Actor 2's Name
	int act1FB; //Actor 1 Facebook likes 
	float gross; // Gross (could be long int)
	String genre; // genere char * of char *
	String act1Name; // Actor name
	String title; // Title
	String numVoted; // number user voted
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
};