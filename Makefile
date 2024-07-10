CFLAGS=-std=c99 -Wpedantic -Wall -Wextra -Wshadow

TARGET=supervisor
OBJECT=io.o main.o mfp.o opt.o osPRNG.o psjf.o scheduler.o

all:$(TARGET)

$(TARGET):$(OBJECT)
	$(CC) $(CFLAGS) -o $@ $(OBJECT) $(LDLIBS)

clean:
	rm -f $(OBJECT) $(TARGET)

.SUFFIXES: .c .rl .svg

.rl.c:
	ragel -G2 $<
.rl.svg:
	ragel -pV $< | dot -Tsvg > $@
