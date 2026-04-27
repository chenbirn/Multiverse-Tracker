#include "Defs.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "Jerry.h"
#include <math.h>

// free planets
void destroy_PlanetsArr(planet **p, int size_p) {
    if (p != NULL) {
        for (int i = 0; i < size_p; i++) {
            destroy_planet(p[i]);
        }
    }
}

//Shallow copy Jerry function
Element CopyJerry(Element j) {
    if (j == NULL) {
        return NULL;
    }
    jerry *copy_jerry = j;
    return copy_jerry;
}

//free Jerry function
status FreeJerry(Element j) {
    if (j == NULL) {
        return failure;
    }
    destroy_Jerry(j);
    return success;
}

//free shallow Jerry function
status FreeShallowJerry(Element j) {
    if (j == NULL) {
        return failure;
    }
    return success;
}

//print Jerry function
status PrintJerry(Element j) {
    if (j == NULL) {
        return failure;
    }
    return print_jerry(j);
}

//check if an element is a part of Jerry
bool PartJerry(Element j, Element elem) {
    if (j == NULL || elem == NULL) {
        return false;
    }
    jerry *j_elem = (jerry *) j;
    //equal Jerries
    if (j_elem == elem) {
        return true;
    }
    // equal ID
    if (strcmp(j_elem->id, elem) == 0) {
        return true;
    }
    // equal dimension
    if (strcmp(j_elem->j_origin->d_name, elem) == 0) {
        return true;
    }
    //equal physical characteristic
    for (int i = 0; i < j_elem->pc_num; i++) {
        if (strcmp(j_elem->j_pc[i]->ph_name, elem) == 0) {
            return true;
        }
    }
    if (j_elem->j_origin->p == elem) {
        return true;
    }
    return false;
}

//transform physical character's name to number
int TransformPCNameToNumber(Element pc_name) {
    if (pc_name == NULL) {
        return 0;
    }
    char *t_pc_name = (char *) pc_name;
    //HashNum = first char in ascii
    int HashNum = (int) t_pc_name[0];
    return HashNum;
}

// copy physical character's name function
Element CopyPCName(Element pc_name) {
    if (pc_name == NULL) {
        return NULL;
    }
    char *new_pc_name = (char *) malloc(strlen(pc_name) + 1);
    if (new_pc_name == NULL) {
        return NULL;
    }
    strcpy(new_pc_name, pc_name);
    return (Element) new_pc_name;
}

// free physical character's name function
status FreePCName(Element pc_name) {
    if (pc_name == NULL) {
        return failure;
    }
    free(pc_name);
    return success;
}

// print physical character's name function
status PrintPCName(Element pc_name) {
    if (pc_name == NULL) {
        return failure;
    }
    printf("%s : \n", (char *) pc_name);
    return success;
}

//Equal name function
bool EqualPCName(Element pc1, Element pc2) {
    if (pc1 == NULL || pc2 == NULL) {
        return false;
    }
    if (strcmp(pc1, pc2) == 0) {
        return true;
    }
    return false;
}

// help function to check if input is between 1 and 9
bool checkInput(const char *str) {
    if (strlen(str) == 1) {
        if (str[0] >= '1' && str[0] <= '9') {
            return true;
        }
    }
    return false;
}

//help function to destroy everything and exit the program
void MemoryProblem(MVhash PCMulti, linked_list JerrysList, int p_counter, planet *Planets_arr[]) {
    printf("A memory problem has been detected in the program \n");
    destroyMultiValueHashTable(PCMulti);
    destroyList(JerrysList);
    destroy_PlanetsArr(Planets_arr, p_counter);
    exit(1);
}

