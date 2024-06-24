#ifndef UNTITLED19_MAIN_H
#define UNTITLED19_MAIN_H

#define max_size 20

typedef struct flowers {
    char name[max_size];
    char color[max_size];
    char country[max_size];
    unsigned count;
} flw ;

flw base[4] = { {"pion", "pink", "netherlands", 14},
                {"rose", "red", "russia", 101},
                {"tulip", "yellow", "netherlands", 41},
                {"iris", "red", "france", 83}
};

#endif //UNTITLED19_MAIN_H
