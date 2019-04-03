build:
	mkdir -p tmp/src
	clang-8 src/main.c -S -emit-llvm --target=wasm32 -o tmp/src/main.ll
	llvm-link-8 -o tmp/main.bc tmp/src/*\.ll
	opt-8 -O3 tmp/main.bc -o tmp/main.bc
	llc-8 -mtriple=wasm32-unknown-unknown -O3 -filetype=obj tmp/main.bc -o tmp/main.o
	wasm-ld-8 tmp/main.o -o main.wasm --no-entry --export-dynamic -allow-undefined
	rm -rf tmp
lint:
	clang-lint -i src/main.c
