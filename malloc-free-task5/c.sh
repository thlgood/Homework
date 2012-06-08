#!/bin/bash

gcc -o  	all 			\
			main.c 			\
			mem_free.c 		\
		  	mem_allocate.c 	\
			common.h -g
