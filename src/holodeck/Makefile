include ../Makefile.inc

GEN_EXE = test forking

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

test_test: test_test.o
	${CC} -o $@ test_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

	forking_test: forking_test.o
		${CC} -o $@ forking_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
