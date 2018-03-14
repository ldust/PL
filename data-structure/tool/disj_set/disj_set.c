//
//  disj_set.c
//  tool
//
//  Created by Plus on 2017/2/21.
//  Copyright © 2017年 Aily. All rights reserved.
//

#include "disj_set.h"

#define NumSets 7

typedef int SetType;

typedef struct {
    int depth;
    SetType index;
    char value;
} ElementType;

typedef ElementType DisjSet[NumSets + 1];

void disjSet_print(DisjSet s);

void disjSet_init(DisjSet s, char *value){
    for (int i = 0; i <= NumSets; i++) {
        s[i].depth = -1;
        s[i].index = i;
        s[i].value = value[i];
    }
}

SetType _disjSet_find(DisjSet s, SetType e){
    if (s[e].depth <= 0) {
        return e;
    } else {
        return _disjSet_find(s, s[e].depth);
    }
}

SetType disjSet_find(DisjSet s, char value) {
    for (int i = 0; i <= NumSets; i++) {
        if (s[i].value == value) {
            return _disjSet_find(s, s[i].index);
        }
    }
    return -1;
}

void _disjSet_union(DisjSet s, SetType root1, SetType root2){
    if (s[root2].depth < s[root1].depth) {
        s[root1].depth = root2;
    } else {
        if (s[root1].depth == s[root2].depth) {
            s[root1].depth--;
        }
        s[root2].depth = root1;
    }
    disjSet_print(s);
}

void disjSet_print(DisjSet s) {
    for (int i = 0; i <= NumSets; i++) {
        printf("% 2d ", s[i].depth);
    }
    printf("\n");
}

void disjSet_union(DisjSet s, char c1, char c2){
    SetType s1 = disjSet_find(s, c1);
    SetType s2 = disjSet_find(s, c2);
    if (s1 != -1 && s2 != -1) {
        _disjSet_union(s, s1, s2);
    }
}

void disj_set_test(){
    DisjSet s;
    
    char values[NumSets + 1];
    for (int i = 0; i <= NumSets; i++) {
        values[i] = 'a' + i;
    }
    
    disjSet_init(s, values);
    for (int i = 0; i <= NumSets; i++) {
        printf("% 2d ", i);
    }
    printf("\n\n");
    
    disjSet_print(s);
    
    disjSet_union(s, 'e', 'f');
    disjSet_union(s, 'g', 'h');
    disjSet_union(s, 'e', 'g');
    disjSet_union(s, 'd', 'f');
    
    printf("%d\n", disjSet_find(s, 'h'));
    printf("%d\n", disjSet_find(s, 'd'));
    
    printf("%d\n", disjSet_find(s, 'a'));
}
