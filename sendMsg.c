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
	
	
	/*Now send some data to the connected server*/
	//char *data		 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean egestas dapibus finibus. Suspendisse odio metus, auctor eu ultricies sed, fermentum sollicitudin odio. Cras venenatis lacinia tempor. Nam vitae massa at odio vehicula convallis. Cras quis pretium turpis. Vestibulum efficitur convallis lacus in scelerisque. Nunc efficitur ac eros fringilla placerat. Morbi cursus sapien neque, quis lobortis arcu convallis id. Mauris quis mattis enim. Mauris et dui suscipit, ullamcorper purus vel, rutrum sem.\n\nIn eleifend mattis tellus, non ullamcorper felis tincidunt eu. Proin consectetur turpis non velit molestie, id vehicula arcu vulputate. Ut malesuada dui at velit pulvinar sagittis. Vestibulum ullamcorper convallis lorem, sed condimentum est vestibulum sit amet. In sit amet sapien a libero accumsan sagittis at at velit. Pellentesque aliquet mi sagittis neque rhoncus, id ornare massa euismod. Donec hendrerit urna nec augue scelerisque scelerisque in non elit. Mauris dictum quis enim id hendrerit.\n\nAenean eu nulla orci. Suspendisse potenti. Suspendisse quis lorem eget ex maximus pulvinar imperdiet et orci. Maecenas at feugiat odio. Praesent at consectetur lorem. Pellentesque imperdiet mattis neque eget convallis. Aenean commodo ante vitae sodales accumsan.\n\nDuis a pellentesque mauris, ac malesuada ligula. Sed pulvinar consectetur varius. Nullam sit amet efficitur lacus, nec porta sapien. Cras placerat et lectus sit amet molestie. Sed sed turpis nec felis auctor iaculis. Proin elementum lacus at erat efficitur aliquet. Curabitur eget tellus semper, feugiat purus vitae, semper justo.\n\nDuis a quam vel justo pretium pretium vel a tortor. Fusce quis interdum nibh, nec consequat ante. Proin bibendum turpis sed dignissim maximus. Nunc pulvinar tortor at rhoncus eleifend. Etiam blandit augue sit amet elit ultricies, ac hendrerit sem mattis. Praesent tincidunt, justo non feugiat finibus, leo nisl pulvinar urna, a cursus nulla dui id sem. Donec faucibus augue vitae eros efficitur, nec iaculis nunc dictum. Cras posuere, ex eget blandit ornare, sapien dolor imperdiet felis, a aliquam lacus augue vitae sapien. Vivamus in sapien non ligula elementum porttitor. Mauris ex erat, venenatis eget posuere nec, aliquam eu tortor. Sed diam justo, consectetur eu turpis eu, interdum facilisis turpis. In in faucibus ipsum, id laoreet mi. In hac habitasse platea dictumst. Donec vitae sollicitudin mauris. Morbi vestibulum lorem vel venenatis consequat.\n\nDonec ornare diam sit amet ex ornare aliquet. Nam mollis pharetra placerat. Etiam id libero non nibh venenatis volutpat. Suspendisse tincidunt luctus enim quis dapibus. Integer elementum nibh blandit, pulvinar nunc id, aliquet lorem. Praesent interdum tincidunt elit at varius. Maecenas eu neque eu justo tincidunt tempor. Ut imperdiet arcu euismod tempus rutrum. Sed fringilla erat a sodales egestas. Quisque porta tempus nisi eget varius. Vivamus sit amet sem vehicula, dignissim nisi quis, porttitor massa.\n\nProin bibendum erat neque, in blandit massa rutrum vel. Mauris ac risus eget urna feugiat elementum sit amet a felis. Suspendisse sollicitudin justo a est convallis facilisis at nec arcu. Vivamus facilisis, metus luctus volutpat suscipit, nisl orci eleifend arcu, eget condimentum risus sem ac purus. Pellentesque ipsum tellus, mattis eu pellentesque non, semper et eros. Aliquam nisl nisl, malesuada ut justo vitae, blandit feugiat. ";
	char *data 		= "Hello, Network!";
	ssize_t data_len  = strlen(data);
	ssize_t totalSent = 0;
	int flags		 = MSG_NOSIGNAL;
	
	while (totalSent != data_len) {	//While there is still data left to send
		ssize_t lastSent = send(fd, data + totalSent, data_len - totalSent, flags);	//Send a chunk of data
		
		totalSent += lastSent;
	}
	
	/*Close socket*/
	close(fd);
}
