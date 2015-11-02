include ../Makefile.inc

GEN_EXE = client rshmServer

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}
client_test: client_test.o
		${CC} -o $@ client_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

rshmServer_test: rshmServer_test.o
		${CC} -o $@ rshmServer_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}


${EXE} : ${LPLIB}		# True as a rough approximation
