build:
	mkdir -p tmp/src
	clang-9 src/main.c -I./ -S -emit-llvm --target=wasm32 -o tmp/src/main.ll
	llvm-link-9 -o tmp/main.bc tmp/src/*\.ll
	opt-9 -O3 tmp/main.bc -o tmp/main.bc
	llc-9 -mtriple=wasm32-unknown-unknown -O3 -filetype=obj tmp/main.bc -o tmp/main.o
	wasm-ld-9 tmp/main.o -o main.wasm --no-entry --export-dynamic -allow-undefined
	rm -rf tmp
serve:
	python3 -m http.server 8080
lint:
	clang-lint -i src/main.c
