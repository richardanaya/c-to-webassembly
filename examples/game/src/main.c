#define export __attribute__((visibility("default")))
#include "./js_ffi.h"

extern unsigned char __heap_base;

JSValue fn_init;
JSValue fn_render;
JSValue fn_width;
JSValue fn_height;
JSValue fn_loop;
JSValue hyperpixel;
double width;
double height;
float time = 0; 

int RENDER = 0;
int KEYBOARD = 1;

int show_trash = 0;

void render() {
	float *pixel = (float*)&__heap_base;
	int len = width*height*3.0;
	if(show_trash){
		float *pixel = (float*)&__heap_base;
		int len = width*height*3.0;
		for(int x=0;x<width;x++){
			for(int y=0;y<height;y++){
				float *pixel = (float*)&__heap_base;
				int len = width*height*3.0;
				int p = (((y*width)+x)*3);
				pixel[p] = ((int)x%100)/100.0;
				pixel[p+1] = ((int)x%20)/20.0;
				pixel[p+2] = 0;
			}
			
		}
		jsfficall3(hyperpixel,fn_render,TYPE_MEMORY,0,TYPE_NUM,(int)pixel,TYPE_NUM,len);
		return;
	}
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			int p = (((y*width)+x)*3);
			pixel[p] = x/width+(((int)time%1000)/1000.0);
			pixel[p+1] = y/height;
			pixel[p+2] = 0;
		}
	}
	jsfficall3(hyperpixel,fn_render,TYPE_MEMORY,0,TYPE_NUM,(int)pixel,TYPE_NUM,len);
}

export int main() {
	// get enough memory for pixels
	__builtin_wasm_memory_grow(0,64);
	fn_init = jsffiregister("\
		(selector,cb)=>{\
			let canvas = document.querySelector(selector);\
			document.addEventListener('keydown',function(e){cb(e.keyCode);});\
			return new HyperPixel(canvas);\
		}\
	");
	fn_render = jsffiregister("\
		(function(mem,ptr,length){\
			let p = ptr/4;\
			let pixelView = (new Float32Array(mem)).subarray(p,p+length);\
			this.render(pixelView);\
		})\
	");
	fn_width = jsffiregister("\
		(function(){\
			return this.width;\
        })\
	");
	fn_height = jsffiregister("\
		(function(){\
			return this.height;\
		})\
	");
	fn_loop = jsffiregister("(cb)=>{\
                    let time = Date.now();\
                    function run(){\
                        let new_time = Date.now();\
                        let delta = new_time-time;\
                        time = new_time;\
                        window.requestAnimationFrame(run);\
                        cb(delta);\
                    }\
                    window.requestAnimationFrame(run);\
                }");
	hyperpixel = jsfficall2(JS_UNDEFINED,fn_init,TYPE_STRING,(JSValue)(int)&"#screen",TYPE_FUNCTION,KEYBOARD);
	width = (int)jsfficall0(hyperpixel,fn_width);
	height = (int)jsfficall0(hyperpixel,fn_height);
	jsfficall1(JS_UNDEFINED,fn_loop,TYPE_FUNCTION,RENDER);
	return 0;
}

export void jsfficallback(int fn, JSValue v1, JSValue v2, JSValue v3, JSValue v4, JSValue v5, JSValue v6, JSValue v7, JSValue v8, JSValue v9, JSValue v10) {
	if(fn == RENDER){
		time += v1;
		render();
	} else if (fn == KEYBOARD){
		int keyCode = v1;
		
		// do something with key pressed?
		show_trash = !show_trash;
	}
}
