SRCTEST     =     test.cc 
SRC         =     test.cc
CC          =     g++ -std=c++17
LIBCHECK    =     -lgtest
TESTF       =     test.cc
PUSHCOMMENT =     "finish"
EXETEST     =     test
O           =     leaks
clean       =     clean
OS          =     $(shell uname -s)

.PHONY:
	clean rebuild test leaks all default

ifeq ($(OS), Linux)
	O = valgrind
endif

default: test

all: test gcov_report



$(clean):
	rm -rf *.txt test valgrind leaks *.dSYM *.out *.cfg
	rm -rf *.gcno *.gcda *.gcov *.info report
	rm -rf *.o *.a

lint:
	cp ../materials/linters/CPPLINT.cfg . 
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp
	rm -f CPPLINT.cfg

gcov_report: test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html
	

leaks: $(clean)
	$(CC)   $(TESTF) $(LIBCHECK)  -o leaks 
	leaks  -atExit -- ./leaks > result.txt
	
	
test: $(clean)
	$(CC) --coverage $(SRCTEST) -o $(EXETEST) $(LIBCHECK)
	./$(EXETEST)


memory: $(clean) $(O)


rebuild: clean all
