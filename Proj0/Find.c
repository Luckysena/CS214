#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
int 
getInputSize (const char *input) 
{
  
 
int count = 1;
  
 
while (*input)
    
 
    {
      
 
if (((int) '/' == (int) *input )||((int) '\\' == (int) *input))
    
count++;
      
 
input++;
    
} 
 
return count;

}
int getSize(const char* s)
{   
    int count = 0;
    while(*s)
    {
    count++;
    s++;
    }
    return count;
}

 
char* appendNull(const char * dir)
{
    int size =getSize(dir);
char* ret = (char*)malloc(1+sizeof(char) * (size));
    memset(ret,'\0',size+1);
    strncpy(ret,dir,size);
return ret;
}

void
getDir (char** dir,const char *directory,int i) 
{
  
char * newDir = appendNull(directory);


 
char *temp;
temp = strtok (newDir, "/\\");
 char * buffer;
 
int counter = 1;
int size;  
 
while (temp != NULL && counter < i)
    
    {
size = getSize(temp);
*dir = (char*)malloc(sizeof(char)*size);
temp = strtok (NULL, "/");
strcpy(*dir,temp);
dir++;
counter++;
    
}
}
int findInt(char* comp)
 {
    char*cat[] = {"color","director_num","num_critic_for_reviews","duration","director_facebook_likes","actor_3_facebook_likes","actor_2_name","actor_1_facebook_likes"\
    ,"gross","genres","actor_1_name","movie_title","num_voted_users","cast_total_facebook_likes","actor_3_name","facenumber_in_poster","plot_keywords","movie_imdb_link"\
    "num_user_for_reviews","language","country","content_rating","budget","title_year","actor_2_facebook_likes","imdb_score","aspect_ratio","movie_facebook_likes"};
    
    int counter = 0;
    int size = sizeof(cat)/sizeof(cat[0]);

    while(counter < size )
    {
        if(comp != NULL)
            if(strcmp(comp,cat[counter]) == 0)
              return counter;
        counter++;
     }
    return 2;
 }

void getInput(int* input, const char *directory,int i)
{

char * newDir = appendNull(directory);


 
char *temp;
temp = strtok (newDir, "\\");
 char * buffer;
 
int counter = 0;
int size;  
 
while (temp != NULL && counter < i)
    {
      
       input[counter] = findInt(temp);
        temp = strtok (NULL, "\\");
        counter++;
    }  

}

 
 /*
int 
main (int argc, char const *argv[]) 
{
  
 
 
char *test = "color\\movie_title\\country\\language\\gross\\stuff";
int i = getInputSize (test);
int *compareArr = (int*)malloc(sizeof(int)*i); 
getInput(compareArr,test,i);
int counter = 0;
return 0;

 
}
*/




