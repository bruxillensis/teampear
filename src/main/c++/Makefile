CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I.
LIBS = -lstdc++
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET_DIR = ../../../target/bin
OBJ = $(TARGET_DIR)/main.o
MAIN = astaro
RM = rm

all: $(MAIN)
	@echo Successfully compiled team-pear project.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCUDLES) -o $(TARGET_DIR)/$(MAIN) $(OBJ) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCUDLES) -c $< -o $(TARGET_DIR)/$@

clean:
	$(RM) $(TARGET_DIR)/*.o $(TARGET_DIR)/$(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^