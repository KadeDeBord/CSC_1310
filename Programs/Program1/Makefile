# this is the Makefile for the Buisiness program
# all you have to do is type the word "make" in the command prompt to compile
# or you can type "make clean" to delete all object & executable files

all			:	Business

Business	:	Business.cpp Driver.cpp RentItem.cpp Game.cpp Text.cpp
			g++ -o Business.exe Business.cpp Driver.cpp RentItem.cpp Game.cpp Text.cpp

clean		:	Business.exe
			del *.o 
			del Business.exe
			
			