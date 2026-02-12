#*****************************WINDOWS VERSION of Makefile
# This is a comment

# The Makefile is named Makefile with no extension and should be in the SAME folder as your source files.
# Then, open your command prompt in this folder.

# If typing make in command prompt gives error that make is unknown, you need to rename the make executable in the mingw/bin folder

# Type "make" (without the double quotes) in command prompt or terminal to compile your program
# Type "make run" (without the double quotes) in command prompt to run your program
# Type "make clean" (without the double quotes) in command prompt to delete the executable file

#remember - do not use spaces in the rules - TABS only!

#Default rule - the first rule listed in the Makefile. It's the entry point for the build process. 
#It's the rule that "make" will execute when you just type make with no arguments.
all:		PetAdoption


# The rule below will compile the program if driver.cpp and functions.cpp exists.
PetAdoption: Driver.cpp
			g++ -Wall -o petadoption Driver.cpp

# Execute the rule below with "make run" (without the double quotes), which will run the program if the petadoption executable exists.
run:		petadoption.exe
			petadoption

# Execute the rule below with "make clean" (without the double quotes), which will delete the executable file petadoption if it exists.	
clean:		petadoption.exe	
			del petadoption.exe
	