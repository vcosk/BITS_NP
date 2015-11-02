include ../Makefile.inc

GEN_EXE = tcpserver tcpclient server client

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

tcpserver_test: tcpserver_test.o
	${CC} -o -g $@ tcpserver_test ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

tcpclient_test: tcpclient_test.o
	${CC} -o -g $@ sockettest_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

server_test: server_test.o
	${CC} -o -g $@ server_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

client_test: client_test.o
	${CC} -o -g $@ client_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
