//
//  main.cpp
//  cpp
//
//  Created by Plus on 2017/3/3.
//  Copyright © 2017年 Aily. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    FILE *file = fopen("/Users/Plus/Desktop/0.txt", "r");
    
    int buf;
    int counter = 'a';
    while (fscanf(file, "%d", &buf) != EOF) {
        for (int i = 0; i < buf; i++) printf("%c", counter);
        counter++;
        if (counter > 'z') {
            counter = 'a';
            printf("\n");
        }
    }
    return 0;
}
