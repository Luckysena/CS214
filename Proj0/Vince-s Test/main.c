#include "testSorterV1.c"
#include <string.h>
char *strtok_new(char * string, char const * delimiter);
void toString(data (*total)[5044]);

int main(int argc, char const *argv[])
{
	FILE *fp;
	FILE *wf;

	fp=fopen("movie_metadata.csv","r");
	wf=fopen("movie_new_metadata.csv","ab+");
	int init = 0;
	data ori[5044];
	data (*total)[5044] =&ori;

	char string[4000];
	char *end;
	while(fgets(string,4000,(FILE*) fp)!= NULL)
	{
		int type = 0;
		
		fgets(string,4000,(FILE*) fp);
   		char delimiter[] = ",";
   		char * p    = strtok_new(string, "delimiter");
   		if(init != 0)
   		{
   		while(type<28)
   		{
   			//printf("%s\n",p);
   			switch(type)
   			{
   				case 0:
   				{
   					 if(*p)  
            	(*total)[init-1].color = p;
           			 else   
            	(*total)[init-1].color = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 1:
   				{
   					 if(*p)  
            	(*total)[init-1].dirName = p;
           			 else   
            	(*total)[init-1].dirName= NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 2:
   				{
   					 if(*p)  
            	(*total)[init-1].critCount = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].critCount = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 3:
   				{
   					 if(*p)  
            	(*total)[init-1].durMin = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].durMin = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 4:
   				{
   					 if(*p)  
            	(*total)[init-1].dirFB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].dirFB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 5:
   				{
   					 if(*p)  
            	(*total)[init-1].act3FB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].act3FB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 6:
   				{
   					 if(*p)  
            	(*total)[init-1].act2Name = p;
           			 else   
            	(*total)[init-1].act2Name = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 7:
   				{
   					 if(*p)  
            	(*total)[init-1].act1FB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].act1FB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 8:
   				{
   					 if(*p)  
            	(*total)[init-1].gross = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].gross = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 9:
   				{
   					 if(*p)  
            	(*total)[init-1].genre = p;
           			 else   
            	(*total)[init-1].genre = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 10:
   				{
   					 if(*p)  
            	(*total)[init-1].act1Name = p;
           			 else   
            	(*total)[init-1].act1Name = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 11:
   				{
   					 if(*p)  
            	(*total)[init-1].title = p;
           			 else   
            	(*total)[init-1].title = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 12:
   				{
   					 if(*p)  
            	(*total)[init-1].numVoted = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].numVoted = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 13:
   				{
   					 if(*p)  
            	(*total)[init-1].totalFB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].totalFB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 14:
   				{
   					 if(*p)  
            	(*total)[init-1].act3Name = p;
           			 else   
            	(*total)[init-1].act3Name = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 15:
   				{
   					 if(*p)  
            	(*total)[init-1].faceNum = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].faceNum = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 16:
   				{
   					 if(*p)  
            	(*total)[init-1].keyWord = p;
           			 else   
            	(*total)[init-1].keyWord = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 17:
   				{
   					 if(*p)  
            	(*total)[init-1].link = p;
           			 else   
            	(*total)[init-1].link = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 18:
   				{
   					 if(*p)  
            	(*total)[init-1].numReview = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].numReview = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 19:
   				{
   					 if(*p)  
            	(*total)[init-1].lang = p;
           			 else   
            	(*total)[init-1].lang = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 20:
   				{
   					 if(*p)  
            	(*total)[init-1].country = p;
           			 else   
            	(*total)[init-1].country = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 21:
   				{
   					 if(*p)  
            	(*total)[init-1].rated = p;
           			 else   
            	(*total)[init-1].rated = NULL;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 22:
   				{
   					 if(*p) 
            	(*total)[init-1].budget = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].budget = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 23:
   				{
   					 if(*p)  
            	(*total)[init-1].year= strtol(p,&end,10);
           			 else   
            	(*total)[init-1].year = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 24:
   				{
   					 if(*p)  
            	(*total)[init-1].act2FB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].act2FB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 25:
   				{
   					 if(*p)  
            	(*total)[init-1].score = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].score = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 26:
   				{
   					 if(*p)  
            	(*total)[init-1].ratio = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].ratio = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				case 27:
   				{
   					 if(*p)  
            	(*total)[init-1].movieFB = strtol(p,&end,10);
           			 else   
            	(*total)[init-1].movieFB = 0;
           		
           		p = strtok_new(NULL, delimiter);
           		
   				
   				}
   				break;
   				default:
   				break;
   			}

   			type++;
   		}
           
   			}
   		init++;
		}
		printf("%d\n",(*total)[8].gross);
		printf("%d\n",(*total)[9].gross);
		printf("%d\n",(*total)[10].gross);
		printf("%d\n",(*total)[11].gross);
		//toString(total);
		split(total,0,init,2);
		printf("%s\n","FUC MOTHER FUCKER --------------------------");
		printf("%d\n",(*total)[8].gross);
		printf("%d\n",(*total)[9].gross);
		printf("%d\n",(*total)[10].gross);
		printf("%d\n",(*total)[11].gross);
	
	fclose(fp);	
	fclose(wf);
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
   if((p = strpbrk (source, ",\t")) != NULL || (p = strpbrk (source, "\n")) != NULL )
    {
      *p  = 0;
      riturn = source;
      source = ++p;
   	}
return riturn;
}
void toString(data (*total)[5044])
{
	int size = 5044;
	printf("%d\n",size);
/*	for (int i = 0; i <size ; i++)
	{
		printf("%s\n",(*total) [i].color);
		printf("%s\n",(*total) [i].dirName);
		printf("%d\n",(*total) [i].critCount);
		printf("%d\n",(*total) [i].durMin);
		printf("%d\n",(*total) [i].dirFB);
		printf("%d\n",(*total) [i].act3FB);
		printf("%s\n",(*total) [i].act2Name);
		printf("%d\n",(*total) [i].act1FB);
		printf("%d\n",(*total) [i].gross);
		printf("%s\n",(*total) [i].genre);
		printf("%s\n",(*total) [i].act1Name);
		printf("%s\n",(*total) [i].title);
		printf("%d\n",(*total) [i].numVoted);
		printf("%d\n",(*total) [i].totalFB);
		printf("%s\n",(*total) [i].act3Name);
		printf("%d\n",(*total) [i].faceNum);
		printf("%s\n",(*total) [i].keyWord);
		printf("%s\n",(*total) [i].link);
		printf("%d\n",(*total) [i].numReview);
		printf("%s\n",(*total) [i].lang);
		printf("%s\n",(*total) [i].country);
		printf("%s\n",(*total) [i].rated);
		printf("%d\n",(*total) [i].budget);
		printf("%d\n",(*total) [i].year);
		printf("%d\n",(*total) [i].act2FB);
		printf("%f\n",(*total) [i].score);
		printf("%f\n",(*total) [i].ratio);
		printf("%d\n",(*total) [i].movieFB);
		if(i == 20)
			system("pause");
	}*/

}

/*
 			 if(*p)  
            	printf("%s\n", p );
            else   
            	printf("%s\n", NULL );
            p = strtok_new(NULL, delimiter);

	fclose(wf);
/*	struct _data DataArray[4];
	int DataArraySize = sizeof(DataArray)/sizeof(DataArray[0]);

	char *s;
	fscanf(fp, "%s", s);  //initial row removal
	int i;
	for(i = 0; i < 4; i++){    //iterate through all the newlines
	printf("%s\n","hi" );
	/*fscanf(fp, "%s%*c %s%*c %d%*c %d%*c %d%*c %d%*c %s%*c %d%*c %d%*c %s%*c %s%*c %s%*c %s%*c %d%*c %d%*c %s%*c %d%*c %s%*c %s%*c %d%*c %s%*c %s%*c %s%*c %d%*c %d%*c %d%*c %f%*c %f%*c %d", DataArray[i].color, DataArray[i].dirName,
	&DataArray[i].critCount, &DataArray[i].durMin, &DataArray[i].dirFB, &DataArray[i].act3FB,
	DataArray[i].act2Name, &DataArray[i].act1FB, &DataArray[i].gross, DataArray[i].genre,
	DataArray[i].act1Name, DataArray[i].title, &DataArray[i].numVoted, &DataArray[i].totalFB,
	DataArray[i].act3Name, &DataArray[i].faceNum, DataArray[i].keyWord, DataArray[i].link,
	&DataArray[i].numReview, DataArray[i].lang, DataArray[i].country, DataArray[i].rated,
	&DataArray[i].budget, &DataArray[i].year, &DataArray[i].act2FB, &DataArray[i].score,
	&DataArray[i].ratio, &DataArray[i].movieFB);*/
