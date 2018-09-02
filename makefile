CC = g++
CFLAGS = -g -Wall -std=c++1z -w
DEPS = Listing.h Cursor.h Command.h ExecuteCmd.h
OBJ = Cursor.o list.o Main.o Command.o ExecuteCmd.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
