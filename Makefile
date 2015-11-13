ARCH_ID=$(shell uname -ms | tr 'A-Z' 'a-z' | sed -e 's,[^a-z0-9_][^a-z0-9_]*,-,')
CFLAGS=-std=c99 -pedantic -Wall
NAME=libsimplesocket
OUTPUT_DIR=output/${ARCH_ID}

all: mac linux-in-vagrant

clean:
	git clean -ffdx

${OUTPUT_DIR}:
	mkdir -p ${OUTPUT_DIR}

linux-in-vagrant:
	vagrant up && vagrant destroy -f

linux: ${OUTPUT_DIR}/${NAME}.so
	gcc ${CFLAGS} -L${OUTPUT_DIR} -o test ${NAME}_test.c -lsimplesocket
	LD_LIBRARY_PATH=${OUTPUT_DIR} ./test
	rm -f test

mac: ${OUTPUT_DIR}/${NAME}.dylib
	clang ${CFLAGS} -L${OUTPUT_DIR} -lsimplesocket -o test ${NAME}_test.c
	./test
	rm -f test

${OUTPUT_DIR}/${NAME}.so: ${OUTPUT_DIR} ${NAME}.c
	gcc ${CFLAGS} -shared -fPIC -o ${OUTPUT_DIR}/${NAME}.so ${NAME}.c

${OUTPUT_DIR}/${NAME}.dylib: ${OUTPUT_DIR} ${NAME}.c
	clang ${CFLAGS} -shared -o ${OUTPUT_DIR}/${NAME}.dylib ${NAME}.c
