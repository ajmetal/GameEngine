#include <stdio.h>
#include <stdlib.h>

struct animation {
    const char* key;
};

int main()
{
    struct animation animationArray[10];
    for (int i = 0; i < 10; ++i) {
        char buffer[256];
        sprintf_s(buffer, 256, "frame%d", i);
        //animationArray[i] = (struct animation*)malloc(sizeof(struct animation));
        animationArray[i].key = *buffer;
    }

    return 0;
}