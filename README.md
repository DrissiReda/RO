
##Compiling and buidling
*Enter ``` make ``` to compile the project and report in normal mode
*Enter ```make verbose ``` to compile the project in verbose mode
*Enter ```make conv``` to compile edgtoadj converter
##Usage
First download any number of DIMAC instances in .clq format
Then put them in bingraph folder. then run clqtoadj script to convert 
all the .clq files into .mat(adjacency matrices) and .ls (edge lists) files
which would be respectively in adjmat/ and edgls/ folders.
then you can run the main program with the command
```./clique <input-file> [1 for fast/0 for deep mode(defaults at 1)] [maximum size to search for]```

