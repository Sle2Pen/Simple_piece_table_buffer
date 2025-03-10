LIBRARY = ../piece_table.so
TEST_PROGRAM = text_buffer_tests

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -std=c11
DIN_LIBRARY = $(CFLAGS) -fPIC
CLIBS = -L. $(LIBRARY)

CHECK_LIB = -lcheck -lrt -lm -lsubunit 

SOURCE = piece_table.c 
OBJECTS = piece_table.o 

# TEST_SOURCE = tests/text_buffer_checking.c tests/text_buffer_create_tests.c tests/text_buffer_insert_from_tests.c tests/text_buffer_character_from_tests.c tests/text_create_tests.c tests/text_calculate_size_tests.c tests/text_copy_tests.c
# TEST_OBJECTS = text_buffer_checking.o text_buffer_create_tests.o text_buffer_insert_from_tests.o text_buffer_character_from_tests.o text_create_tests.o text_calculate_size_tests.o text_copy_tests.o

# GCOV_FLAGS = --coverage
# GCOV_REPORT_DIR = tests/gcov_report
# GCOV_RESULT = $(GCOV_REPORT_DIR)/text_buffer_checking.c.gcov $(GCOV_REPORT_DIR)/*.gcno $(GCOV_REPORT_DIR)/*.gcda
# BRANCHES = --rc lcov_branch_coverage=1

# all : clean_objects clean_gcov_files clean_report clean_library clean_tests format $(LIBRARY) test gcov_report
all : clean_objects clean_library format $(LIBRARY) copy_header

copy_header :
	cp piece_table.h ../piece_table.h

$(LIBRARY) : format buffer create_library clean_objects

create_library :
	$(CC) $(CFLAGS) -shared $(OBJECTS) -o $(LIBRARY)


buffer : 
	$(CC) $(DIN_LIBRARY) -c piece_table.c  -o piece_table.o


# text :
# 	$(CC) $(DIN_LIBRARY) -c text_buffer/text.c -o text.o

# test : $(LIBRARY) build_tests $(TEST_PROGRAM) run_tests clean_objects 
	
# build_tests : text_buffer_checking text_create_tests text_calculate_size_tests text_copy_tests text_buffer_create_tests text_buffer_insert_from_tests text_buffer_character_from_tests

# run_tests:
# 	./$(TEST_PROGRAM)

# $(TEST_PROGRAM) : 
# 	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_PROGRAM) $(CLIBS) $(CHECK_LIB)

# text_buffer_checking :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_checking.c -o text_buffer_checking.o

# text_create_tests :
# 	$(CC) $(CFLAGS) -c tests/text_create_tests.c -o text_create_tests.o

# text_calculate_size_tests :
# 	$(CC) $(CFLAGS) -c tests/text_calculate_size_tests.c -o text_calculate_size_tests.o

# text_copy_tests :
# 	$(CC) $(CFLAGS) -c tests/text_copy_tests.c -o text_copy_tests.o

# text_buffer_create_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_create_tests.c -o text_buffer_create_tests.o

# text_buffer_character_from_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_character_from_tests.c -o text_buffer_character_from_tests.o

# text_buffer_insert_from_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_insert_from_tests.c -o text_buffer_insert_from_tests.o



# gcov_report: clean_tests format build_report call_report create_coverage_info clean_gcov_files clean_objects

# build_report :
# 	$(CC) $(CFLAGS) $(TEST_SOURCE) $(SOURCE) -o $(TEST_PROGRAM) $(CHECK_LIB) $(GCOV_FLAGS)

# call_report :
# 	./$(TEST_PROGRAM)

# create_coverage_info :
# 	mkdir -p $(GCOV_REPORT_DIR)
# 	lcov -t "Report" -c -d . -o $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)
# 	genhtml -o $(GCOV_REPORT_DIR)/html $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)


# format :
# 	clang-format -i *.c *.h tests/*.c tests/*.h

# clean : clean_objects clean_gcov_files clean_report clean_tests clean_library

# clean_objects :
# 	rm -rf $(OBJECTS) $(TEST_OBJECTS)

# clean_gcov_files :
# 	rm -f *.gcno *.gcda

# clean_report :
# 	rm -rf tests/gcov_report

# clean_tests :
# 	rm -f $(TEST_PROGRAM)

# clean_library :
# 	rm -f $(LIBRARY) *.h

format :
	clang-format -i *.c *.h

clean : clean_objects clean_library

clean_objects :
	rm -rf $(OBJECTS) $(TEST_OBJECTS)

clean_library :
	rm -f $(LIBRARY) ../*.h