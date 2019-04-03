#define export __attribute__((visibility("default")))

export int add(int x, int y) {
  return x + y;
}

export int sub(int x, int y) {
  return x - y;
}
