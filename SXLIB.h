#pragma once

#include <iostream>
#include <cstdio>
#include <climits>
#include <fstream>
#include <cassert>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>

unsigned long long FileSize(FILE* file);
char** FileToBuf(FILE* input);
int strwicmp(const char string1[], const char string2[]);


template <typename Type>
bool ArrayResize(Type*& data, size_t& old_capacity, size_t new_capacity);

template <typename Type>
bool ArrayResize(Type*& data, size_t& old_capacity, size_t new_capacity)
{
    if (new_capacity <= old_capacity)
        return false;

    else
    {
        Type* dataResize = (Type*)calloc(new_capacity, sizeof(Type));
        if (dataResize == nullptr)
            ArrayResize(data, old_capacity, new_capacity * 8 / 10);
        else
        {
            for (int i = 0; i < old_capacity; i++)
            {
                dataResize[i] = data[i];
            }

            free(data);
            data = dataResize;
            old_capacity = new_capacity;
        }

        return true;
    }
}