
## Compiling and buidling
* Enter ``` make ``` to compile the project and report in normal mode
* Enter ```make verbose ``` to compile the project in verbose mode
* Enter ```make conv``` to compile edgtoadj converter
## Usage
1. First download any number of [DIMAC](https://turing.cs.hbg.psu.edu/txn131/clique.html) instances in __.clq__ format
1. Then put them in bingraph folder. then run __clqtoadj__ script to convert 
all the .clq files into __.mat__(adjacency matrices) and __.ls__ (edge lists) files. <br>
1. You can use the command 
  ```./clqtoadj bingraph/* ```
 to convert all __.clq__ files in __bingraph__. The resulting adjacency matrices and edge lists would be respectively in __adjmat/__ and __edgls/__ folders.
1. then you can run the main program with the command <br>
```./clique <input-file> [1 for fast/0 for deep mode(defaults at 1)] [maximum size to search for]```

