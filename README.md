# C to Web Assembly

This is a simple project for compiling C with `clang` and `llvm` to web assembly. This is a more direct approach than using `https://emscripten.org/`, but still has much value for learning.

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

```C
#define export __attribute__((visibility("default")))
typedef double JSValue;
extern int jsffiregister(char*);
extern void jsfficall1(JSValue,int,int,JSValue);


JSValue const UNDEFINED = 0.0;
int const TYPE_STRING = 2;

export int main() {
	int log = jsffiregister("window.alert");
	jsfficall1(UNDEFINED,log,TYPE_STRING,(JSValue)(int)&"Hello World!");
	return 0;
}
```
