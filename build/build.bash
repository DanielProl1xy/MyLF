clang -c containers.c -o ./build/containers.o -fPIC
clang -shared -o ./build/containers.so ./build/containers.o