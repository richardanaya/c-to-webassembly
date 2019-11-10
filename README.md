# C to Web Assembly

This is a simple project for compiling C with `clang` and `llvm` to web assembly

First you will most likely need to install dependencies.

## Ubuntu/Debian
As per the LLVM website https://apt.llvm.org/

```
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
```

## OSX

```
brew install llvm
brew link --force llvm
```

Now you should be ready to build any example by going into their directory and running

```
make
```

My suggestion is starting with [`basic`](https://github.com/richardanaya/c-to-webassembly/blob/master/examples/basic/src/main.c)
