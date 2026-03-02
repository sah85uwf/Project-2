# Sophia Herrmann

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = rr_scheduler
SRCS = main.cpp Process.cpp Scheduler.cpp
OBJS = $(SRCS:.cpp=.o)

all: run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) 26S_COP4610_Project2_InputFile1.txt
	./$(TARGET) 26S_COP4610_Project2_InputFile2.txt
	./$(TARGET) 26S_COP4610_Project2_InputFile3.txt
	./$(TARGET) 26S_COP4610_Project2_InputFile4.txt


clean:
	rm -f $(TARGET) $(OBJS)
