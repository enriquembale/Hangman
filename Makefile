CC = gcc
CFLAGS = -Wall -g

SRCDIR = src
BUILDDIR = build

TARGET = $(BUILDDIR)/hangman
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

.PHONY: all clean clean_objs

all: $(TARGET) clean_objs

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)


clean_objs:
	rm -f $(BUILDDIR)/*.

clean:
	rm -rf $(BUILDDIR)