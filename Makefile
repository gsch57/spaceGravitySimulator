# Compiler
CC      = clang++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11

# Linker flags
LDFLAGS = -Llib -lSDL2-2.0.0

# Directories
SRCDIR  = src
INCDIR  = include
OBJDIR  = obj
BINDIR  = bin

# Target executable name
TARGET  = play

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Main source file
MAIN_SRC := main.cpp

# Main object file
MAIN_OBJ := $(OBJDIR)/main.o

# Remove command
RM      = rm -f

# Build target
$(BINDIR)/$(TARGET): $(OBJECTS) $(MAIN_OBJ) | $(BINDIR)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile main source file
$(MAIN_OBJ): $(MAIN_SRC) | $(OBJDIR)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Compile sources
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean objects and executables
clean:
	$(RM) $(OBJECTS) $(MAIN_OBJ)

# Clean all
fclean: clean
	$(RM) $(BINDIR)/$(TARGET)
	$(RM) -r $(OBJDIR)

# Rebuild
re: fclean all

# Build all
all: $(BINDIR)/$(TARGET)

# PHONY targets
.PHONY: all clean fclean re