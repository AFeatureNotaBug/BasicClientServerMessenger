all: serv send recv

serv: server.c required.h
	clang -W -Wall -Werror -lpthread server.c -o server

send: sendMsg.c required.h
	clang -W -Wall -Werror sendMsg.c -o sender

recv: recvMsg.c required.h
	clang -W -Wall -Werror recvMsg.c -o reciever