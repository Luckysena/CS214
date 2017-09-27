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
	String test[4];
	test[0].data = o;
	test[1].data = b;
	test[2].data = g;
	test[3].data = y;

	int size = (sizeof(test)/sizeof(test[0]));
	printf("%d\n",size );


 	splitString(test,0,size-1);

	for (int i = 0; i < sizeof(test)/sizeof(test[0]); ++i)
	{
		printf("%s:",test[i].data);
	}
	printf("\n");
	return 0;

}
//C:\\MinGw\bin\main.exe