
# COOPLFUC

Concise Object-Oriented Programming Library For Users in C.

## Example

```c++
#include <stdio.h>
#include "cooplfuc.h"
#include "vector.h"

class_begin(MyClass)
    int a;
    method(int, foo1, int x);
    method(int, foo2);
    method(int, foo3, int a, int b);
    staticmethod(int, bar, int x, int y);
class_end(MyClass)

method_begin(int, MyClass, foo1, int x)
    return self->a + x;
method_end()

method_begin(int, MyClass, foo2)
    return self->a * 2;
method_end()

method_begin(int, MyClass, foo3, int a, int b)
    return self->a * a * b;
method_end()

staticmethod_begin(int, MyClass, bar, int x, int y)
    return x * y;
staticmethod_end()

initmethod_begin(MyClass, int a)
    self->a = a;
    loadmethod(MyClass, foo1);
    loadmethod(MyClass, foo2);
    loadmethod(MyClass, foo3);
    loadmethod(MyClass, bar);
initmethod_end()

int main(int argc, char** argv)
{
    defvar(MyClass, mc, 5);
    printf("%d\n", apply(mc, foo1, 10));
    printf("%d\n", apply(mc, foo2));
    printf("%d\n", apply(mc, foo3, 15, 20));
    printf("%d\n", mc->bar(7, 17));
    return 0;
}
```
