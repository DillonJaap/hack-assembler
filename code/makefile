TARGET = assembler.a
CC = gcc

# compiling flags here
CFLAGS = -std=c99 -Wall -I. -g

LINKER   = gcc

# linking flags here
LFLAGS   = -Wall -I. -lm -g -std=c99

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = build
BINDIR   = .

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"
