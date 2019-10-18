
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

#include "cooplfuc.h"
#include "vector.h"


method_begin(void*, vector, get, int pos)
    if (pos < 0 || pos >= self->size)
        return nullptr;
    return self->_data[pos];
method_end()

method_begin(void, vector, set, int pos, void *val)
    if (pos < 0 || pos >= self->size)
        return ;
    self->_data[pos] = val;
    return ;
method_end()

method_begin(void, vector, push_back, void *val)
    apply(self, extend, self->size + 1);
    apply(self, set, self->size - 1, val);
    return ;
method_end()

method_begin(void*, vector, back)
    if (self->size <= 0)
        return nullptr;
    return self->_data[self->size - 1];
method_end()

method_begin(void, vector, pop_back)
    if (self->size <= 0)
        return ;
    self->size -= 1;
    return ;
method_end()

method_begin(void, vector, extend, int nsize)
    if (nsize > self->capacity) {
        int n_cap = 1;
        while (n_cap * 2 < nsize)
            n_cap *= 2;
        n_cap *= 2;
        void **ndata = (void**)malloc(sizeof(void*) * n_cap);
        int i = 0;
        for (; i < self->capacity; i++)
            ndata[i] = self->_data[i];
        for (; i < n_cap; i++)
            ndata[i] = nullptr;
        if (self->_data != nullptr)
            free(self->_data);
        self->_data = ndata;
        self->capacity = n_cap;
    }
    self->size = nsize;
    return ;
method_end()

initmethod_begin(vector)
    self->size = 0;
    self->capacity = 0;
    self->_data = nullptr;
    loadmethod(vector, get);
    loadmethod(vector, set);
    loadmethod(vector, push_back);
    loadmethod(vector, back);
    loadmethod(vector, pop_back);
    loadmethod(vector, extend);
    apply(self, extend, 2);
    self->size = 0;
    return ;
initmethod_end()
