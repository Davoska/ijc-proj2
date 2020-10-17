# Makefile
# Reseni IJC-DU2, priklad 1) 2), 10. 4. 2020
# Autor: David Hurta, FIT
# Prelozeno: gcc 7.5.0
# Makefile pro prelozeni souboru.

CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra

all: tail wordcount wordcount-dynamic

# ********************************** tail *****************************************************
tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o

# ********************************** wordcount vyuzivajici statickou knihovnu ******************
wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount io.o wordcount.o libhtab.a

wordcount.o: wordcount.c htab.h
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

# ********************************** wordcount vyuzivajici dynamickou knihovnu *****************
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic io.o wordcount.o libhtab.so

# ********************************* io modul **************************************************
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o

# ********************************* Staticka knihovna *****************************************
libhtab.a: htab_hash_fun.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_begin.o htab_end.o htab_iterator_next.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_set_value.o htab_clear.o htab_free.o htab_iterator_valid.o htab_iterator_equal.o
	ar -rc libhtab.a -o htab_hash_fun.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_begin.o htab_end.o htab_iterator_next.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_set_value.o htab_clear.o htab_free.o htab_iterator_valid.o htab_iterator_equal.o
	ranlib libhtab.a

htab_hash_fun.o: htab_hash_fun.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_hash_fun.c -o htab_hash_fun.o

htab_init.o: htab_init.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_init.c -o htab_init.o

htab_size.o: htab_size.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_size.c -o htab_size.o

htab_bucket_count.o: htab_bucket_count.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_bucket_count.c -o htab_bucket_count.o

htab_find.o: htab_find.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_find.c -o htab_find.o

htab_lookup_add.o: htab_lookup_add.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_lookup_add.c -o htab_lookup_add.o

htab_erase.o: htab_erase.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_erase.c -o htab_erase.o

htab_begin.o: htab_begin.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_begin.c -o htab_begin.o

htab_end.o: htab_end.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_end.c -o htab_end.o

htab_iterator_next.o: htab_iterator_next.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_next.c -o htab_iterator_next.o

htab_iterator_get_key.o: htab_iterator_get_key.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_get_key.c -o htab_iterator_get_key.o

htab_iterator_get_value.o: htab_iterator_get_value.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_get_value.c -o htab_iterator_get_value.o

htab_iterator_set_value.o: htab_iterator_set_value.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_set_value.c -o htab_iterator_set_value.o

htab_clear.o: htab_clear.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_clear.c -o htab_clear.o

htab_free.o: htab_free.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_free.c -o htab_free.o

htab_iterator_valid.o: htab_iterator_valid.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_valid.c -o htab_iterator_valid.o

htab_iterator_equal.o: htab_iterator_equal.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -c htab_iterator_equal.c -o htab_iterator_equal.o

# ********************************* Dynamicka knihovna *************************************
libhtab.so: htab_hash_fun-dynamic.o htab_init-dynamic.o htab_size-dynamic.o htab_bucket_count-dynamic.o htab_find-dynamic.o htab_lookup_add-dynamic.o htab_erase-dynamic.o htab_begin-dynamic.o htab_end-dynamic.o htab_iterator_next-dynamic.o htab_iterator_get_key-dynamic.o htab_iterator_get_value-dynamic.o htab_iterator_set_value-dynamic.o htab_clear-dynamic.o htab_free-dynamic.o htab_iterator_valid-dynamic.o htab_iterator_equal-dynamic.o
	gcc -shared -o libhtab.so htab_hash_fun-dynamic.o htab_init-dynamic.o htab_size-dynamic.o htab_bucket_count-dynamic.o htab_find-dynamic.o htab_lookup_add-dynamic.o htab_erase-dynamic.o htab_begin-dynamic.o htab_end-dynamic.o htab_iterator_next-dynamic.o htab_iterator_get_key-dynamic.o htab_iterator_get_value-dynamic.o htab_iterator_set_value-dynamic.o htab_clear-dynamic.o htab_free-dynamic.o htab_iterator_valid-dynamic.o htab_iterator_equal-dynamic.o

htab_hash_fun-dynamic.o: htab_hash_fun.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_hash_fun.c -o htab_hash_fun-dynamic.o

htab_init-dynamic.o: htab_init.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init-dynamic.o

htab_size-dynamic.o: htab_size.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size-dynamic.o

htab_bucket_count-dynamic.o: htab_bucket_count.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count-dynamic.o

htab_find-dynamic.o: htab_find.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find-dynamic.o

htab_lookup_add-dynamic.o: htab_lookup_add.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add-dynamic.o

htab_erase-dynamic.o: htab_erase.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_erase.c -o htab_erase-dynamic.o

htab_begin-dynamic.o: htab_begin.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_begin.c -o htab_begin-dynamic.o

htab_end-dynamic.o: htab_end.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_end.c -o htab_end-dynamic.o

htab_iterator_next-dynamic.o: htab_iterator_next.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_next.c -o htab_iterator_next-dynamic.o

htab_iterator_get_key-dynamic.o: htab_iterator_get_key.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_get_key.c -o htab_iterator_get_key-dynamic.o

htab_iterator_get_value-dynamic.o: htab_iterator_get_value.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_get_value.c -o htab_iterator_get_value-dynamic.o

htab_iterator_set_value-dynamic.o: htab_iterator_set_value.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_set_value.c -o htab_iterator_set_value-dynamic.o

htab_clear-dynamic.o: htab_clear.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear-dynamic.o

htab_free-dynamic.o: htab_free.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free-dynamic.o

htab_iterator_valid-dynamic.o: htab_iterator_valid.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_valid.c -o htab_iterator_valid-dynamic.o

htab_iterator_equal-dynamic.o: htab_iterator_equal.c htab.h hash_table_structs.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_equal.c -o htab_iterator_equal-dynamic.o

# ******************************* clean  ***********************************************
clean:
	-rm *.o libhtab.a tail wordcount libhtab.so wordcount-dynamic