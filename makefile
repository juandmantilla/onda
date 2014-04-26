graph_onda.py : data.dat
	python graph_onda.py
data.dat : a.out
	./a.out
a.out : onda.c
	cc onda.c -lm
clean :  
	rm  data.dat a.out