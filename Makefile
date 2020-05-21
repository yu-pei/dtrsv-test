DPLASMADIR=/home/ypei2/sandbox/master/dplasma/build/install
PARSECDIR=/home/ypei2/sandbox/master/dplasma/build/install
#DPLASMADIR=/lustre/project/k1339/peiy/dplasma/build/install_dir
#PARSECDIR=/lustre/project/k1339/peiy/dplasma/build/install_dir

PARSEC_PKGCONFIG=${PARSECDIR}/lib64/pkgconfig
DPLASMA_PKGCONFIG=${DPLASMADIR}/lib64/pkgconfig

export PKG_CONFIG_PATH+="${DPLASMA_PKGCONFIG}:${PARSEC_PKGCONFIG}"

CC = gcc
#CC = cc
MPICC=mpicc
SMKL=$(MKLDIR) -Wl,-Bstatic -Wl,--start-group -lmkl_scalapack_lp64 -lmkl_blacs_openmpi_lp64 -lmkl_sequential -lmkl_gf_lp64 -lmkl_core -Wl,--end-group -Wl,-Bdynamic -ldl -lm
#SMKL= -I${MKLROOT}/include/intel64/lp64 -mkl=sequential ${MKLROOT}/lib/intel64/libmkl_blas95_lp64.a ${MKLROOT}/lib/intel64/libmkl_lapack95_lp64.a -lmkl_scalapack_lp64 -lmkl_blacs_intelmpi_lp64 -lpthread -lm -ldl

CFLAGS  = $(shell pkg-config --cflags dplasma)
LDFLAGS = $(shell pkg-config --libs dplasma)
CFLAGS += $(shell pkg-config --cflags mkl-dynamic-lp64-seq)
LDFLAGS += $(shell pkg-config --libs mkl-dynamic-lp64-seq)
CFLAGS += -I/home/ypei2/sandbox/master/dplasma/src/include -I/home/ypei2/sandbox/master/dplasma/src -I/home/ypei2/sandbox/master/dplasma/build/src/include -I/home/ypei2/sandbox/master/dplasma/build/src
#CFLAGS += -I/lustre/project/k1339/peiy/dplasma/src/include -I/lustre/project/k1339/peiy/dplasma/src -I/lustre/project/k1339/peiy/dplasma/build/src/include -I/lustre/project/k1339/peiy/dplasma/build/src

LDFLAGS += -Wl,-rpath,$(DPLASMADIR)/lib64 $(DPLASMADIR)/lib64/libparsec.so $(DPLASMADIR)/lib64/libdplasma.so

PTGPP = ${PARSECDIR}/bin/parsec-ptgpp
PTGPPFLAGS =

TESTS = testing_dtrsm
PTESTS = pdtrsm

all:${TESTS} ${PTESTS}

JDFS += dtrsm_LLN.jdf dtrsm_LLT.jdf
GENERATED_SRC = $(subst .jdf,.c,${JDFS})
GENERATED_HDR = $(subst .jdf,.h,${JDFS})
GENERATED_OBJ = $(subst .jdf,.o,${JDFS})

%.c %.h: %.jdf
	${PTGPP} -E -i $< -o `basename $@ .c` ${PTGPPFLAGS}

%.o: %.c
	${CC} -o $@ -c $< ${CFLAGS}

common.o: common.c
	${CC} -o $@ -c $< ${CFLAGS}

testing_dtrsm.o: testing_dtrsm.c dtrsm_LLN.c dtrsm_LLT.c dtrsm_wrapper.c
	${CC} -o $@ -c $< ${CFLAGS}

testing_dtrsm: testing_dtrsm.o dtrsm_LLN.o dtrsm_LLT.o  dtrsm_wrapper.o common.o
	${CC} -o $@ $^ ${LDFLAGS}

common_scalapack.o: common_scalapack.c
	${CC} -o $@ -c $< ${CFLAGS}

pdtrsm: pdtrsm.o common_scalapack.o
	${MPICC} -o $@ $^ ${SMKL}
#pdtrsm: pdtrsm.o common_scalapack.o
#	${CC} -o $@ $^ ${SMKL}

clean:
	rm -f *.o ${TESTS} ${PTESTS} ${GENERATED_OBJ} ${GENERATED_HDR} ${GENERATED_SRC}

