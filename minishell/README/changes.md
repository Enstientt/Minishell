# Old version:
    - use a tmp to fill the list: add a node if needed.
        + this action causes the problem of filll just the tmp; and when freeing the tmp it will affect also the ariginal list.
# New version: 
    - Update the lexer from void return value to a ptr lisked list, this ptr holsd the head of the original list after fill it derectly withoud using a tmp;
    + This method will be the new method of fill / make changes in on the list.
    