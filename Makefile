all: homework homework1

homework: homework.c homework.h main.c
	gcc -fopenmp -o homework homework.c homework.h main.c

homework1: homework1.c homework1.h main1.c
	gcc -fopenmp -o homework1 homework1.c homework1.h main1.c

clean:
	rm homework
	rm homework1
	rm out/*
