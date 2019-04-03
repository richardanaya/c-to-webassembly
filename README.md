# llvm-8-wasm

This is a simple project for compiling C with clang and llvm 8 to web assembly

First you will need to install dependencies:

add to your sources appropriate sources 

```console
sudo vim /etc/apt/sources.list
```

choose the right sources from http://apt.llvm.org/


```console
sudo apt-get update
sudo apt-get install llvm-8
sudo apt-get install wasm-ld-8
sudo apt-get install lld-8
sudo apt-get install clang-8
```

Now you should be ready to build

```
make
```
