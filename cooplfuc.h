
// MIT License
//
// Copyright (c) 2019 Geoffrey Tang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef __COOPLFUC_H
#define __COOPLFUC_H

#define nullptr NULL

// class_begin(class_name) -- beginning of a class definition
// @param class_name: the canonical name, for example, "MyClass"
#define class_begin(__class_name)                                             \
    typedef struct __STRUCT_##__class_name {

// class_end(class_name) -- end of a class definition
// @param class_name: the canonical name that was used at the beginning
#define class_end(__class_name)                                               \
    } __class_name;

// method(return_type, method_name, arguments...) -- declare method
// @param return_type: the data type this method returns
// @param method_name: canonical name of the method
// @param arguments: a number of arguments
// @example method(void, foo, int x, int y) <--> void foo(this, int x, int y);
#define method(__return_type, __method_name, __args...)                       \
    __return_type (*__method_name)(void *self, ##__args)

// staticmethod(return_type, method_name, arguments...) -- declare static
//         method
// @param return_type: the data type this method returns
// @param method_name: canonical name of the method
// @param arguments: a number of arguments
// @example staticmethod(void, bar, int z) <--> void bar(int z);
#define staticmethod(__return_type, __method_name, __args...)                 \
    __return_type (*__method_name)(__args)

// initmethod(arguments...) -- declare constructor
// @param arguments: a number of arguments
// @example initmethod(int a) <--> MyClass(int a);
#define initmethod(__args...)                                                 \
    void (*init)(##__args)

// method_begin(return_type, class_name, method_name, arguments...) -- begin
//         definition of class method
// @param return_type: the data type this method returns
// @param class_name: canonical name of the class
// @param method_name: canonical name of the method
// @param arguments: a number of arguments
// @example method_begin(void, MyClass, foo, int x, int y) <-->
//          void MyClass::foo(this, int x, int y)
#define method_begin(__return_type, __class_name, __method_name, __args...)   \
    __return_type __METHOD_##__class_name##_SPLIT_##__method_name(            \
            void *__void_self, ##__args)                                      \
    {   __class_name *self = (__class_name*)__void_self;

// method_end() -- end definition of class method
#define method_end()  }

// staticmethod_begin(return_type, class_name, method_name, arguments...) --
//         begin definition of static method
// @param return_type: the data type this method returns
// @param class_name: canonical name of the class
// @param method_name: canonical name of the method
// @param arguments: a number of arguments
// @example staticmethod_begin(void, MyClass, bar, int z) <-->
//          void MyClass::bar(int z)
#define staticmethod_begin(__return_type, __class_name, __method_name,        \
                           __args...)                                         \
    __return_type __METHOD_##__class_name##_SPLIT_##__method_name(__args) {

// staticmethod_end() -- end definition of static method
#define staticmethod_end()  }

// initmethod_begin(class_name, arguments...) -- begin constructor definition
// @param class_name: canonical name of the class
// @param arguments: a number of arguments
// @example initmethod_begin(MyClass, int w) <-->
//          void MyClass::__init__(this, int z) <-->
//          void MyClass::MyClass(this, int z)
#define initmethod_begin(__class_name, __args...)  \
    void __METHOD_##__class_name##_SPLIT_##__init__(void *__void_self, ##__args)  \
    {   __class_name *self = (__class_name*)__void_self;

// initmethod_end() -- end constructor definition
#define initmethod_end()  }

// loadmethod(class_name, method_name) -- initialize method pointer
// @param class_name: canonical name of the class
// @param method_name: canonical name of the method
// @example: loadmethod(MyClass, foo);
// @warning: must called at constructor, elsewise the method would not work
#define loadmethod(__class_name, __method_name)  \
    self->__method_name = __METHOD_##__class_name##_SPLIT_##__method_name

// defvar(class_name, variable, arguments...) -- define variable and init
// @param class_name: canonical name of the class
// @param variable: defined variable name
// @param arguments: constructor arguments
// @example: defvar(MyClass, instance, 10) <-->
//           MyClass *instance = new MyClass(10);
#define defvar(__class_name, __variable, __args...)  \
    __class_name *__variable = (__class_name*)malloc(sizeof(__class_name));  \
    __METHOD_##__class_name##_SPLIT_##__init__((void*)__variable, ##__args)

// apply(variable, method_name, arguments...) -- call method
// @param variable: variable name
// @param method_name: canonical name of the method to call
// @param arguments: method arguments
// @example: apply(instance, foo, 5, 7); <-->
//           instance->foo(5, 7);
#define apply(__variable, __method_name, __args...)  \
    __variable->__method_name((void*)(__variable), ##__args)

#endif  // __COOPLFUC_H