// read configuration file
void read_configuration(char *config_file, planet *Planets_arr[], int planetNum, linked_list JerrysList,
                        MVhash PCMulti) {
    // read line in file into array "line"
    if (config_file == NULL) {
        printf("File Not Found\n");
        return;
    }
    //count planets in array
    int p_counter = 0;
    // count Jerries in array
    int j_counter = 0;
    char line[256];
    // read file
    FILE *c_file = fopen(config_file, "r");
    while (fgets(line, sizeof(line), c_file)) {
        if (strcmp(line, "Planets\n") == 0) {
            continue;
        }
        // if not all planets were read from file
        if (p_counter < planetNum) {
            char temp_p_name[100];
            float x1, y1, z1;
            if (sscanf(line, "%[^,],%f,%f,%f", temp_p_name, &x1, &y1, &z1) == 4) {
                // create planet
                Planets_arr[p_counter] = create_planet(temp_p_name, x1, y1, z1);
                // if memory allocate failed, free all memory and exit
                if (Planets_arr[p_counter] == NULL) {
                    MemoryProblem(PCMulti, JerrysList, p_counter, Planets_arr);
                }
                p_counter++;
                continue;
            }
        }
        if (strcmp(line, "Jerries\n") == 0) {
            continue;
        }
        char id[100];
        char dimension[100];
        char pl_name[100];
        int happiness;
        char pc_name[100];
        float pc_val;
        if (line[0] == '\t') {
            jerry *temp = getDataByIndex(JerrysList, j_counter);
            // start line from the first word in it (and not from tab)
            memmove(line, line + 1, strlen(line));
            if (sscanf(line, "%[^:]:%f", pc_name, &pc_val) == 2) {
                if (add_pc(temp, pc_name, pc_val) == success) {
                    addToMultiValueHashTable(PCMulti, pc_name, temp);
                } else {
                    // if memory allocate failed, free all memory and exit
                    MemoryProblem(PCMulti, JerrysList, p_counter, Planets_arr);
                }
            }
        } else {
            // create Jerry
            if (sscanf(line, "%[^,],%[^,],%[^,],%d", id, dimension, pl_name, &happiness) == 4) {
                for (int i = 0; i < p_counter; i++) {
                    if (strcmp(Planets_arr[i]->p_name, pl_name) == 0) {
                        jerry *temp = create_jerry(id, happiness, dimension, Planets_arr[i]);
                        // if memory allocate failed, free all memory and exit
                        if (temp == NULL) {
                            MemoryProblem(PCMulti, JerrysList, p_counter, Planets_arr);
                        }
                        if (appendNode(JerrysList, temp) == failure) {
                            MemoryProblem(PCMulti, JerrysList, p_counter, Planets_arr);
                        }
                        j_counter++;
                        break;
                    }
                }
            }
        }
    }
    // close file
    fclose(c_file);
}

// user's input in menu is 1
void userChoice1(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    planet *new_JerryP = NULL;
    char dim[300];
    char ID[300];
    int happiness = 0;
    printf("What is your Jerry's ID ? \n");
    scanf("%s", ID);
    // check if Jerry exist already
    if (searchByKeyInList(JerrysList, ID) == NULL) {
        printf("What planet is your Jerry from ? \n");
        char plant_name[300];
        scanf("%s", plant_name);
        // check if it's a known planet
        for (int i = 0; i < planetNum; i++) {
            if (strcmp(Planets_arr[i]->p_name, plant_name) == 0) {
                new_JerryP = Planets_arr[i];
                break;
            }
        }
        if (new_JerryP == NULL) {
            printf("%s is not a known planet ! \n", plant_name);
            return;
        }
        printf("What is your Jerry's dimension ? \n");
        scanf("%s", dim);
        printf("How happy is your Jerry now ? \n");
        scanf("%d", &happiness);
        //create Jerry and add to ADTs
        jerry *temp_Jerry = create_jerry(ID, happiness, dim, new_JerryP);
        if (appendNode(JerrysList, temp_Jerry) == success) {
            print_jerry(temp_Jerry);
        } else {
            MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
        }
    } else {
        printf("Rick did you forgot ? you already left him here ! \n");
    }
}

