clean:
	rm -f *.out
run: clean
	 g++ main.cpp classes.cpp -o run.out && ./run.out
test: clean
	g++ test.cpp classes.cpp -o test.out && ./test.out