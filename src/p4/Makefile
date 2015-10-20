include ../Makefile.inc

GEN_EXE = multicast

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}
multicast_test: multicast_test.o
		${CC} -o $@ multicast_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
