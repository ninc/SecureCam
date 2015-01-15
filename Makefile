CC = g++
CFLAGS = -g -Wall -Wextra
SRCS = main.cpp
TARGET = SecureCam

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

all: $(TARGET)

$(TARGET):$(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	$(RM) $(TARGET) *.o
