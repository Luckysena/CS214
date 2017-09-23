#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Sorter.h"


void resize(data * ori) // resizes array if the original aribitrary size is too small
{

data * create=NULL;
create=(data*)realloc(ori,2*sizeof(ori));
while(create == ori);

ori=create;

}

data * split(data * ori) // splits the original array returning one array that is split upper half and only keeping the lower half of the array
{
	int size=sizeof(ori);

	if (size % 2 == 0) // even array size
	{
		data* upper = (data*)malloc(size/2);
		ori+=(size/2)+1;
		data* newupper = (data*) memcopy(upper,ori,sizeof(data)*((size/2)-1));

		data * lower=NULL;
		lower=(data*)realloc(ori,(size/2)*sizeof(ori));
		while(lower == ori);

		ori=lower;

		return newupper;
	}
	//odd case

}
data * merge(data * left, data* right) // Merges the two arrays together returns a combined array
{

}