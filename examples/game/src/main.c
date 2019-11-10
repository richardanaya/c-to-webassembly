#define export __attribute__((visibility("default")))
#include "./js_ffi.h"

export int main() {
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
	int pixels_mem_start = 0;
	float *pixel = (float*)pixels_mem_start;
	int len = width*height*3.0;
	for(int i=0;i<len;i++){
		int x = i%(int)width;
		int y = i/(int)height;
		pixel[i] = y/height;
	}
	pixel[0] = 1;
	pixel[1] = 0;
	pixel[2] = 0;
	pixel[len-3] = 1;
	pixel[len-2] = 0;
	pixel[len-1] = 0;
	jsfficall3(hyperpixel,fn_render,TYPE_MEMORY,0,TYPE_NUM,pixels_mem_start,TYPE_NUM,len);
	return 0;
}