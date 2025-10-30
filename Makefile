CC      = clang
CFLAGS  = -O3 -Wall
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

SRC    = $(wildcard *.c)
OBJDIR = build
TARGET = $(OBJDIR)/main

.PHONY = clean run

$(TARGET): $(SRC)
	mkdir -p $(OBJDIR) && \
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -r $(OBJDIR)/*

run: $(TARGET)
	$^
