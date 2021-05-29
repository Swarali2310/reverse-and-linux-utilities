**reverse folder has the code and test cases for reversing the program line by line.**

GOAL : The goal of the reversing program is to read in the data from the specified input file and reverse it; thus, the lines should be printed out in the reverse order of the input stream. Reverse can be invoked in any of the three ways :-

./reverse <input from stdin till EOF (Ctrl + D) encountered> --> output printed on stdout
./reverse --> reverses the contents of input file and prints output on stdout
./reverse --> reverses the content of input file and prints it in the output file

**utilities folder has 4 utilites: wcat, wgrep, wzip, wunzip and test cases.** 

GOAL : 

_wcat_ : print the file contents on the command line wcat can be invoked in the following way :-
./wcat file1 [file2 ...] --> this prints all the contents of all the files provided

_wgrep_ : looks through file/stdin line by line and and tries to find a user specified search term in the line wgrep can be invoked in the following way :- 
./wgrep [file ..] --> this will search the search term in the files and print out the matching lines. If no files specified, it will read from stdin line by line and then print the matching lines

_wzip_ and _wunzip_ are pair tools (file compression and decompression tools):- wzip uses Run Length Encoding - 4 bytes count, 1 byte char encoding format
./wzip file1 [file2 ...] > file.z 
./wunzip file.z [file1.z ..]
