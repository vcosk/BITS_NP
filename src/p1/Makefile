include ../Makefile.inc

GEN_EXE = shell

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}
shell_test: shell_test.o
		${CC} -w -o -g $@ shell_test.o ${CFLAGS} ${LDLIBS} ${LINUX_LIBRT}

${EXE} : ${LPLIB}		# True as a rough approximation
