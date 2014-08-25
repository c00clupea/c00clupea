test_addon := -DUSEC00TESTS -DWRITEC00CRAP

CC := gcc -std=c99


alltest:
	make clean
	make clean_test
	make create_test
	make c00_hashmap_test
	make c00_array_list_test
	make c00_linked_list_test

clean:
	rm -f c00_hashmap_test
	rm -f c00_array_list_test
	rm -f c00_linked_list_test
	rm -f *.o

run_test:
	sh run_test.sh > testrun.log

clean_test:
	rm -f run_test.sh

create_test:
	touch run_test.sh
	echo "#!/bin/sh" >> run_test.sh
	chmod +x run_test.sh
	echo "./c00_hashmap_test" >> run_test.sh
	echo "./c00_array_list_test" >> run_test.sh
	echo "./c00_linked_list_test" >> run_test.sh

c00_hashmap_test:../src/util/c00_hashmap.c
	${CC} ${test_addon} -c ../src/util/c00_hashmap.c
	${CC} ${test_addon} -o c00_hashmap_test c00_hashmap.o


c00_array_list_test:../src/util/c00_array_list.c
	${CC} ${test_addon} -c ../src/util/c00_array_list.c
	${CC} ${test_addon} -o c00_array_list_test c00_array_list.o

c00_linked_list_test: ../src/util/c00_linked_list.c
	${CC} ${test_addon} -c -g ../src/util/c00_linked_list.c
	${CC} ${test_addon} -g -o c00_linked_list_test c00_linked_list.o
