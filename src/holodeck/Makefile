include ../Makefile.inc

GEN_EXE = test forking execve envargs pipe pipe2 pipe3 multiplesep sharedmem sharedmem2 sockettest

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

test_test: test_test.o
	${CC} -o -g $@ test_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

forking_test: forking_test.o
	${CC} -o -g $@ forking_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

execve_test: execve_test.o
	${CC} -o -g $@ execve_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

envargs_test: envargs_test.o
	${CC} -o -g $@ envargs_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe_test: pipe_test.o
	${CC} -o -g $@ pipe_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe2_test: pipe2_test.o
	${CC} -o -g $@ pipe2_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe3_test: pipe3_test.o
	${CC} -o -g $@ pipe3_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

multiplesep_test: multiplesep_test.o
	${CC} -o -g $@ multiplesep_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

try_test: try_test.o
	${CC} -o -g $@ try_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

sharedmem_test: sharedmem_test.o
	${CC} -o -g $@ sharedmem_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

sharedmem2_test: sharedmem2_test.o
	${CC} -o -g $@ sharedmem2_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}


sockettest_test: sockettest_test.o
	${CC} -o -g $@ sockettest_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
