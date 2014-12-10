CC = gcc

all: server client
server: reqresp.o mycloudserver.o mycloudlib.o
	${CC} $^ -pthread -o $@
client: reqresp.o mycloudclient.o mycloudlib.o
	${CC} $^ -pthread -o $@
%.o: %.c
	${CC} $< -pthread -c -o $@
clean:
	rm -f */*.o server client