// user's input in menu is 2
void userChoice2(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    char ID[300];
    char pc_name[300];
    float pc_value;
    printf("What is your Jerry's ID ? \n");
    scanf("%s", ID);
    // search for Jerry
    jerry *temp_Jerry = searchByKeyInList(JerrysList, ID);
    if (temp_Jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
    } else {
        printf("What physical characteristic can you add to Jerry - %s ? \n", ID);
        scanf("%s", pc_name);
        // if Jerry has no physical characteristics
        if (temp_Jerry->pc_num == 0) {
            printf("What is the value of his %s ? \n", pc_name);
            scanf("%f", &pc_value);
            add_pc(temp_Jerry, pc_name, pc_value);
            if (addToMultiValueHashTable(PCMulti, pc_name, temp_Jerry) == failure) {
                MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
            }
            displayMultiValueHashTable(PCMulti, pc_name);
        } else {
            // check if the physical characteristic exist already
            for (int i = 0; i < temp_Jerry->pc_num; i++) {
                if (strcmp(temp_Jerry->j_pc[i]->ph_name, pc_name) == 0) {
                    printf("The information about his %s already available to the daycare ! \n", pc_name);
                    break;
                }
                if (i == temp_Jerry->pc_num - 1) {
                    printf("What is the value of his %s ? \n", pc_name);
                    scanf("%f", &pc_value);
                    add_pc(temp_Jerry, pc_name, pc_value);
                    if (addToMultiValueHashTable(PCMulti, pc_name, temp_Jerry) == failure) {
                        MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
                    }
                    displayMultiValueHashTable(PCMulti, pc_name);
                }
            }
        }
    }
}

// user's input in menu is 3
void userChoice3(MVhash PCMulti, linked_list JerrysList) {
    char ID[300];
    char pc_name[300];
    printf("What is your Jerry's ID ? \n");
    scanf("%s", ID);
    // search for Jerry
    jerry *temp_Jerry = searchByKeyInList(JerrysList, ID);
    if (temp_Jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        return;
    }
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", ID);
    scanf("%s", pc_name);
    // check if physical characteristic exists
    for (int i = 0; i < temp_Jerry->pc_num; i++) {
        if (strcmp(temp_Jerry->j_pc[i]->ph_name, pc_name) == 0) {
            delete_pc(temp_Jerry, pc_name);
            removeFromMultiValueHashTable(PCMulti, pc_name, temp_Jerry);
            print_jerry(temp_Jerry);
            break;
        }
        if (i == temp_Jerry->pc_num - 1) {
            printf("The information about his %s not available to the daycare ! \n", pc_name);
        }
    }
}

// user's input in menu is 4
void userChoice4(MVhash PCMulti, linked_list JerrysList) {
    char ID[300];
    printf("What is your Jerry's ID ? \n");
    scanf("%s", ID);
    //search for Jerry
    jerry *temp_Jerry = searchByKeyInList(JerrysList, ID);
    if (temp_Jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        return;
    }
    //removes Jerry from ADTs
    for (int i = 0; i < temp_Jerry->pc_num; i++) {
        removeFromMultiValueHashTable(PCMulti, temp_Jerry->j_pc[i]->ph_name, temp_Jerry);
    }
    deleteNode(JerrysList, temp_Jerry);
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
}

// user's input in menu is 5
void userChoice5(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    char pc_name[300];
    float val = 0;
    float difference = 100;
    jerry *similar_jerry = NULL;
    printf("What do you remember about your Jerry ? \n");
    scanf("%s", pc_name);
    //search for Jerries with this physical characteristic
    linked_list temp_list = lookupInMultiValueHashTable(PCMulti, pc_name);
    if (temp_list == NULL) {
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pc_name);
        return;
    }
    printf("What do you remember about the value of his %s ? \n", pc_name);
    scanf("%f", &val);
    //search Jerry with the closest value  as input
    for (int i = 1; i <= getLengthList(temp_list); i++) {
        jerry *check_jerry = getDataByIndex(temp_list, i);
        for (int j = 0; j < check_jerry->pc_num; j++) {
            if (strcmp(check_jerry->j_pc[j]->ph_name, pc_name) == 0) {
                float sub = fabsf(val - check_jerry->j_pc[j]->value);
                if (sub < difference) {
                    difference = sub;
                    similar_jerry = check_jerry;
                }
            }
        }
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    print_jerry(similar_jerry);
    // removes Jerry from ADTs
    if (removeFromMultiValueHashTable(PCMulti, pc_name, similar_jerry) == failure) {
        MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
    }
    if (deleteNode(JerrysList, similar_jerry) == failure) {
        MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
    }
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
}

