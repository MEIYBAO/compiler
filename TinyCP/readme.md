执行命令
```
flex compiler.l
bison -vdty compiler.y
g++ -std=c++11 -o compiler tree.cpp Praser.cpp innerCode.cpp tools.cpp codeOptimize.cpp lex.yy.c y.tab.c
./compiler.exe ./test.c
```
![alt text](image.png)