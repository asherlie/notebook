CXX=gcc
all: nb
nb:
	$(CXX) notebook.c -w -o nb
clean:
	rm -rf nb
