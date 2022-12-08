lex jac.l
yacc -d -v jac.y
cc -g -Wall -o jac y.tab.c semantic.c lex.yy.c -ll -ly

./jac -t < Echo.ja

./jac < Echo.ja > out.ll

llc-3.8 out.ll
clang-3.8 -o out out.s
./out
