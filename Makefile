CC = g++
CFLAGS = -std=c++11 -g -Wall -Wextra
SRCS = main.cpp GuiNinc.cpp
TARGET = SecureCam

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

all: $(TARGET)

$(TARGET):$(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	$(RM) $(TARGET) *.o
