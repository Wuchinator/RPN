CC = gcc 
FLAGS = -Werror -Wall -Wextra 
PATH1 = ../build/graph


graph : stack.c rpn_exe.c parser.c graph.c get_func.c
	$(CC) $(FLAGS) -c stack.c rpn_exe.c parser.c graph.c get_func.c
	$(CC) $(FLAGS) *.o -o $(PATH1)



all : 
	make graph
	rm *.o

clean :
	rm *.o ../build/*

rebuild : 
	make clean
	make all
