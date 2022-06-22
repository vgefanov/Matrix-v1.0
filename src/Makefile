CC=gcc
CFLAGS=-Wall -Wextra -Werror
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	LEAKS=CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test.out
else
	LIBS=-lcheck
	LEAKS=CK_FORK=no leaks --atExit -- ./test.out
endif

all: clean s21_matrix.a test

test: clean s21_matrix.a
	$(CC) -g s21_matrix_test.c s21_matrix.a $(LIBS) -o test.out
	./test.out

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) --coverage -c s21_matrix.c
	ar rc s21_matrix.a *.o
	$(CC) $(CFLAGS) s21_matrix_test.c -L. s21_matrix.a -lcheck -lpthread -lm -lgcov -o test_cov
	rm -rf *.o
	./test_cov
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	mkdir -p ./report
	genhtml -o report gcov_report.info
	open ./report/index.html

s21_matrix.a: clean
	$(CC) -c s21_matrix.c -o s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

clean:
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM *.gch *.o .vscode .DS_Store s21_matrix.c.gcov test_cov CPPLINT.cfg s21_matrix ../.DS_Store ../.vscode a.out

leaks: clean test
	$(LEAKS)

codestyle:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21_matrix.c *.c *.h
