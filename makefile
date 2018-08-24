CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = Listing.h
OBJ = list.o Main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
