CXX = g++
ifeq ($(OS),Windows_NT)
	CXXFLAGS = -std=c++17 -Wall -Wextra
    LDFLAGS = -I"C:/msys64/mingw64/include" -L"C:/msys64/mingw64/lib" -licuuc -licudt
else 
	CXXFLAGS = -Wall -Wextra -std=c++17 $(shell pkg-config --cflags icu-uc)
	LDFLAGS = $(shell pkg-config --libs icu-uc)
endif

TARGET = freq
SOURCES = *.cpp

all: $(TARGET)

$(TARGET) : $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean: 
	rm -f $(TARGET)