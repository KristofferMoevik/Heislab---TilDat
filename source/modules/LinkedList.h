#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
   int data;
   int key;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

void printList();

void insertFirst(int key, int data);

struct node* deleteFirst();

bool isEmpty();

int length();

struct node* find(int key);

struct node* delete_key(int key);

void sort();

void reverse(struct node** head_ref);