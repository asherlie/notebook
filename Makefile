CXX=gcc
all: nb
nb:
	$(CXX) notebook.c -o nb
clean:
	rm -rf nb
