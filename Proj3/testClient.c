#include "Sorter.c"

int main(int argc, char **argv)
{
	int s, n;
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hints, *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* IPv4 only */
	hints.ai_socktype = SOCK_STREAM; /* TCP */

	s = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (s != 0) {
	        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        	exit(1);
	}

	if(connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1){
                perror("connect");
                exit(2);
        }

  printf("Connecting to server...\n");
	char *buffer = "Sort";
  char *sortingCol = "movie_title";

	n = write(sock_fd, buffer, strlen(buffer));
  if(n != -1){
    printf("Sending sort request...\n");
  }
  else{
    printf("Error writing to socket\n");
  }
	char resp[1000];
	int len = read(sock_fd, resp, 999);
	resp[len] = '\0';
	printf("%s\n", resp);

  n = write(sock_fd,sortingCol,strlen(sortingCol));
  if(n != -1){
    printf("Sending sortingCol...\n");
  }
  else{
    printf("Error writing to socket\n");
  }
  len = read(sock_fd, resp, 999);
  resp[len] = '\0';
  printf("%s\n", resp);

  return 0;
}