// user's input in menu is 6
void userChoice6(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    // if there are no Jerries in the daycare
    if (getLengthList(JerrysList) == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return;
    }
    // search for the saddest Jerry
    int happiness_level = 101;
    jerry *sad_jerry = NULL;
    for (int i = 1; i <= getLengthList(JerrysList); i++) {
        jerry *sad_temp = getDataByIndex(JerrysList, i);
        if (sad_temp->happiness < happiness_level) {
            happiness_level = sad_temp->happiness;
            sad_jerry = sad_temp;
        }
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    print_jerry(sad_jerry);
    //remove Jerry from ADTs
    for (int i = 0; i < sad_jerry->pc_num; i++) {
        if (removeFromMultiValueHashTable(PCMulti, sad_jerry->j_pc[i]->ph_name, sad_jerry) == failure) {
            MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
        }
    }
    if (deleteNode(JerrysList, sad_jerry) == failure) {
        MemoryProblem(PCMulti, JerrysList, planetNum, Planets_arr);
    }
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
}

// user's input in menu is 7
void userChoice7(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    char pc_name[300];
    char info_choice[300] = "0";
    printf("What information do you want to know ? \n");
    printf("1 : All Jerries \n");
    printf("2 : All Jerries by physical characteristics \n");
    printf("3 : All known planets \n");
    scanf("%s", info_choice);
    // if there are no Jerries
    if (getLengthList(JerrysList) == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return;
    }
    // print all Jerries
    if (strcmp(info_choice, "1") == 0) {
        displayList(JerrysList);
        return;
    }
    //print all Jerries with the same physical characteristic as input
    if (strcmp(info_choice, "2") == 0) {
        printf("What physical characteristics ? \n");
        scanf("%s", pc_name);
        linked_list pc_list = lookupInMultiValueHashTable(PCMulti, pc_name);
        if (pc_list == NULL) {
            printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pc_name);
            return;
        }
        printf("%s : \n", pc_name);
        displayList(pc_list);
        return;
    }
    //print all planets
    if (strcmp(info_choice, "3") == 0) {
        for (int i = 0; i < planetNum; i++) {
            print_planet(Planets_arr[i]);
        }
        return;
    }
    printf("Rick this option is not known to the daycare ! \n");
}

