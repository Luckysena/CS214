
#include "Sorter.c"
Heap * outputHeap;
pthread_t tid[1000];
serverThreadParams serverParams[1000];
int numThreads = 0;

int main(int argc, char **argv)
{
    if((argv[1] == NULL) || (argv[2] == NULL)){
      printf("Missing port input, terminating...\n");
      return -1;
    }
    else if(argc > 3){
      printf("Too many command arguments, terminating...\n");
      return -2;
    }

    char *portNum = argv[2];
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, portNum, &hints, &result);
    if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(1);
    }

    if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
        perror("bind()");
        exit(1);
    }

    outputHeap = Heap_create(10000);
    while(true){
      if (listen(sock_fd, 100) != 0) {
          perror("listen()");
          exit(1);
      }

      int * client_fd = (int*)malloc(sizeof(int));
      int tempfd = accept(sock_fd,NULL,NULL);
      memcpy(client_fd, &tempfd,sizeof(int));
      serverParams[numThreads].heap = outputHeap;
      serverParams[numThreads].client_fd = client_fd;

      pthread_create(&tid[numThreads],0,acceptService,(void*)&serverParams[numThreads]);
      numThreads++;
    }
    int i;
    for(i = 0; i < numThreads; i++){
      pthread_join(tid[i],NULL);
    }
    return 0;
}
