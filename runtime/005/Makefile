CXX=clang
CFLAGS=-O2 -Xclang -disable-O0-optnone -flto -use-gold-plugin -Wl,-plugin-opt=save-temps
CFLAGS=-flto -use-gold-plugin -Wl,-plugin-opt=save-temps -Xclang -disable-O0-optnone -O2

TARGET=aproflib


aproflib.o: aproflib.c
	${CXX} ${CFLAGS} -c aproflib.c -o aproflib.o


clean:
	rm -rf *.o ${TARGET}