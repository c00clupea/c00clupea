test_addon := -DUSEC00TESTS -DWRITEC00CRAP

alltest:
	make c00_hashmap_test



c00_hashmap_test:../src/util/c00_hashmap.c
	gcc ${test_addon} -c ../src/util/c00_hashmap.c
	gcc ${test_addon} -o c00_hashmap_test c00_hashmap.o
