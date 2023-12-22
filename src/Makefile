ifeq ($(shell uname -s),Linux)
    CHECK_FLAGS = $(shell pkg-config --libs gtest --cflags)
endif
ifeq ($(shell uname -s),Darwin)
    CHECK_FLAGS = $(shell pkg-config --libs gtest --cflags)
endif

CC = g++
ADD_FLAG = -std=c++17 --coverage
CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

build: s21_matrix_oop.cc
	$(CC) $(CFLAGS) $(ADD_FLAG) -c s21*.cc

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) $(ADD_FLAG) -c ./test/test.cc
	$(CC) $(ADD_FLAG) -L. s21_matrix_oop.a test.o ${CHECK_FLAGS} -o run_tests
	./run_tests

gcovr_report: test
	mkdir -p report
	./run_tests
	gcovr -r . -e s21_matrix_test.cc --html --html-details -o report/report.html
	open report/report.html

leaks_check: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) $(ADD_FLAG) -c ./test/test.cc
	$(CC) $(ADD_FLAG) -L. s21_matrix_oop.a test.o ${CHECK_FLAGS} -o run_tests
	leaks -atExit -- ./run_tests

# FOR VALGRIND СHECK YOU MUST RUN DOCKER

test_valgrind: clean build
	$(CC) $(CFLAGS) $(ADD_FLAG) -c ./test/test.cc
	$(CC) $(ADD_FLAG) s21_matrix_oop.o test.o ${CHECK_FLAGS} -o run_tests

valgrind_check: 
	cd ../materials/build/Valgrind && bash run.sh

clean:
	rm -rf *.o *.a *.gcno *.gcda run_tests report

git: clean
	git add -A
	git commit -m "$m"
	git push origin "$b"