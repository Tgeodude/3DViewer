CC = gcc
FlAGS = -std=c11
OS = $(shell uname)
INSTALL_DIR = 3DViewer
ifeq ($(OS), Linux)
  LIBS = -lcheck -lm -lpthread -lsubunit -lrt
  OPEN = xdg-open
else
  LIBS = -lcheck
  OPEN = open
endif

SRCS = sources/parser.c \
       sources/transformations.c \
	   sources/utils.c

OBJS=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: install

install: uninstall
	mkdir build
	rm -rf .tmp
	mkdir .tmp
	cd .tmp/ && qmake ../sources/3DViewer_v1.pro && make && mv 3DViewer_v1.app ../build/3DViewer_v1.app
	rm -rf .tmp

uninstall:
	rm -rf build

clean:
	rm -rf reports
	rm -f *.tar *.a *.gcno *.gcda tests
	cd sources && rm -f *.gcno *.gcda gcov_report *.o *.a

dvi:
	cd readme && $(OPEN) readme.html

dist:
	rm -rf 3DViewer_v1.tar
	tar -cf 3DViewer_v1.tar readme sources objects Makefile 

tests: 3dviewer.a
	$(CC) $(FLAGS) tests.c 3dviewer.a $(LIBS) -o tests
	./tests

gcov_report: add_coverage_flag tests
	rm -rf reports/
	mkdir reports
	./tests
	rm -rf tests*.gcda tests*.gcno
	gcov -b -l -p -c *.gcno
	gcovr -o gcov_report.html --html --html-details
	rm -rf sources/*.gcda sources/*.gcno
	mv *html reports/
	mv *css reports/
	$(OPEN) reports/gcov_report.html

add_coverage_flag:
	$(eval FLAGS += --coverage)

3dviewer.a: $(OBJS)
	ar rcs 3dviewer.a $^
	ranlib 3dviewer.a
	rm -rf sources/*.o
