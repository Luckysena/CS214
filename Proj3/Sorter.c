
#include "Sorter.h"
enum _boolean {false, true};
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexD = PTHREAD_MUTEX_INITIALIZER;
int heapCompare(data leftArr, data rightArr, int comp_ptr){
	char c1 = leftArr.title[0];
	char c2 = rightArr.title[0];
	char * tmp1 = leftArr.title;
	char * tmp2 = rightArr.title;

	switch(comp_ptr)
	{
		case 0:
			return strcmp(leftArr.color,rightArr.color);
		break;
		case 1:
		{
			return strcmp(leftArr.dirName,rightArr.dirName);
		}
		break;
		case 2:
			return strcmp(leftArr.critCount,rightArr.critCount);
		break;
		case 3:
			if(atoi(leftArr.durMin) < atoi(rightArr.durMin)){
				return -1;
			}
			else if(atoi(leftArr.durMin) == atoi(rightArr.durMin)){
				return 0;
			}
			else return 1;
		break;
		case 4:
			return strcmp(leftArr.dirFB,rightArr.dirFB) ;
		break;
		case 5:
			 if(atoi(leftArr.act3FB) < atoi(rightArr.act3FB)){
				 return -1;
			 }
			 else if(atoi(leftArr.act3FB) == atoi(rightArr.act3FB)){
				 return 0;
			 }
			 else return 1;
		break;
		case 6:
			return strcmp(leftArr.act2Name,rightArr.act2Name);
		break;
		case 7:
		if(atoi(leftArr.act1FB) < atoi(rightArr.act1FB)){
			return -1;
		}
		else if(atoi(leftArr.act1FB) == atoi(rightArr.act1FB)){
			return 0;
		}
		else return 1;
		break;
		case 8:
		if(atoi(leftArr.gross) <= atoi(rightArr.gross)){
			return -1;
		}
		else if(atoi(leftArr.gross) <= atoi(rightArr.gross)){
			return 0;
		}
		else return 1;
		break;
		case 9:
			return strcmp(leftArr.genre,rightArr.genre);
		break;
		case 10:
			return strcmp(leftArr.act1Name,rightArr.act1Name);
		break;
		case 11:

			if(c1 == '\"'){
				tmp1++;
			}
			if(c2 == '\"'){
				tmp2++;
			}
			//printf("When comparing %s and %s, strcmp says: %i\n",tmp1,tmp2,strcmp(tmp1,tmp2));
			return strcmp(tmp1,tmp2);
		break;
		case 12:
			if(atoi(leftArr.numVoted) <= atoi(rightArr.numVoted)){
				return -1;
			}
			else if(atoi(leftArr.numVoted) <= atoi(rightArr.numVoted)){
				return 0;
			}
			else return 1;
		break;
		case 13:
		if(atoi(leftArr.totalFB) <= atoi(rightArr.totalFB)){
			return -1;
		}
		else if(atoi(leftArr.totalFB) <= atoi(rightArr.totalFB)){
			return 0;
		}
		else return 1;
		break;
		case 14:
			return strcmp(leftArr.act3Name,rightArr.act3Name);
		break;
		case 15:
		if(atoi(leftArr.faceNum) <= atoi(rightArr.faceNum)){
			return -1;
		}
		else if(atoi(leftArr.faceNum) <= atoi(rightArr.faceNum)){
			return 0;
		}
		else return 1;
		break;
		case 16:
			return strcmp(leftArr.keyWord,rightArr.keyWord);
		break;
		case 17:
			return strcmp(leftArr.link,rightArr.link);
		break;
		case 18:
		if(atoi(leftArr.numReview) <= atoi(rightArr.numReview)){
			return -1;
		}
		else if(atoi(leftArr.numReview) <= atoi(rightArr.numReview)){
			return 0;
		}
		else return 1;
		break;
		case 19:
			return strcmp(leftArr.lang,rightArr.lang);
		break;
		case 20:
			return strcmp(leftArr.country,rightArr.country);
		break;
		case 21:
			return strcmp(leftArr.rated,rightArr.rated);
		break;
		case 22:
		if(atoi(leftArr.budget) <= atoi(rightArr.budget)){
			return -1;
		}
		else if(atoi(leftArr.budget) <= atoi(rightArr.budget)){
			return 0;
		}
		else return 1;
		break;
		case 23:
		if(atoi(leftArr.year) <= atoi(rightArr.year)){
			return -1;
		}
		else if(atoi(leftArr.year) <= atoi(rightArr.year)){
			return 0;
		}
		else return 1;
		break;
		case 24:
		if(atoi(leftArr.act2FB) <= atoi(rightArr.act2FB)){
			return -1;
		}
		else if(atoi(leftArr.act2FB) <= atoi(rightArr.act2FB)){
			return 0;
		}
		else return 1;
		break;
		case 25:{
			char * endToken;
			char * endToken2;
			double left = strtol(leftArr.score,&endToken,10);
			double right = strtol(rightArr.score,&endToken,10);
			return left <= right;
		}
		break;
		case 26:{
				char * endToken;
			char * endToken2;
			double left = strtol(leftArr.ratio,&endToken,10);
			double right = strtol(rightArr.ratio,&endToken,10);
			if(left<right){
				return -1;
			}
			else if(left==right){
				return 0;
			}
			else return 1;
		}
		break;
		case 27:{
			 int left = atoi(leftArr.movieFB);
			 int right = atoi(rightArr.movieFB);
			if(left < right){
				return -1;
			}
			else if (left == right){
				return 0;
			}
			else return 1;
		}
		break;
		default:
		return -2;
		break;

	}
}
bool compare(data leftArr, data rightArr, int comp_ptr){
	char c1 = leftArr.title[0];
	char c2 = rightArr.title[0];
	char * tmp1 = leftArr.title;
	char * tmp2 = rightArr.title;

	switch(comp_ptr)
	{
		case 0:
			return strcmp(leftArr.color,rightArr.color) < 0;
		break;
		case 1:
		{
			return strcmp(leftArr.dirName,rightArr.dirName)< 0;
		}
		break;
		case 2:
			return strcmp(leftArr.critCount,rightArr.critCount)< 0;
		break;
		case 3:
			return atoi(leftArr.durMin) <= atoi(rightArr.durMin);
		break;
		case 4:
			return strcmp(leftArr.dirFB,rightArr.dirFB) < 0;
		break;
		case 5:
			return atoi(leftArr.act3FB) <= atoi(rightArr.act3FB);
		break;
		case 6:
			return strcmp(leftArr.act2Name,rightArr.act2Name) < 0;
		break;
		case 7:
			return atoi(leftArr.act1FB) <= atoi(rightArr.act1FB);
		break;
		case 8:
			return atoi(leftArr.gross) <= atoi(rightArr.gross);
		break;
		case 9:
			return strcmp(leftArr.genre,rightArr.genre) < 0;
		break;
		case 10:
			return strcmp(leftArr.act1Name,rightArr.act1Name) < 0;
		break;
		case 11:

			if(c1 == '\"'){
				tmp1++;
			}
			if(c2 == '\"'){
				tmp2++;
			}

			return strcmp(tmp1,tmp2) < 0;
		break;
		case 12:
			return atoi(leftArr.numVoted) <= atoi(rightArr.numVoted);
		break;
		case 13:
			return atoi(leftArr.totalFB) <= atoi(rightArr.totalFB);
		break;
		case 14:
			return strcmp(leftArr.act3Name,rightArr.act3Name) < 0;
		break;
		case 15:
			return atoi(leftArr.faceNum) <= atoi(rightArr.faceNum);
		break;
		case 16:
			return strcmp(leftArr.keyWord,rightArr.keyWord) < 0;
		break;
		case 17:
			return strcmp(leftArr.link,rightArr.link) < 0;
		break;
		case 18:
			return atoi(leftArr.numReview) <= atoi(rightArr.numReview);
		break;
		case 19:
			return strcmp(leftArr.lang,rightArr.lang) < 0;
		break;
		case 20:
			return strcmp(leftArr.country,rightArr.country) < 0;
		break;
		case 21:
			return strcmp(leftArr.rated,rightArr.rated) < 0;
		break;
		case 22:
			return atoi(leftArr.budget) <= atoi(rightArr.budget);
		break;
		case 23:
			return atoi(leftArr.year) <= atoi(rightArr.year);
		break;
		case 24:
			return atoi(leftArr.act2FB) <= atoi(rightArr.act2FB);
		break;
		case 25:{
			char * endToken;
			char * endToken2;
			double left = strtol(leftArr.score,&endToken,10);
			double right = strtol(rightArr.score,&endToken,10);
			return left <= right;
		}
		break;
		case 26:{
				char * endToken;
			char * endToken2;
			double left = strtol(leftArr.ratio,&endToken,10);
			double right = strtol(rightArr.ratio,&endToken,10);
			return left <= right;
		}
		break;
		case 27:{
			 int left = atoi(leftArr.movieFB);
			 int right = atoi(rightArr.movieFB);
			return left < right;
		}
		break;
		default:
		return atoi(leftArr.critCount) < atoi(rightArr.critCount);
		break;

	}

}
void mergeData(data *array,int left , int middle , int right, int comp_ptr){
	int size1,size2;
	size1 = middle-left+1;
	size2 = right-middle;
	data *first = (data*) malloc(sizeof(data)*size1);
	data *second = (data*) malloc(sizeof(data)*size2);
	int i;
	for (i = 0; i < size1; ++i)
	{
		first[i] = array[left+i];
	}
	int j;
	for (j = 0; j < size2; ++j)
	{
		second[j] = array[middle+1+j];
	}
	int iL = 0;
	int iR = 0;
	int iM = left;
	while(iL < size1 && iR < size2)
	{
		if(compare(first[iL],second[iR],comp_ptr))
		{
			array[iM] = first[iL];
			iL++;
		}
		 else
		{
			array[iM] = second[iR];
			iR++;
		}

	iM++;
	}
	while(iL < size1)
	{
		array[iM] = first[iL];
		iL++;
		iM++;
	}
	while(iR < size2)
	{

		array[iM] = second[iR];
		iR++;
		iM++;
	}
		free(first);
		free(second);
		first = NULL;
		second = NULL;
		return;
}
void split(data *array, int left, int right,int comp_ptr){
	if (left < right)
	{
		int middle=left+(right-left)/2;
		split(array,left,middle,comp_ptr);
		split(array,middle+1,right,comp_ptr);
		mergeData(array,left,middle,right,comp_ptr);
	}
	return;
}
void toString(data *total){
	    printf("%s\n",total->color);
	    printf("%s\n",total->dirName);
	    printf("%s\n",total->critCount);
	    printf("%s\n",total->durMin);
	    printf("%s\n",total->dirFB);
	    printf("%s\n",total->act3FB);
	    printf("%s\n",total->act2Name);
	    printf("%s\n",total->act1FB);
	    printf("%s\n",total->gross);
	    printf("%s\n",total->genre);
	    printf("%s\n",total->act1Name);
	    printf("%s\n",total->title);
	    printf("%s\n",total->numVoted);
	    printf("%s\n",total->totalFB);
	    printf("%s\n",total->act3Name);
	    printf("%s\n",total->faceNum);
	    printf("%s\n",total->keyWord);
	    printf("%s\n",total->link);
	    printf("%s\n",total->numReview);
	    printf("%s\n",total->lang);
	    printf("%s\n",total->country);
	    printf("%s\n",total->rated);
	    printf("%s\n",total->budget);
	    printf("%s\n",total->year);
	    printf("%s\n",total->act2FB);
	    printf("%s\n",total->score);
	    printf("%s\n",total->ratio);
	    printf("%s\n",total->movieFB);
	  return;
}
int isCSV(const char* str){
  if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv")){
    return 0;
  }
  else{
    return -1;
  }
}
int isFile(const char* name){
    DIR* directory = opendir(name);

    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}
