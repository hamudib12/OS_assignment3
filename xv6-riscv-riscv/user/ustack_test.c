#include "user/ustack.h"

int main()
{
    void *buffer1 = ustack_malloc(100);
    if (buffer1 == 0)
    {
        printf("Failed to allocate buffer1\n");
        return 1;
    }
    printf("Allocated buffer1\n");

    void *buffer2 = ustack_malloc(200);
    if (buffer2 == 0)
    {
        printf("Failed to allocate buffer2\n");
        return 1;
    }
    printf("Allocated buffer2\n");

    void *buffer3 = ustack_malloc(512);
    if (buffer3 == (void *)-1)
    {
        printf("Failed to allocate buffer3\n");
        return 1;
    }
    printf("Allocated buffer3\n");
    void *buffer4 = ustack_malloc(512);
    if (buffer4 == (void *)-1)
    {
        printf("Failed to allocate buffer3\n");
        return 1;
    }
    printf("Allocated buffer4\n");

    void *buffer5 = ustack_malloc(512);
    if (buffer5 == (void *)-1)
    {
        printf("Failed to allocate buffer3\n");
        return 1;
    }
    printf("Allocated buffer5\n");

    void *buffer6 = ustack_malloc(198);
    if (buffer6 == (void *)-1)
    {
        printf("Failed to allocate buffer3\n");
        return 1;
    }
    printf("Allocated buffer6\n");
    int free_len6 = ustack_free();
    if (free_len6 == -1)
    {
        printf("Failed to free buffer6\n");
        return 1;
    }
    printf("Freed buffer1 of size %d\n", free_len6);

    int free_len5 = ustack_free();
    if (free_len5 == -1)
    {
        printf("Failed to free buffer5\n");
        return 1;
    }
    printf("Freed buffer3 of size %d\n", free_len5);

    int free_len4 = ustack_free();
    if (free_len4 == -1)
    {
        printf("Failed to free buffer4\n");
        return 1;
    }
    printf("Freed buffer2 of size %d\n", free_len4);

    int free_len3 = ustack_free();
    if (free_len3 == -1)
    {
        printf("Failed to free buffer\n");
        return 1;
    }
    printf("Freed buffer1 of size %d\n", free_len3);
    int free_len2 = ustack_free();
    if (free_len2 == -1)
    {
        printf("Failed to free buffer2\n");
        return 1;
    }
    printf("Freed buffer1 of size %d\n", free_len2);
    int free_len1 = ustack_free();
    if (free_len1 == -1)
    {
        printf("Failed to free buffer1\n");
        return 1;
    }
    printf("Freed buffer1 of size %d\n", free_len1);

    int free_len = ustack_free();
    if (free_len == -1)
    {
        printf("Failed to free buffer (empty stack)\n");
    }

    return 0;
}