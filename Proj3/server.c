
#include "Sorter.c"
pthread_t tid;
Heap * outputHeap;

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
    while(true){
      if (listen(sock_fd, 10) != 0) {
          perror("listen()");
          exit(1);
      }

      struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
      printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

      printf("Waiting for connection...\n");
      int * client_fd = (int*)malloc(sizeof(int));
      int tempfd = accept(sock_fd,NULL,NULL);
      memcpy(client_fd, &tempfd,sizeof(int));

      printf("%i\n",*client_fd);
      //pthread_create(&tid,0,acceptService,(void*)&client_fd);

      printf("Connection made: client_fd=%d\n", client_fd);


      char buffer[1000];
      int len = read(client_fd, buffer, sizeof(buffer) - 1);
      buffer[len] = '\0';



    }


    return 0;
}
