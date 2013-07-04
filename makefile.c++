all:
	make Integer.zip

clean:
	rm -f Integer.log
	rm -f Integer.zip
	rm -f RunInteger
	rm -f RunInteger.tmp
	rm -f TestInteger

diff: RunInteger RunInteger.out
	RunInteger > RunInteger.tmp
	diff RunInteger.out RunInteger.tmp
	rm RunInteger.tmp

doc: Integer.h
	doxygen Doxyfile

turnin-list:
	turnin --list dlessin cs378pj3

turnin-submit: Integer.zip
	turnin --submit dlessin cs378pj3 Integer.zip

turnin-verify:
	turnin --verify dlessin cs378pj3

Integer.log:
	git log > Integer.log

Integer.zip: Integer.h Integer.log RunInteger.c++ RunInteger.out TestInteger.c++ TestInteger.out
	zip -r Integer.zip html/ Integer.h Integer.log RunInteger.c++ RunInteger.out TestInteger.c++ TestInteger.out

RunInteger: Integer.h RunInteger.c++
	g++ -pedantic -std=c++0x -Wall RunInteger.c++ -o RunInteger

RunInteger.out: RunInteger
	valgrind RunInteger > RunInteger.out

TestInteger: Integer.h TestInteger.c++
	g++ -pedantic -std=c++0x -Wall TestInteger.c++ -o TestInteger -lcppunit -ldl

TestInteger.out: TestInteger
	valgrind TestInteger > TestInteger.out