// user's input in menu is 8
void userChoice8(MVhash PCMulti, linked_list JerrysList) {
    // if there are no Jerries
    if (getLengthList(JerrysList) == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return;
    }
    printf("What activity do you want the Jerries to partake in ? \n");
    printf("1 : Interact with fake Beth \n");
    printf("2 : Play golf \n");
    printf("3 : Adjust the picture settings on the TV \n");
    char activity_choice[300] = "0";
    scanf("%s", activity_choice);
    //Interact with fake Beth
    if (strcmp(activity_choice, "1") == 0) {
        for (int i = 1; i <= getLengthList(JerrysList); i++) {
            jerry *happy_jerry = getDataByIndex(JerrysList, i);
            if (happy_jerry->happiness > 19) {
                happy_jerry->happiness = happy_jerry->happiness + 15;
                if (happy_jerry->happiness > 100) {
                    happy_jerry->happiness = 100;
                }
                continue;
            }
            happy_jerry->happiness = happy_jerry->happiness - 5;
            if (happy_jerry->happiness < 0) {
                happy_jerry->happiness = 0;
            }
        }
        printf("The activity is now over ! \n");
        displayList(JerrysList);
        return;
    }
    //play golf
    if (strcmp(activity_choice, "2") == 0) {
        for (int i = 1; i <= getLengthList(JerrysList); i++) {
            jerry *happy_jerry = getDataByIndex(JerrysList, i);
            if (happy_jerry->happiness > 49) {
                happy_jerry->happiness = happy_jerry->happiness + 10;
                if (happy_jerry->happiness > 100) {
                    happy_jerry->happiness = 100;
                }
                continue;
            }
            happy_jerry->happiness = happy_jerry->happiness - 10;
            if (happy_jerry->happiness < 0) {
                happy_jerry->happiness = 0;
            }
        }
        printf("The activity is now over ! \n");
        displayList(JerrysList);
        return;
    }
    //Adjust the picture settings on the TV
    if (strcmp(activity_choice, "3") == 0) {
        for (int i = 1; i <= getLengthList(JerrysList); i++) {
            jerry *happy_jerry = getDataByIndex(JerrysList, i);
            happy_jerry->happiness = happy_jerry->happiness + 20;
            if (happy_jerry->happiness > 100) {
                happy_jerry->happiness = 100;
            }
        }
        printf("The activity is now over ! \n");
        displayList(JerrysList);
        return;
    }
    printf("Rick this option is not known to the daycare ! \n");
}

// user's input in menu is 9
void userChoice9(MVhash PCMulti, linked_list JerrysList, int planetNum, planet *Planets_arr[]) {
    //free all and exit the program
    destroyMultiValueHashTable(PCMulti);
    destroyList(JerrysList);
    destroy_PlanetsArr(Planets_arr, planetNum);
    exit(1);
}

int main(int argc, char *argv[]) {
    int planetNum = atoi(argv[1]);

    // create array of pointers to planets
    planet *Planets_arr[planetNum];

    //create MultiValueHashTable - key is physical character's name, value is Jerry
    MVhash PCMulti = createMultiValueHashTable(CopyPCName, FreePCName, PrintPCName, CopyJerry, FreeShallowJerry,
                                               PrintJerry, EqualPCName, 10, TransformPCNameToNumber);
    //create linked list of Jerry's
    linked_list JerrysList = createLinkedList(FreeJerry, PrintJerry, PartJerry);

    read_configuration(argv[2], Planets_arr, planetNum, JerrysList, PCMulti);

    char user_choice[300] = "1";
    while (user_choice) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s", user_choice);

        if (strcmp(user_choice, "1") == 0) {
            userChoice1(PCMulti, JerrysList, planetNum, Planets_arr);
        }
        if (strcmp(user_choice, "2") == 0) {
            userChoice2(PCMulti, JerrysList, planetNum, Planets_arr);
        }
        if (strcmp(user_choice, "3") == 0) {
            userChoice3(PCMulti, JerrysList);
        }

        if (strcmp(user_choice, "4") == 0) {
            userChoice4(PCMulti, JerrysList);
        }

        if (strcmp(user_choice, "5") == 0) {
            userChoice5(PCMulti, JerrysList, planetNum, Planets_arr);
        }
        if (strcmp(user_choice, "6") == 0) {
            userChoice6(PCMulti, JerrysList, planetNum, Planets_arr);
        }
        if (strcmp(user_choice, "7") == 0) {
            userChoice7(PCMulti, JerrysList, planetNum, Planets_arr);
        }
        if (strcmp(user_choice, "8") == 0) {
            userChoice8(PCMulti, JerrysList);
        }
        if (strcmp(user_choice, "9") == 0) {
            printf("The daycare is now clean and close ! \n");
            userChoice9(PCMulti, JerrysList, planetNum, Planets_arr);
            break;
        }

        // if user's choice is not a number between 1 and 9
        if (checkInput(user_choice) == false) {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
    }
}
