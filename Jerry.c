#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

// create origin structure
origin *create_origin(char *d_name, planet *p) {
    origin *og = (origin *) malloc(sizeof(origin));
    // check if memory allocate was successful
    if (og != NULL) {
        og->d_name = (char *) malloc(strlen(d_name) + 1);
        // if memory allocate failed, return null
        if (og->d_name == NULL) {
            return NULL;
        } else {
            strcpy(og->d_name, d_name);
        }
        og->p = p;
    } else {
        return NULL;
    }
    return og;
}

// create a jerry structure
jerry *create_jerry(char *id, int happiness, char *dimension, planet *pl) {
    jerry *j = (jerry *) malloc(sizeof(jerry));
    // check if memory allocate was successful
    if (j != NULL) {
        j->id = (char *) malloc(strlen(id) + 1);
        // if memory allocate failed, return null
        if (j->id == NULL) {
            return NULL;
        } else {
            strcpy(j->id, id);
        }
        j->j_origin = create_origin(dimension, pl);
        j->happiness = happiness;
        j->j_pc = NULL;
        j->pc_num = 0;
    } else {
        return NULL;
    }
    return j;
}

// create a planet structure
planet *create_planet(char *p_name, float x, float y, float z) {
    planet *p = (planet *) malloc(sizeof(planet));
    // check if memory allocate was successful
    if (p != NULL) {
        p->p_name = malloc(strlen(p_name) + 1);
        // if memory allocate failed, return null
        if (p->p_name == NULL) {
            return NULL;
        } else {
            strcpy(p->p_name, p_name);
        }
        p->coordinates[0] = x;
        p->coordinates[1] = y;
        p->coordinates[2] = z;
    } else {
        return NULL;
    }
    return p;
}

// create physical characteristics structure
pc *create_pc(char *ph_name, float value) {
    pc *phc = (pc *) malloc(sizeof(pc));
    // check if memory allocate was successful
    if (phc != NULL) {
        phc->ph_name = malloc(strlen(ph_name) + 1);
        // if memory allocate failed, return null
        if (phc->ph_name == NULL) {
            return NULL;
        } else {
            strcpy(phc->ph_name, ph_name);
            phc->value = value;
        }
    } else {
        return NULL;
    }
    return phc;
}

//help variable for storing index of the checked physical character
static int checked_idx = -1;

// checks if jerry has a physical characteristic
bool check_pc(jerry *j, char *phc) {
    if (j->pc_num != 0) {
        for (int i = 0; i < j->pc_num; i++) {
            if (strcmp(j->j_pc[i]->ph_name, phc) == 0) {
                checked_idx = i;
                return true;
            }
        }
    }
    return false;
}

// add a physical character to Jerry
status add_pc(jerry *j, char *pc_name, float pc_val) {
    if (j->pc_num == 0) {
        j->j_pc = (pc **) malloc(sizeof(pc *));
        if (j->j_pc == NULL) {
            return failure;
        }
    }
    else {
        pc** temp = (pc **) realloc(j->j_pc, (1 + j->pc_num) * sizeof(pc *));
        // if memory allocate failed, return null
        if (temp == NULL) {
            return failure;
        }
        j->j_pc = temp;
    }
    pc *new_pc = create_pc(pc_name, pc_val);
    if (new_pc == NULL) {
        return failure;
    }
    j->j_pc[j->pc_num] = new_pc;
    j->pc_num++;
    return success;
}

// destroys a physical character
void destroy_pc(jerry *j, pc *phc) {
    if (phc != NULL && j!=NULL) {
        free(phc->ph_name);
        free(phc);
        if (j->pc_num == 1) {
            free(j->j_pc);
        }
    }
}

// Delete a physical character from Jerry
status delete_pc(jerry *j, char *phc) {
    // check if the physical character exist. if so, deletes it.
    if (check_pc(j, phc) == true) {
        // if Jerry has more than 1 physical character, make the array smaller
        if (j->pc_num > 1) {
            destroy_pc(j,j->j_pc[checked_idx]);
            for (int i = checked_idx; i < j->pc_num - 1; i++) {
                j->j_pc[i] = j->j_pc[i + 1];
            }
            j->pc_num--;
            pc** temp = (pc **) realloc(j->j_pc, (j->pc_num) * sizeof(pc *));
            // if memory allocate failed, return null
            if (temp == NULL) {
                return failure;
            }
            j->j_pc = temp;
            return success;
        }
        destroy_pc(j,j->j_pc[0]);
        j->j_pc = NULL;
        j->pc_num--;
        return success;
    }
    return failure;
}


// print Jerry's details
status print_jerry(jerry *j) {
    if (j != NULL) {
        printf("Jerry , ID - %s :  \n", j->id);
        printf("Happiness level : %d \n", j->happiness);
        printf("Origin : %s \n", j->j_origin->d_name);
        printf("Planet : %s (%.2f,%.2f,%.2f) \n", j->j_origin->p->p_name, j->j_origin->p->coordinates[0],
               j->j_origin->p->coordinates[1], j->j_origin->p->coordinates[2]);
        // if Jerry has physical characters - print it
        if (j->pc_num != 0) {
            printf("Jerry's physical Characteristics available : \n");
            printf("\t");
            for (int i = 0; i < j->pc_num; i++) {
                if (i == j->pc_num - 1) {
                    printf("%s : %.2f ", j->j_pc[i]->ph_name, j->j_pc[i]->value);
                } else {
                    printf("%s : %.2f , ", j->j_pc[i]->ph_name, j->j_pc[i]->value);
                }
            }
            printf("\n");
        }
        return success;
    } else {
        return failure;
    }
}

// print Planet details
status print_planet(planet *pl) {
    // check if the pointer is not NULL
    if (pl != NULL) {
        printf("Planet : %s (%.2f,%.2f,%.2f) \n", pl->p_name, pl->coordinates[0], pl->coordinates[1],
               pl->coordinates[2]);
        return success;
    } else {
        return failure;
    }
}

// destroy Jerry
void destroy_Jerry(jerry *j) {
    // check if the pointer is not NULL
    if (j != NULL) {
        if (j->pc_num > 0) {
            for (int i = 0; i < j->pc_num; i++) {
                destroy_pc(j,j->j_pc[i]);
            }
        }
        if (j->pc_num>1) {
            free(j->j_pc);
        }
        free(j->id);
        destroy_Origin(j->j_origin);
        free(j);
    }
}

// destroy a planet
void destroy_planet(planet *pl) {
    if (pl != NULL) {
        free(pl->p_name);
        free(pl);
    }
}

// destroys an Origin
void destroy_Origin(origin *o) {
    if (o != NULL) {
        free(o->d_name);
        free(o);
    }
}
