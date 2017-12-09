
#include "Sorter.h"
enum _boolean {false, true};

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

bool compare(data leftArr, data rightArr, int comp_ptr)
{
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
void split(data *array, int left, int right,int comp_ptr)
{
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


void acceptService(int* _client_fd){
	int client_fd = *_client_fd;
	printf("[TID:%i]Accepted connection from client id: %i, Awaiting request...\n",pthread_self(),client_fd);
	char request[100], buffer[1000];
	char * ack = "Acknowledged!";

	int len = read(client_fd, request, sizeof(request) - 1);
	if(len < 0) error("ERROR reading from socket\n");
	printf("Request received from client id: %i, request: %s\n",client_fd,request);
	request[len] = '\0';

	if(strcmp(request,"Sort") == 0){
		printf("Sorting..\n");
		write(client_fd, ack, strlen(ack));
		char sortingCol[100];
		len = read(client_fd,sortingCol,sizeof(sortingCol)-1);
		sortingCol[len] = '\0';
		write(client_fd, ack, strlen(ack));
		//Need to add read for sort

		while(true){
			data *Data = (data*)malloc(sizeof(data));
			len = read(client_fd,buffer,sizeof(sortingCol)-1);
			buffer[len] = '\0';
			memcpy(Data,buffer,len);
			toString(Data);
			break;
		}

	}
	close(client_fd);
	return;
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
