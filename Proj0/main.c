#include "Sorter.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	data * a = (data*)malloc(sizeof(data)*12);\
	char o[]={'a','b','c','d','y','u','\0'};
	char b[]={'v','i','n','c','\0'};
	char g[]={'c','o','o','l','\0'};
	char y[]={'d','i','e','d','\0'};
	char t[]={'t','l','o','o','\0'};
	String test[5];
	test[0].data = o;
	test[1].data = b;
	test[2].data = g;
	test[3].data = y;
	test[4].data = t;
	int size = (sizeof(test)/sizeof(test[0]));
	int comp_ptr = 3;
		
	void (*Merge_ptr)(const void*,int,int,int);
	if(comp_ptr==1)
	{
		void (*Merge_ptr)(const void*,int,int,int) = &mergeInt;
	}
	if(comp_ptr==2){
		void (*Merge_ptr)(const void*,int,int,int) = &mergeFloat;
	}
	if(comp_ptr==3){
		void (*Merge_ptr)(const void*,int,int,int) = &mergeString;
	}
	if (comp_ptr==4){
		void (*Merge_ptr)(const void*,int,int,int)= &mergeDateTime;	
	}


	split(test,0,size-1,(*Merge_ptr));

	for (int i = 0; i < sizeof(test)/sizeof(test[0]); ++i)
	{
		printf("%s ",test[i].data);
	}
	printf("\n");
	return 0;

}
// int is default any number not 2,3,4
// float is 2
// String is 3
// Datetime is 4
//C:\\MinGw\bin\main.exe