// a simple way to export your functions
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