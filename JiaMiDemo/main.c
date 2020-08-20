//
//  main.c
//  JiaMiDemo
//
//  Created by Master on 2020/8/20.
//  Copyright © 2020 Master. All rights reserved.
//

#include <stdio.h>
#include <zconf.h>
#include <memory.h>
#include <malloc/_malloc.h>

char *confusion(const char *str);
char *disConfusion(const char *str);


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    const char *source = "刘港欢";
    printf("原始字符串：%s\n",source);
    
    const char *afterConfusion = confusion(source);
    printf("混淆后：%s\n",afterConfusion);
    
    char *result = disConfusion(afterConfusion);
    printf("解混淆后：%s\n",result);
    
    
    return 0;
}


char *confusion(const char *str) {
    int v13 = strlen(str);
    const void *ebbytes = str;
    char *v11;
    v11 = (char *)malloc(4*((v13+2)/3));
    for (int i = 0; i < v13; i+=3) {
        int v9 = 0;
        for (int j =i; j<i+3; ++j) {
            v9 <<= 8;
            if (j<v13) {
                v9|= *(Byte *)(ebbytes+j);
            }
        }
        char *v12 = "Pz#`(:7F-a%diHm<kQDTVEKXI68loAqwsGgC42!R^ju0h@xYc][}S9B{M~+t$.>,J";
            char *v3;
            v3 = &v11[4*(i/3)];
            *v3 = *(Byte *)(v12+((v9>>18)&0x3F));
            Byte *v4;
            v4 = v3 + 1;
            *v4 = *(Byte *) (v12 + ((v9 >> 12) & 0x3F));
            char v7;
            if (i + 1 >= v13) {
                v7 = *(Byte *)(v12 + 64);
            } else {
                v7 = *(Byte *)(v12 + ((v9 >> 6)&0x3F));
            }
            v4[1] = v7;
            char v6;
            if (i+2 >= v13) {
                v6 = *(Byte *)(v12+64);
            } else {
                v6 = *(Byte *)(v12 + (v9 &0x3F));
            }
            v4[2] = v6;
    }
    return v11;
}

char *disConfusion(const char *str) {
    size_t *a1 = (size_t *) malloc(sizeof(size_t));
    int i;
    char *v6;
    char *v7;
    char *v8;
    char *v9;
    char v10;
    char v11;
    char v12;
    char *v13;
    int v14;
    char *v15 = "Pz#`(:7F-a%diHm<kQDTVEKXI68loAqwsGgC42!R^ju0h@xYc][}S9B{M~+t$.>,J";
    const char *v16 = str;
    size_t *v17 = a1;
    int a3 = strlen(str);
    v14 = (signed int) a3 / 4;
    *a1 = 3 * ((signed int) a3 / 4);
    v13 = malloc(*a1);
    for (i = 0; i < v14; ++i) {
        v6 = strchr(v15, *(char *)(v16+4*i));
        if (!v6) {
            free(v13);
            *v17 = 0;
            return 0;
        }
        v12 = 4 * ((Byte)v6 - (Byte)v15);
        v7 = strchr(v15, *(char *)(v16+4*i+1));
        if (!v7) {
            free(v13);
            *v17 = 0LL;
            return 0LL;
        }
        v11 = (Byte)v7-(Byte)v15;
        *((Byte*)v13+3*i) = v12+(((v7-v15)&0x30)>>4);
        v8 = strchr(v15, *(char *)(v16+4*i+2));
        if (!v8) {
            free(v13);
            *v17 = 0LL;
            return 0LL;
        }
        if (((Byte)v8 - (Byte)v15) == 64) {
            *v17 = 3*i+1;
            return realloc(v13, *v17);
        }
        v10 = (Byte) v8 - (Byte)v15;
        *((Byte *) v13 + 3*i+1) = 16*v11+(((v8-v15)&0x3C)>>2);
        v9 = strchr(v15, *(char *)(v16+4*i+3));
        if (!v9) {
            free(v13);
            *v17 = 0LL;
            return 0LL;
        }
        if (((Byte)v9 - (Byte)v15)==64) {
            *v17 = 3*i+2;
            return realloc(v13, *v17);
        }
        *((Byte *)v13+3*i+2) = (v10 <<6)+(Byte)v9-(Byte)v15;
    }
    return v13;
}
