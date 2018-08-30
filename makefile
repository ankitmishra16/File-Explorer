CC = g++
CFLAGS = -g -Wall -std=c++1z -w
DEPS = Listing.h Cursor.h
OBJ = Cursor.o list.o Main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