void strip_ext(char *fname){
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}
char *strtok_new(char * string, char const* delimiter){
   char * delim = (char*)malloc(sizeof(char)*25);
   memset(delim,'/0',sizeof(delim));
   strcpy(delim,"exception");

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
   if(strcmp(delimiter,delim)==0){

     if((p = strpbrk(source, "\"")) != NULL){
       if((p = strpbrk(source+1, "\"")) != NULL){
         p++;
         *p = 0;
         riturn = source;
         source = ++p;
         return riturn;
       }
     }

   }
   if((p = strpbrk (source, ",")) != NULL || (p = strpbrk (source, "\n")) != NULL)
    {
      *p  = 0;
      riturn = source;
      source = ++p;
    }
    if(riturn == NULL){
      riturn = source;
    }
		return riturn;
}

//might need to mutex this
data * fillData(char * input){
	int type = 0;             // counter to assign proper struct attributes
	char delimiter[] = ",";   // delim char
	data * read = (data*)malloc(sizeof(data));
	char * p = strtok_new(input, delimiter);  // p will iterate through input string

	while(type<28){
		switch(type){

			case 0:
			{
				read->color = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->color,p);
						 else
					 strcpy(read->color,"");

					p = strtok_new(NULL, delimiter);


			}
			break;
			case 1:
			{
				 read->dirName = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->dirName,p);
						 else
					strcpy(read->dirName,"");

					p = strtok_new(NULL, delimiter);


			}
			break;
			case 2:
			{
				 read->critCount= (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->critCount,p);
						 else
					strcpy(read->critCount,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 3:
			{
				 read->durMin = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->durMin,p);
						 else
					strcpy(read->durMin,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 4:
			{
				read->dirFB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->dirFB,p);
						 else
					strcpy(read->dirFB,"");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 5:
			{
					read->act3FB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act3FB,p);
						 else
					strcpy(read->act3FB,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 6:
			{
				 read->act2Name = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act2Name,p);
						 else
					strcpy(read->act2Name,"");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 7:
			{
					 read->act1FB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act1FB,p);
						 else
					strcpy(read->act1FB,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 8:
			{
					 read->gross = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->gross,p);
						 else
					strcpy(read->gross,"0");

					p = strtok_new(NULL, delimiter);


			}
			break;
			case 9:
			{
					 read->genre = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->genre,p);
						 else
					strcpy(read->genre,"");

					p = strtok_new(NULL, delimiter);


			}
			break;
			case 10:
			{
					read->act1Name = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act1Name,p);
						 else
					strcpy(read->act1Name,"");

					p = strtok_new(NULL, "exception");


			}
			break;
			case 11:
			{ read->title= (char*) malloc(sizeof(char)*400);

				 if(*p)
					strcpy(read->title,p);
						 else
					strcpy(read->title,"");

					p = strtok_new(NULL, delimiter);


			}
			break;
			case 12:
			{
					read->numVoted = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->numVoted,p);
						 else
					strcpy(read->numVoted,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 13:
			{
					read->totalFB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->totalFB,p);
						 else
					strcpy(read->totalFB,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 14:
			{
					read->act3Name = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act3Name,p);
						 else
					strcpy(read->act3Name,"");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 15:
			{
				read->faceNum = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->faceNum,p);
						 else
					strcpy(read->faceNum,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 16:
			{
				read->keyWord = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->keyWord,p);
						 else
					strcpy(read->keyWord,"");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 17:
			{
				 read->link = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->link,p);
						 else
					strcpy(read->link,"");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 18:
			{
				 read->numReview = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->numReview,p);
						 else
					strcpy(read->numReview,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 19:
			{
				read->lang = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->lang,p);
						 else
					strcpy(read->lang,"");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 20:
			{
				 read->country = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->country,p);
						 else
					strcpy(read->country,"");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 21:
			{
					read->rated = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->rated,p);
						 else
					strcpy(read->rated,"");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 22:
			{
				read->budget = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->budget,p);
						 else
					strcpy(read->budget,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 23:
			{
				read->year = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->year,p);
						 else
					strcpy(read->year,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 24:
			{
			 read->act2FB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->act2FB,p);
						 else
					strcpy(read->act2FB,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 25:
			{
				read->score = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->score,p);
						 else
					strcpy(read->score,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			case 26:
			{
				read->ratio = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->ratio,p);
						 else
					strcpy(read->ratio,"0");

					p = strtok_new(NULL, delimiter);

			}
			break;
			case 27:
			{
		 read->movieFB = (char*) malloc(sizeof(char)*400);
				 if(*p)
					strcpy(read->movieFB,p);
						 else
					strcpy(read->movieFB,"0");

					p = strtok_new(NULL, delimiter);
			}
			break;
			default:
			break;
		}
		type++;
	}
  return read;
}

bool isNum(char* input){

		if(input == NULL){
			return false;
		}
		int i;
		for(i = 0; i < strlen(input); i++){
			if(isdigit(input[i]) == 0){
				return false;
			}
		}
		return true;
}





Node * Node_create(data * elem){
	Node * node = malloc(sizeof(Node));
	node->entries = 1;
	node->dataVal = malloc(sizeof(data));
	memcpy(node->dataVal,elem,sizeof(data));
	if(node == NULL){
		printf("Node creation failed\n");
		return node;
	}
	return node;
}
ArrayList * ArrayList_create(int n){
	ArrayList *list = malloc(sizeof(*list));
	if(list == NULL){
		return NULL;
	}
	list->capacity = n;
	list->size = 0;
	list->nodeList = calloc(n,sizeof(*(list->nodeList)));

	return list;
}
ArrayList * Arraylist_resize(ArrayList * list, int cap){
	ArrayList * newList = ArrayList_create((2*cap));
	int i;
	for(i = 0; i < cap; i++){
		(newList->nodeList[i]) = (list->nodeList[i]);
	}
	newList->size = cap;
	return newList;
}
ArrayList * ArrayList_add(ArrayList * list, data * elem){
	if(elem->color == NULL){
		printf("Adding elem failed due to null elem\n");
		return;
	}
	list->nodeList[list->size] = Node_create(elem);
	(list->size)++;
	if((list->capacity)==(list->size)){
		list = Arraylist_resize(list,(list->capacity));
	}
	return list;
}
Heap * Heap_create(int n){
	Heap * heap = malloc(sizeof(*heap));
	if(heap == NULL){
		printf("Heap creation failed\n");
		return NULL;
	}
	heap->size = n;
	heap->list = ArrayList_create(n);
	return heap;
}
void SiftUp(Heap * heap, int comp_ptr){
	int k, p;
	k = (heap->list->size)-1;
	p = (k-1)/2;
	if(k==p){
		//single node case
		return;
	}
	//printf("Comparing %s with %s\n",heap->list->nodeList[k]->dataVal->durMin,heap->list->nodeList[p]->dataVal->durMin);

	while((heapCompare(*(heap->list->nodeList[k]->dataVal),*(heap->list->nodeList[p]->dataVal),comp_ptr))<0){
		//printf("Swapping %s with %s\n",heap->list->nodeList[k]->dataVal->durMin,heap->list->nodeList[p]->dataVal->durMin);
		swapNodes(heap,p,k);
		k = p;
		p = (k-1)/2;
		//free(temp);
	}
	return;
}
void Heap_add(Heap * heap, data * elem, int comp_ptr){
	//printf("Adding to heap: %s\n",elem->title);
	heap->list = ArrayList_add(heap->list,elem);
	//printf("Item added.\n");
	SiftUp(heap,comp_ptr);
	return;
}
void swapNodes(Heap * heap, int p, int k){
	data * temp = heap->list->nodeList[p]->dataVal;
	heap->list->nodeList[p]->dataVal = heap->list->nodeList[k]->dataVal;
	heap->list->nodeList[k]->dataVal = temp;
	return;
}
SiftDown(Heap * heap, int comp_ptr){
	int p, c1, c2, k, sizeHeap;
	p = 0; c1 = 1; c2 = 2; sizeHeap = heap->list->size;
	data * datap, *data1, *data2;

	if(sizeHeap == 1){
		return;
	}

	if(c2>(sizeHeap-1)){
		datap = heap->list->nodeList[p]->dataVal;
		data1 = heap->list->nodeList[c1]->dataVal;
		if(heapCompare(*datap,*data1,comp_ptr)<=0){
			return;
		}
		else{
			//printf("Swapping %s with %s\n",datap->durMin,data1->durMin);
			swapNodes(heap,p,c1);
		}
		return;
	}

	while(c1<=(sizeHeap-1)){
		if(c2>(sizeHeap-1)){
			break;
		}
		datap = heap->list->nodeList[p]->dataVal;
		data1 = heap->list->nodeList[c1]->dataVal;
		data2 = heap->list->nodeList[c2]->dataVal;
		if((heapCompare(*datap,*data1,comp_ptr)>0) && (heapCompare(*datap,*data2,comp_ptr)>0)){
			k = heapCompare(*data1,*data2,comp_ptr);
			if(k <= 0){
				swapNodes(heap,p,c1);
				//printf("Swapping %s with %s\n",datap->durMin,data1->durMin);
				p = c1;
			}

			else if(k > 0){
				swapNodes(heap,p,c2);
				//printf("Swapping %s with %s\n",datap->durMin,data2->durMin);
				p = c2;
			}
		}
		else if((heapCompare(*datap,*data1,comp_ptr)>0) && (heapCompare(*datap,*data2,comp_ptr)<=0)){
			swapNodes(heap,p,c1);
			//printf("Swapping %s with %s\n",datap->durMin,data1->durMin);
			p = c1;
		}
		else if((heapCompare(*datap,*data1,comp_ptr)<=0) && (heapCompare(*datap,*data2,comp_ptr)>0)){
			swapNodes(heap,p,c2);
			//printf("Swapping %s with %s\n",datap->durMin,data2->durMin);
			p = c2;
		}
		else if((heapCompare(*datap,*data1,comp_ptr)<=0) && (heapCompare(*datap,*data2,comp_ptr)<=0)){
			break;
		}
		c1 = 2*p + 1;
		c2 = 2*p + 2;
	}
	if(c1>(sizeHeap-1)){
		return;
	}
	datap = heap->list->nodeList[p]->dataVal;
	data1 = heap->list->nodeList[c1]->dataVal;
	if(c2>(sizeHeap-1)){
		if(heapCompare(*datap,*data1,comp_ptr)>0){
			swapNodes(heap,p,c1);
		}
	}
	return;
}
data * Heap_remove(Heap * heap, int comp_ptr){
	int root, last;
	root = 0;
	last = (heap->list->size)-1;
	data * temp = heap->list->nodeList[root]->dataVal;
	heap->list->nodeList[root]->dataVal = heap->list->nodeList[last]->dataVal;
	heap->list->nodeList[last]->dataVal = NULL;
	heap->list->size--;
	SiftDown(heap,comp_ptr);
	return temp;

}

void acceptService(void* arguments){

	//parameter unpacking from thread input
	serverThreadParams *args = arguments;
	int client_fd = args -> client_fd;
	char * requestType = args -> requestType;
	char * sessionID = args -> sessionID;
	Heap * heap = args -> heap;
	int comp_ptr = args -> sortingColumn;



	//string declarations
	char * ack = "Acknowledged!";
	char * finish = "Finished";
	data * tempData;
	int len, i;


	//sort request
	if(strcmp(requestType,"Sort") == 0){
		// Acknowledged sortingCol
		write(client_fd, ack, strlen(ack));

		//accept file contents
		char buffer[9001];
		while(true){

			memset(buffer,'\0',sizeof(char)*9001);
			len = read(client_fd,buffer,9000);
			buffer[len] = '\0';


			//printf("Adding: %s\n",buffer);
			//printf("\n");

			//end of file content message
			if(strcmp(buffer,"Finished") == 0){
				break;
			}


			//fill in the heap with data structs
			tempData = fillData(buffer);
			Heap_add(heap,tempData,comp_ptr);
			write(client_fd,"Accepted line",strlen("Accepted line"));
		}
		printf("[SID:%s]Sort Completed\n",sessionID);
		close(client_fd);
	}

	//dump request
	else if(strcmp(requestType,"Dump") == 0){

			//convert data struct to strings
			int i;
			int listSize = heap->list->size;
			char buffer[9000];
			for (i = 0; i <(listSize-1) ; i++){
				tempData = Heap_remove(heap,comp_ptr);
				memset(buffer,'\0',sizeof(char)*9000);
				strcat(buffer,tempData->color);
				strcat(buffer,",");
				strcat(buffer,tempData->dirName);
				strcat(buffer,",");
				strcat(buffer,tempData->critCount);
				strcat(buffer,",");
				strcat(buffer,tempData->durMin);
				strcat(buffer,",");
				strcat(buffer,tempData->dirFB);
				strcat(buffer,",");
				strcat(buffer,tempData->act3FB);
				strcat(buffer,",");
				strcat(buffer,tempData->act2Name);
				strcat(buffer,",");
				strcat(buffer,tempData->act1FB);
				strcat(buffer,",");
				strcat(buffer,tempData->gross);
				strcat(buffer,",");
				strcat(buffer,tempData->genre);
				strcat(buffer,",");
				strcat(buffer,tempData->act1Name);
				strcat(buffer,",");
				strcat(buffer,tempData->title);
				strcat(buffer,",");
				strcat(buffer,tempData->numVoted);
				strcat(buffer,",");
				strcat(buffer,tempData->totalFB);
				strcat(buffer,",");
				strcat(buffer,tempData->act3Name);
				strcat(buffer,",");
				strcat(buffer,tempData->faceNum);
				strcat(buffer,",");
				strcat(buffer,tempData->keyWord);
				strcat(buffer,",");
				strcat(buffer,tempData->link);
				strcat(buffer,",");
				strcat(buffer,tempData->numReview);
				strcat(buffer,",");
				strcat(buffer,tempData->lang);
				strcat(buffer,",");
				strcat(buffer,tempData->country);
				strcat(buffer,",");
				strcat(buffer,tempData->rated);
				strcat(buffer,",");
				strcat(buffer,tempData->budget);
				strcat(buffer,",");
				strcat(buffer,tempData->year);
				strcat(buffer,",");
				strcat(buffer,tempData->act2FB);
				strcat(buffer,",");
				strcat(buffer,tempData->score);
				strcat(buffer,",");
				strcat(buffer,tempData->ratio);
				strcat(buffer,",");
				strcat(buffer,tempData->movieFB);
				write(client_fd, buffer, strlen(buffer));
			}
			write(client_fd,"FinishedSend",strlen("FinishedSend"));
			printf("[SID:%s]Dump completed\n",sessionID);
			close(client_fd);
	}
	return;
}
