#Sample Makefile

CFLAGS=-g -O0

all:	check

default: check

clean-ckpt:
	rm -rf myckpt

clean: clean-ckpt
	rm -rf hello rem libckpt.so


libckpt.so: libckpt.c
	gcc -std=gnu99 -shared -fPIC -o libckpt.so libckpt.c

res: myRestart.c
	gcc -std=gnu99 ${CFLAGS} -g -static -Wl,-Ttext-segment=5000000 -Wl,-Tdata=5100000 -Wl,-Tbss=5200000 -o rem myRestart.c


restart: res
	./rem myckpt

gdb:
	gdb --args ./myRestart myckpt

check:	clean-ckpt libckpt.so hello
	(sleep 3 && kill -12 `pgrep -n hello` && sleep 2 && pkill -9 hello) &
	LD_PRELOAD=`pwd`/libckpt.so ./hello
	(sleep 2 &&  pkill -9 rem)

dist:
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar
