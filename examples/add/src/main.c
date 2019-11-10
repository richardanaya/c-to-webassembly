// a simple way to export your functions
#define export __attribute__((visibility("default")))

export int add(int x, int y) { return x + y; }
