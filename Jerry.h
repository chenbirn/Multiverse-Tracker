#ifndef JERRY_H
#define JERRY_H
#include "Defs.h"

// Planet struct
typedef struct Planet {
    char *p_name;
    float coordinates[3];
} planet;

//Origin structure
typedef struct Origin {
    planet *p;
    char *d_name;
} origin;

//Physical Characteristics structure
typedef struct PhysicalCharacteristics {
    char *ph_name;
    float value;
} pc;

//Jerry structure
typedef struct Jerry {
    char *id;
    int happiness;
    origin *j_origin;
    pc **j_pc;
    int pc_num;
} jerry;

//create Jerry
jerry *create_jerry(char *id, int happiness, char *dimension, planet* pl);

// create planet
planet *create_planet(char *p_name, float x, float y, float z);

//add a physical characteristic to Jerry
status add_pc(jerry *j, char* pc_name, float pc_val);

// checks if jerry has a physical characteristic, if so- returns "true"
bool check_pc(jerry *j, char *phc);

// destroy a physical character
void destroy_pc(jerry *j, pc *phc);

// delete a physical character from Jerry, returns success if deleted, failure if not
status delete_pc(jerry *j, char *phc);

// print Jerry's info, returns success if printed, failure if not
status print_jerry(jerry *j);

// print planet info, returns success if printed, failure if not
status print_planet(planet *pl);

// destroy Jerry
void destroy_Jerry(jerry *j);

// destroy a planet
void destroy_planet(planet *pl);

// destroys an Origin
void destroy_Origin(origin *o);

#endif //JERRY_H
