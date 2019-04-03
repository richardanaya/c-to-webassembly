#define export __attribute__((visibility("default")))
extern unsigned char __heap_base;

export void *get_heap_base() { return &__heap_base; }

export int add(int x, int y) { return x + y; }

export int sub(int x, int y) { return x - y; }
