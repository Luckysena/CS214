#include "Sorter.c"
#include <string.h>
char *strtok_new(char * string, char const * delimiter);


int main(int argc, char const *argv[])
{

  char * col_names[28];  //array which contains name of columns

  int init = 0;         // counter for rows
  data total[5044];     // array for data structs
  char string[4000];    // stdin string buffer

  while(fgets(string,4000,stdin)!= NULL)   // loop to go thru all of input
  {
      int type = 0;             // counter to assign proper struct attributes
      char delimiter[] = ",";   // delim char
      data read;                // placeholder data struct for filling
      char * p = strtok_new(string, "delimiter");  // p will iterate through input string
      if(init != 0)             // first stdin is column names string
      {
      while(type<28)            // fill in struct attributes
      {
       // printf("%s\n",p);
        switch(type)
        {

          case 0:
          {
            read.color = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.color,p);
                 else
               strcpy(read.color,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 1:
          {
             read.dirName = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.dirName,p);
                 else
              strcpy(read.dirName,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 2:
          {
             read.critCount= (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.critCount,p);
                 else
              strcpy(read.critCount,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 3:
          {
             read.durMin = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.durMin,p);
                 else
              strcpy(read.durMin,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 4:
          {
            read.dirFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.dirFB,p);
                 else
              strcpy(read.dirFB,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 5:
          {
              read.act3FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act3FB,p);
                 else
              strcpy(read.act3FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 6:
          {
             read.act2Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act2Name,p);
                 else
              strcpy(read.act2Name,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 7:
          {
               read.act1FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act1FB,p);
                 else
              strcpy(read.act1FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 8:
          {
               read.gross = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.gross,p);
                 else
              strcpy(read.gross,"0");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 9:
          {
               read.genre = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.genre,p);
                 else
              strcpy(read.genre,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 10:
          {
              read.act1Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act1Name,p);
                 else
              strcpy(read.act1Name,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 11:
          { read.title= (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.title,p);
                 else
              strcpy(read.title,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 12:
          {
              read.numVoted = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.numVoted,p);
                 else
              strcpy(read.numVoted,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 13:
          {
              read.totalFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.totalFB,p);
                 else
              strcpy(read.totalFB,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 14:
          {
              read.act3Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act3Name,p);
                 else
              strcpy(read.act3Name,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 15:
          {
            read.faceNum = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.faceNum,p);
                 else
              strcpy(read.faceNum,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 16:
          {
            read.keyWord = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.keyWord,p);
                 else
              strcpy(read.keyWord,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 17:
          {
             read.link = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.link,p);
                 else
              strcpy(read.link,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 18:
          {
             read.numReview = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.numReview,p);
                 else
              strcpy(read.numReview,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 19:
          {
            read.lang = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.lang,p);
                 else
              strcpy(read.lang,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 20:
          {
             read.country = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.country,p);
                 else
              strcpy(read.country,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 21:
          {
              read.rated = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.rated,p);
                 else
              strcpy(read.rated,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 22:
          {
            read.budget = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.budget,p);
                 else
              strcpy(read.budget,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 23:
          {
            read.year = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.year,p);
                 else
              strcpy(read.year,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 24:
          {
           read.act2FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act2FB,p);
                 else
              strcpy(read.act2FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 25:
          {
            read.score = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.score,p);
                 else
              strcpy(read.score,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 26:
          {
            read.ratio = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.ratio,p);
                 else
              strcpy(read.ratio,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 27:
          {
         read.movieFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.movieFB,p);
                 else
              strcpy(read.movieFB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          default:
          break;
        }

        type++;
      }
        total[init-1]=read;     // point the item in struct array to placeholder data struct

        }
        else
        {
          int counter = 0;       // counter for filling in name of columns row
          while(counter<28){     // loop to create an array of column names
            col_names[counter] = (char *) malloc(sizeof(char)*250);   // make space for the name
            if(*p){              // if the pointer isnt empty, copy the string into array
              strcpy(col_names[counter],p);
            }
            else{
              strcpy(col_names[counter],"");
            }
            p = strtok_new(NULL,delimiter);
            counter++;
          }
        }
      init++;  //increment the row we're on
    }

  // now we need to read the arg column name and set comp_ptr to it
  int comp_ptr = 0;
  for(comp_ptr; comp_ptr < 28; comp_ptr++){
    if(strcmp(col_names[0], argv[2])==0){
      break;  //break out of the loop once we reach the col name we need
    }
  }

  int i;
  char * firstRow = (char *)malloc(sizeof(char)*1000);
  for(i = 0; i<28; i++){
    strcat(firstRow, col_names[i]);
    strcat(firstRow, ",");
    free(col_names[i]);      //free the memory used for col name array
  }

  fprintf(stdout, "%s\n", firstRow);
  free(firstRow);

  if(comp_ptr == 28){   // this is the case where input doesn't match the col names list
    comp_ptr = 2; //defaults to num_critic_for_reviews
  }

  split(total,0,init-2,comp_ptr);  // sort the data
  //toString(total,init-1)
   char * bufferIn = (char*) malloc(sizeof(char)*9000);  // create buffer for output
   for (i = 0; i <init-1 ; i++)
  {
    // copy the sorted information in row by row with commas
    memset(bufferIn,'\0',sizeof(bufferIn));
    strcat(bufferIn,total [i].color);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].dirName);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].critCount);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].durMin);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].dirFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act3FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act2Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act1FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].gross);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].genre);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act1Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].title);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].numVoted);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].totalFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act3Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].faceNum);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].keyWord);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].link);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].numReview);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].lang);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].country);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].rated);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].budget);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].year);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act2FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].score);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].ratio);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].movieFB);
    fprintf(stdout, "%s\n",bufferIn); //output
  }
  return 0;
}


char *strtok_new(char * string, char const * delimiter)
{
   static char *source = NULL;
   char *p, *riturn = 0;
   if(string != NULL)
   {
    source = string;
    }
   if(source == NULL)
    {
    return NULL;
   }
   if((p = strpbrk (source, ",")) != NULL || (p = strpbrk (source, "\n")) != NULL )
    {
      *p  = 0;
      riturn = source;
      source = ++p;
    }
return riturn;
}
void toString(data *total,int size)
{
  printf("%s\n",size);
int i;
for (i = 2; i <size ; i++)
  {
    printf("%s\n",total [i].color);
    printf("%s\n",total [i].dirName);
    printf("%s\n",total [i].critCount);
    printf("%s\n",total [i].durMin);
    printf("%s\n",total [i].dirFB);
    printf("%s\n",total [i].act3FB);
    printf("%s\n",total [i].act2Name);
    printf("%s\n",total [i].act1FB);
    printf("%s\n",total [i].gross);
    printf("%s\n",total [i].genre);
    printf("%s\n",total [i].act1Name);
    printf("%s\n",total [i].title);
    printf("%s\n",total [i].numVoted);
    printf("%s\n",total [i].totalFB);
    printf("%s\n",total [i].act3Name);
    printf("%s\n",total [i].faceNum);
    printf("%s\n",total [i].keyWord);
    printf("%s\n",total [i].link);
    printf("%s\n",total [i].numReview);
    printf("%s\n",total [i].lang);
    printf("%s\n",total [i].country);
    printf("%s\n",total [i].rated);
    printf("%s\n",total [i].budget);
    printf("%s\n",total [i].year);
    printf("%s\n",total [i].act2FB);
    printf("%s\n",total [i].score);
    printf("%s\n",total [i].ratio);
    printf("%s\n",total [i].movieFB);
  }

}
