
CC = g++
CFLAGS = -std=c++11

# The build target 
TARGET = main
HC1 = HuffmanTree
HC2 = ByteBuffer
 
all: $(TARGET)

$(TARGET): $(TARGET).o $(HC1).o $(HC2).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o $(HC1).o $(HC2).o

$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

$(HC1).o: $(HC1).h $(HC1).cpp
	$(CC) $(CFLAGS) -c $(HC1).h $(HC1).cpp

$(HC2).o: $(HC2).h $(HC2).cpp
	$(CC) $(CFLAGS) -c $(HC2).h $(HC2).cpp

clean:
	rm -f *.o