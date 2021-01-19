#include "required.h"


typedef struct connections connections;

struct connections {
	int sendfd;
	int recvfd;
};


int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);	//Create a TCP socket
	if (fd == -1) { printf("Error occurred during socket creation\n"); }
	
	/*Create a sockaddr_in*/
	struct sockaddr_in addr;

	addr.sin_family 	 = AF_INET;			//IPv4
	addr.sin_addr.s_addr = INADDR_ANY;		//Any available network interface
	addr.sin_port 		 = htons(63249);	//Port 63249
	
	
	/*Bind the socket to port 63249*/
	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) { printf("Error occurred during binding\n"); }
	
	
	/*Listen for connections on port 63249*/
	int backlog = 10;	//Total queued connections
	if (listen(fd, backlog) == -1) { printf("Error occurred during listening\n"); }
	
	
	/*We can now accept new connections in a loop*/
	
	/*Create cliaddr, used to store client address*/
	struct sockaddr_in 	cliaddr;
	socklen_t 			cliaddr_len = sizeof(cliaddr);
	char				*cliIP;	//Used to print client IP address
	
	
	struct connections *conns = malloc(sizeof(connections));	//Used to store sender and reciever fd's
	
	
	/*Establish reciever connection and pass connection fd to thread*/
	int recvConn = accept(fd, (struct sockaddr *) &cliaddr, &cliaddr_len);	//Accept a connection
	
	if (recvConn == -1) {
		printf("Error occurred while accepting reciever connection");
		
	} else {
		/*Convert cliaddr to string for printing*/
		cliIP = inet_ntoa(cliaddr.sin_addr);
		printf("Incoming connection from %s\n", cliIP);
		
		conns->recvfd = recvConn;
	}
	
	
	/*Establish sender connection and pass connection fd to thread*/
	int sendConn = accept(fd, (struct sockaddr *) &cliaddr, &cliaddr_len);	//Accept a connection
	
	if (sendConn == -1) {
		printf("Error occurred while accepting sender connection");
		
	} else {
		/*Convert cliaddr to string for printing*/
		cliIP = inet_ntoa(cliaddr.sin_addr);
		printf("Incoming connection from %s\n", cliIP);
		
		conns->sendfd = sendConn;
	}
	
	/*Create threads for sender and reciever*/
	pthread_t connThread;
	
	int err = pthread_create(&connThread, NULL, fwdMsg, conns);
	err = pthread_join(connThread, NULL);
	
	/*Close server socket*/
	close(fd);
}


void *fwdMsg(void *connfd) {
	connections *conns = (connections *) connfd;
	
	/*Recieve some data from a sender*/
	ssize_t rcount;	 		//Number of bytes recieved from client
	char    buf[BUFLEN];	//buffer
	int flags		 = MSG_NOSIGNAL;
	
	while ((rcount = recv(conns->sendfd, buf, BUFLEN, 0)) > 0) {
		int totalSent = 0;
		
		/*Forward data to reciever*/
		while (totalSent < rcount) {	//While there is still data left to send
			ssize_t lastSent = send(conns->recvfd, buf + totalSent, rcount - totalSent, flags);	//Send a chunk of data
			totalSent += lastSent;
		}
	}
	
	return NULL;
}
