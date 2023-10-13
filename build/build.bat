gcc -c containers.c -o ./build/containers.o -fPIC
gcc -shared -o ./build/containers.so ./build/containers.o