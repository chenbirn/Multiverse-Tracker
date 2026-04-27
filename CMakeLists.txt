cmake_minimum_required(VERSION 3.29)
project(HW3_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(HW3_1
        LinkedList.c
        LinkedList.h
        KeyValuePair.c
        KeyValuePair.h
        MultiValueHashTable.c
        MultiValueHashTable.h
        HashTable.c
        HashTable.h
        Defs.h
        JerryBoreeMain.c
        Jerry.c)
