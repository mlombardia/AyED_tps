local:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wl,--wrap=malloc -o tp2 *.c
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp2
	rm tp2

docker:
	docker build --tag tp_udesa .
	docker run tp_udesa

clean_docker:
	 bash docker_clean.sh