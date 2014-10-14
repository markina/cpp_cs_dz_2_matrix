compile:
	g++ -Wall -g -o main main.cpp matrix.cpp
run:
	./main t23 --add t23

valgrind_invalid_operation:
	valgrind ./main t23 --a t34

valgrind_odd_size:
	valgrind ./main t23 --add t34 --mult

valgrind_faile_add:
	valgrind ./main t23 --add t34

valgrind_faile_mult:
	valgrind ./main t23 --mult t23

valgrind_faile_mult_2:
	valgrind ./main t23 --mult t48

valgrind_good_mult:
	valgrind ./main t23 --mult t34

valgrind_good_mult_2:
	valgrind ./main t23 --mult t35

valgrind_good_add:
	valgrind ./main t23 --add t23

valgrind_good_add_m:
	valgrind ./main t23 --add t23 --add t23 --add t23

valgrind_good_complex:
	valgrind ./main t23 --mult t34 --add t24 --mult t48

all_valgrind_test:
	valgrind ./main t23 --a t34
	valgrind ./main t23 --add t34 --mult
	valgrind ./main t23 --add t34
	valgrind ./main t23 --mult t23
	valgrind ./main t23 --mult t48
	valgrind ./main t23 --mult t34
	valgrind ./main t23 --mult t35
	valgrind ./main t23 --add t23
	valgrind ./main t23 --add t23 --add t23 --add t23
	valgrind ./main t23 --mult t34 --add t24 --mult t48

invalid_operation:
	./main t23 --a t34

odd_size:
	./main t23 --add t34 --mult

faile_add:
	./main t23 --add t34

faile_mult:
	./main t23 --mult t23

faile_mult_2:
	./main t23 --mult t48

good_mult:
	./main t23 --mult t34

good_mult_2:
	./main t23 --mult t35

good_add:
	./main t23 --add t23

good_add_m:
	./main t23 --add t23 --add t23 --add t23

good_complex:
	./main t23 --mult t34 --add t24 --mult t48

not_first_file:
	./main tttt23 --mult t34 --add t24 --mult t48

not_file:
	./main t23 --mult t34 --add tnononon24 --mult t48
