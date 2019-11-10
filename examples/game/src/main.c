#define export __attribute__((visibility("default")))
#include "./js_ffi.h"

extern unsigned char __heap_base;

export int main() {
	__builtin_wasm_memory_grow(0,64);
	int fn_init = jsffiregister("\
		(selector)=>{\
			return new HyperPixel(document.querySelector(selector));\
		}\
	");
	int fn_render = jsffiregister("\
		(function(mem,ptr,length){\
			let p = ptr/4;\
			let pixelView = (new Float32Array(mem)).subarray(p,p+length);\
			this.render(pixelView);\
		})\
	");
	int fn_width = jsffiregister("\
		(function(){\
			return this.width;\
        })\
	");
	int fn_height = jsffiregister("\
		(function(){\
			return this.height;\
		})\
	");
	JSValue hyperpixel = jsfficall1(JS_UNDEFINED,fn_init,TYPE_STRING,(JSValue)(int)&"#screen");
	double width = (int)jsfficall0(hyperpixel,fn_width);
	double height = (int)jsfficall0(hyperpixel,fn_height);
	float *pixel = (float*)&__heap_base;
	int len = width*height*3.0;
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			//int p = (y*600+x);
			int p = (((y*width)+x)*3);
			pixel[p] = x/width;
			pixel[p+1] = y/height;
			pixel[p+2] = 0;
		}
	}
	jsfficall3(hyperpixel,fn_render,TYPE_MEMORY,0,TYPE_NUM,(int)pixel,TYPE_NUM,len);
	return 0;
}