myprog.exe  :   project4_GetChange.o getchange.o 
	gcc project4_GetChange.o getchange.o -o myprog.exe
    
project4_GetChange.o   :   project4_GetChange.c getchange.c getchange.h 
	gcc -Wall -c project4_GetChange.c 
    
getchange.o  :   getchange.c getchange.h 
	gcc -Wall -c getchange.c 
    
clean : 
	rm *.o myprog.exe
