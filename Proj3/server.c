
#include "Sorter.c"
pthread_t tid[1000];
serverThreadParams serverParams[1000];
int numThreads = 0;
bool sessions[1000];
int sessionID = 0;


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

    int i = 0;
    for(i; i < 1000; i++){
      sessions[i] = false;
    }

    //initialize sessions to false

    while(true){
      if (listen(sock_fd, 100) == 0) {
        //spawn service thread and keep listening

        int client_fd = accept(sock_fd,NULL,NULL);

        //wait for sessionID request
        char request[100];
        int len = read(client_fd, request, sizeof(request) - 1);
        if(len < 0) error("ERROR reading from socket\n");
        request[len] = '\0';

        //fail if the initial request was incorrect
        if(strcmp(request,"Requesting sessionID")!=0){
          char* sessionIDFailure = "Request for sessionID invalid, terminating connection";
          write(client_fd, sessionIDFailure, strlen(sessionIDFailure));
          close(client_fd);
          continue;
        }

        char ID[10];
        sprintf(ID,"d",sessionID);

        write(client_fd,ID,strlen(ID));

        sessions[sessionID] = true;
        sessionID++;


        serverParams[numThreads].heap = Heap_create(10000);
        serverParams[numThreads].client_fd = client_fd;
        serverParams[numThreads].sessionID = ID;

        pthread_create(&tid[numThreads],0,acceptService,(void*)&serverParams[numThreads]);
        numThreads++;

        //might need to not join pthreads... memory issue and unneeded space usage...
        for(i = 0 ; i < numThreads; i++){
          pthread_join(tid[i],NULL);
        }

      }

      else{
        perror("listen()");
        exit(1);
      }
    }
    return 0;
}
