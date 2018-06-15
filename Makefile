CXX=gcc
all: nb
nb:
	$(CXX) notebook.c -w -o nb -O2
clean:
	rm -rf nb
