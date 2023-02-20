# Pthreads examples

This repo contains several pthread examples on how to create, join, detach and synchronize threads in the C language.
To compile any of these you'll need to explicitly include the pthread library in the compile statement, for example to compile and run **threadsEx0.c**
```console
gcc -pthread threadsEx0.c -o threadEx0
```
The threadsJoinEx.c file uses the functions of sin() tan() so it needs the -lm option.
```console
gcc threadsJoinEx.c –lpthread –lm –o threadsJoinEx
```
