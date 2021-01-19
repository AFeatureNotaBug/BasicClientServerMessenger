#include "required.h"


int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);	//Create a socket
	if (fd == -1) { printf("Error occurred during socket creation\n"); }
	
	
	/*Create a sockaddr_in*/
	struct sockaddr_in addr;
	
	addr.sin_family 	 = AF_INET;        //IPv4
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//Connect on localhost
	addr.sin_port 		 = htons(63249);   //Port 63249
	
	
	/*Connect to address on port 63249*/
	if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		printf("Error occurred during connection\n");
	}
	
	
	/*Now recieve some data from the connected server*/
	ssize_t rcount;			//Number of bytes recieved from client
	char    buf[BUFLEN];	//buffer
			
	while ((rcount = recv(fd, buf, BUFLEN, 0)) > 0) {
		/*Iterate over bytes recieved*/
		for (int i = 0; i < rcount; i++) {
			putchar(buf[i]);
		}
	}
	putchar('\n');
	
	/*Close socket*/
	close(fd);
}
