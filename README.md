# C to Web Assembly

This is a simple project for compiling C with `clang` and `llvm` to web assembly. This is a more direct approach than using [Emscripten](https://emscripten.org/) that comes with the trade off of not having standard library but also knowing exactly what is happening.

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

My suggestion is starting with [`basic`](https://github.com/richardanaya/c-to-webassembly/blob/master/examples/basic/)

# Interacting with the browser

Web assembly comes with no built in ability to interact with the browser. You must create expose your own functions from javascript to your web assembly module to do anything. Nevertheless, a project [`js_ffi`](https://www.github.com/richardanaya/js_ffi) has a standardized interface that can be used for many actions.

The header file can be found [here](https://github.com/richardanaya/js_ffi/blob/master/js_ffi.h)

```C
#define export __attribute__((visibility("default")))
#include "./js_ffi.h"

export int main() {
	int log = jsffiregister("window.alert");
	jsfficall1(UNDEFINED,log,TYPE_STRING,(JSValue)(int)&"Hello World!");
	return 0;
}
```
