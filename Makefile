DPLASMADIR=/home/ypei2/sandbox/master/dplasma/build/install
DPLASMA_PKGCONFIG=${DPLASMADIR}/lib64/pkgconfig
PARSECDIR=/home/ypei2/sandbox/master/dplasma/build/install
PARSEC_PKGCONFIG=${PARSECDIR}/lib64/pkgconfig

export PKG_CONFIG_PATH+="${DPLASMA_PKGCONFIG}:${PARSEC_PKGCONFIG}"

CC = gcc

CFLAGS  = $(shell pkg-config --cflags dplasma)
LDFLAGS = $(shell pkg-config --libs dplasma)
CFLAGS += $(shell pkg-config --cflags mkl-dynamic-lp64-seq)
LDFLAGS += $(shell pkg-config --libs mkl-dynamic-lp64-seq)
CFLAGS += -I/home/ypei2/sandbox/master/dplasma/src/include -I/home/ypei2/sandbox/master/dplasma/src -I/home/ypei2/sandbox/master/dplasma/build/src/include -I/home/ypei2/sandbox/master/dplasma/build/src
LDFLAGS += -Wl,-rpath,$(DPLASMADIR)/lib64 $(DPLASMADIR)/lib64/libparsec.so $(DPLASMADIR)/lib64/libdplasma.so

PTGPP = ${PARSECDIR}/bin/parsec-ptgpp
PTGPPFLAGS =

TESTS = testing_dtrsm

all:${TESTS}

JDFS += dtrsm_LLN.jdf
GENERATED_SRC = $(subst .jdf,.c,${JDFS})
GENERATED_HDR = $(subst .jdf,.h,${JDFS})
GENERATED_OBJ = $(subst .jdf,.o,${JDFS})

%.c %.h: %.jdf
	${PTGPP} -E -i $< -o `basename $@ .c` ${PTGPPFLAGS}

%.o: %.c
	${CC} -o $@ -c $< ${CFLAGS}

common.o: common.c
	${CC} -o $@ -c $< ${CFLAGS}

testing_dtrsm.o: testing_dtrsm.c dtrsm_LLN.c
	${CC} -o $@ -c $< ${CFLAGS}

testing_dtrsm: testing_dtrsm.o dtrsm_LLN.o common.o
	${CC} -o $@ $^ ${LDFLAGS}

clean:
	rm -f *.o ${TESTS} ${GENERATED_OBJ} ${GENERATED_HDR} ${GENERATED_SRC}

