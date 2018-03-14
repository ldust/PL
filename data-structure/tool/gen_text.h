//
//  gen_text.h
//  tool
//
//  Created by Plus on 2017/3/3.
//  Copyright © 2017年 Aily. All rights reserved.
//

#ifndef gen_text_h
#define gen_text_h

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

enum {
    NPREF = 3,
    NHASH = 4093,
    MAXGEN = 10000,
};

typedef struct State State;
typedef struct Suffix Suffix;

#define EMPTY "?"

struct State {
    char* pref[NPREF];
    Suffix* suf;
    State* next;
};

struct Suffix {
    char* word;
    Suffix* next;
};

State *statetab[NHASH];

unsigned int hash(char* s[NPREF]){
    unsigned int h = 0;
    for (int i = 0; i < NPREF; i++) {
        for (unsigned char *p = (unsigned char*)s[i]; *p != '\0'; p++) {
            h = 31 * h + *p;
        }
    }
    return h % NHASH;
}
State* lookup(char* prefix[NPREF], int create) {
    int h = hash(prefix);
    State* sp;
    for (sp = statetab[h]; sp != NULL; sp = sp->next) {
        for (int i = 0; i < NPREF; i++) {
            if (strcmp(prefix[i], sp->pref[i]) != 0) {
                break;
            }
            if (i == NPREF) {
                return sp;
            }
        }
    }
    if (create) {
        sp = (State*)malloc(sizeof(State));
        for (int i = 0; i < NPREF; i++) {
            sp->pref[i] = prefix[i];
            sp->suf = NULL;
            sp->next = statetab[h];
            statetab[h] = sp;
        }
    }
    return sp;
}

void addSuffix(State* sp, char* suffix){
    Suffix *suf = (Suffix*)malloc(sizeof(Suffix));
    suf->word =  suffix;
    suf->next = sp->suf;
    sp->suf = suf;
}

void add(char* prefix[NPREF], char *suffix) {
    State* sp = lookup(prefix, true);
    addSuffix(sp, suffix);
    memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
    prefix[NPREF-1] = suffix;
}

void build(char* prefix[NPREF], FILE *f){
    char buf[100];
    char fmt[10];
    sprintf(fmt, "%%%lus", sizeof(buf) - 1);
    while (fscanf(f, fmt, buf) != EOF) {
        add(prefix, strdup(buf));
    }
}

void gen(int nwords){
    char *prefix[NPREF];
    for (int i = 0; i < NPREF; i++) {
        prefix[i] = EMPTY;
    }
    
    for (int i = 0; i < nwords; i++) {
        State *sp = lookup(prefix, false);
        int nmatch = 0;
        char *w = NULL;
        for (Suffix *suf = sp->suf; suf != NULL; suf = suf->next) {
            if (rand() % ++nmatch == 0) {
                w = suf->word;
            }
        }
        if (strcmp(w, "\n") == 0) {
            break;
        }
        printf("%s\n", w);
        memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
        prefix[NPREF-1] = w;
    }
}

void run(){
    char *prefix[NPREF];
    for (int i = 0; i < NPREF; i++) {
        prefix[i] = EMPTY;
    }
    build(prefix, stdin);
    add(prefix, EMPTY);
    gen(100);
}

#endif /* gen_text_h */
