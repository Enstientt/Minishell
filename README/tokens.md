# Tokenizing the input line or 'CMD'


## input 

```
    * minishell$> echo "Expanding some variables:" PWD=$PWD HOME=$HOME > File | ls -l
```
## Output

```
---- Node 0 ----
Lexeme: echo
Type: -1

---- Node 1 ----
Lexeme:  
Type: -2

---- Node 2 ----
Lexeme: Expanding some variables:
Type: 34

---- Node 3 ----
Lexeme:  
Type: -2

---- Node 4 ----
Lexeme: PWD=
Type: -1

---- Node 5 ----
Lexeme: /home/ahammout/Desktop/Minishell
Type: 36

---- Node 6 ----
Lexeme:  
Type: -2

---- Node 7 ----
Lexeme: HOME=
Type: -1

---- Node 8 ----
Lexeme: /home/ahammout
Type: 36

---- Node 9 ----
Lexeme:  
Type: -2

---- Node 10 ----
Lexeme: >
Type: 62

---- Node 11 ----
Lexeme:  
Type: -2

---- Node 12 ----
Lexeme: File
Type: -1

---- Node 13 ----
Lexeme:  
Type: -2

---- Node 14 ----
Lexeme: |
Type: 124

---- Node 15 ----
Lexeme:  
Type: -2

---- Node 16 ----
Lexeme: ls
Type: -1

---- Node 17 ----
Lexeme:  
Type: -2

---- Node 18 ----
Lexeme: -l
Type: -1

```