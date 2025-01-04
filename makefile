# compiler
CXX = g++

# flags
CXXFLAGS = -O2 -lgmp -lgmpxx

# compile targets
SOURCES = factorizer.cpp
TARGET = factorizer

# i/o files
INPUT = all-moduli.csv
OUTPUT = results.csv

# target
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# running the program
run: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

clean:
	rm -f $(TARGET)

