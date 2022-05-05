CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL2 -lGLU -lGL -lm -lSDL2_image -lstdc++ 



BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/


# Fichiers
EXEC_GEORGES= georges.out

OBJ_GEORGES := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(wildcard $(SRCDIR)georges/*.cpp))

# Regles compilation

all : georges

georges : $(OBJ_GEORGES)
	$(CC) $(CFLAGS) $(OBJ_GEORGES) -o $(BINDIR)$(EXEC_GEORGES) $(LDFLAGS)



clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*


$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)


