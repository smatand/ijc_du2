### IJC - Project 2
*Part 1 - Printing tail of text file  
Part 2 - Counting occurences of words in text file using hash tables*
  
Type `make` to compile.  

Part 1
-
Usage of tail:  `./tail [-n] file` or `./tail [-n] <file` , where the `n` option is by default 10.  
  
Try `./tail -n15 file` to print last 15 lines of a file.  
*Warning: `./tail` does not work using pipe such as `cat file | ./tail -n1`*.  

Part 2
-
Usage of wordcount: `./wordcount file` or `./wordcount <file`  
  
`./wordcount` prints to stdout number of occurences of each word from a given file or stdin. Word is any text separated by spaces.
