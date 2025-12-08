#include "src.h"

namespace example {

int foo(int i) {
    return i * i + i;
}

float bar(float f) {
    return static_cast<float>(foo(static_cast<int>(f))) + f * f + f;
}
  
}
