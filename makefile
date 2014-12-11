CC = gcc
DUMMIES = mcput.c mcget.c mclist.c mcdel.c

all: server client mc
	chmod u+x mc*
server: reqresp.o mycloudserver.o mycloudlib.o
	${CC} $^ -pthread -o $@
client: reqresp.o mycloudclient.o mycloudlib.o
	${CC} $^ -pthread -o $@
%.o: %.c
	${CC} $< -pthread -c -o $@
mc: 
	for dummy in ${DUMMIES}; do ln -s makefile "$$dummy"; done

clean:
	rm -f *.o server client  
	for dummy in ${DUMMIES}; do rm -f $$dummy; done
	chmod u-x mc*
