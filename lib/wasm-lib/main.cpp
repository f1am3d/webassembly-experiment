#include <stdio.h>
#include <emscripten/emscripten.h>
#include "Vector2.h"
#include "PhysObject.h"

int main() {
    Vector2 pos = { 0, 0 };
    PhysObject test = PhysObject(pos);

    printf("Hello WASM!!!\n");

    return 0;
}

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char** argv) {
    printf("MyFunction Called\n");
}