// a simple way to export your functions
#define export __attribute__((visibility("default")))

// you would use this variable to write your own malloc/free
extern unsigned char __heap_base;

export void *get_heap_base() { return &__heap_base; }

export int add(int x, int y) { return x + y; }
