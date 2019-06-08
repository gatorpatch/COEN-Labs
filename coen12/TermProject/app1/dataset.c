#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    int id;
    int age;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list {
    int count;
    struct node *head;
}LIST;

typedef struct set {
    int count;



