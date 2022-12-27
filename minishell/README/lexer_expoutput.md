minishell $> echo "This is a sentence between quotes" > Quoted | cat Quoted | ls -l 
---- Node 0 ----
Lexeme: echo
Type: -1

---- Node 1 ----
Lexeme: "This is a sentence between quotes"
Type: 34

---- Node 2 ----
Lexeme: >
Type: 62

---- Node 3 ----
Lexeme: Quoted
Type: -1

---- Node 4 ----
Lexeme: |
Type: 124

---- Node 5 ----
Lexeme: cat
Type: -1

---- Node 6 ----
Lexeme: Quoted
Type: -1

---- Node 7 ----
Lexeme: |
Type: 124

---- Node 8 ----
Lexeme: ls
Type: -1

---- Node 9 ----
Lexeme: -l
Type: -1