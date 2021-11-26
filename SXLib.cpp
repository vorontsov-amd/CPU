#include "SXLIB.h"

//-------------------------------------------------------------------------------------------------------------------------------

char** FileToBuf(FILE* input)
{
    if (input == nullptr)
        return nullptr;

    long long SIZE = FileSize(input);

    static char* buffer = (char*)calloc(SIZE + 1, sizeof(char));
    if (buffer == nullptr)
        return nullptr;

    char* fileArr = (char*)calloc(SIZE + 1, sizeof(char));
    if (fileArr == nullptr)
        return nullptr;

    fread(fileArr, sizeof(char), SIZE, input);

    long long nLine = 1;
    for (int i = 0; fileArr[i] != '\0'; i++)
    {
        if (fileArr[i] == '\n')
        {
            nLine++;
        }
    }

    static char** buf_ptr = (char**)calloc(nLine + 1, sizeof(char*));
    if (buf_ptr == nullptr)
        return nullptr;

    buf_ptr[nLine] = nullptr;
    buf_ptr[0] = &buffer[0];
    for (int i = 0, k = 0, f = 1; fileArr[i] != '\0'; i++)
    {
        if (fileArr[i] != '\n' and fileArr[i] != '\r')
            buffer[k++] = fileArr[i];
        else if (fileArr[i] == '\n')
        {
            k++;
            buffer[k] = fileArr[++i];
            buf_ptr[f++] = &buffer[k++];
        }
    }

    free(fileArr);
    return buf_ptr;
}


//-------------------------------------------------------------------------------------------------------------------------------


unsigned long long FileSize(FILE* file)
{
    _fseeki64(file, 0, SEEK_END);
    unsigned long long SIZE = _ftelli64(file);
    rewind(file);
    return SIZE;
}


//-------------------------------------------------------------------------------------------------------------------------------


int strwicmp(const char string1[], const char string2[])
{
    int i = 0;
    while (true)
    {
        if (tolower(string1[i]) != tolower(string2[i])) break;
        if (string1[i] == ' ') break;
        if (string1[i] == '\n') break;
        i++;
    }

    return string1[i] - string2[i];
}


//-------------------------------------------------------------------------------------------------------------------------------