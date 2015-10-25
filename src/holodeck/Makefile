include ../Makefile.inc

GEN_EXE = test forking execve envargs pipe pipe2 pipe3 multiplesep

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

execve_test: execve_test.o
	${CC} -o $@ execve_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

envargs_test: envargs_test.o
	${CC} -o $@ envargs_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe_test: pipe_test.o
	${CC} -o $@ pipe_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe2_test: pipe2_test.o
	${CC} -o $@ pipe2_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

pipe3_test: pipe3_test.o
	${CC} -o $@ pipe3_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

multiplesep_test: multiplesep_test.o
	${CC} -o $@ multiplesep_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

try_test: try_test.o
	${CC} -o $@ try_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
