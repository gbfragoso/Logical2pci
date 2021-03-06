# Logical2pci
This projects aims to receive an well formed formula of the proposional logic and, after some steps, convert it into equivalent
pcode instructions.

# Steps
1. Catch the logical expression from input;
2. Running it in a pushdown automata;
3. Use result of step 2 to build a binary tree;
4. Run postorder transversal at btree to build reverse polish notation;
5. Convert RPN into valid Pcode instructions;
6. Run pcode and then generate output file;

# Grammar (Greibach normal form)
```
E -> 0 | 1 | p | q | !E | (EAEB
A -> & | | | : | - 
B -> )
```
Note: Your program do not assign value to p and q, although accept it.

# Codes for logical conectives and semantic
| Conective | Code | Semantic |
|--- | --- |----|
| ^ | & |AND
| v | \| |OR
| ¬ | ! |NOT
| ->| : |IMPLICATION 
|<->| \- |BICONDITIONAL
| F |  0  | FALSE
| T |  1  | TRUE

# Pushdown Automata
![Figure 1. Pushdown Automata](./pushdown2.png)

# Compilation
> gcc -o teste ada2asa.c pcode.c rpn2pci.c btree2rpn.c pushdown.c main.c

# Running example
> ./teste "expression"

# Assumption
* For successful conversion the user must provide a balanced logical expression.

# Examples
See ![Example 1](./output.txt) and ![Example 2](./output2.txt) file on repo.
