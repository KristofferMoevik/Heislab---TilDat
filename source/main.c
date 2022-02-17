#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "driver/elevio.h"
#include "modules/LinkedList.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    insertFirst(1,10);
    insertFirst(2,20);
    insertFirst(3,30);
    insertFirst(4,1);
    insertFirst(5,40);
    insertFirst(6,56); 

    printf("Original List: "); 

    //print list
    printList();

    while(!isEmpty()) {            
        struct node *temp = deleteFirst();
        printf("\nDeleted value:");
        printf("(%d,%d) ",temp->key,temp->data);
    }  

    printf("\nList after deleting all items: ");
    printList();
    insertFirst(1,10);
    insertFirst(2,20);
    insertFirst(3,30);
    insertFirst(4,1);
    insertFirst(5,40);
    insertFirst(6,56);

    printf("\nRestored List: ");
    printList();
    printf("\n");  

    struct node *foundLink = find(4);

    if(foundLink != NULL) {
        printf("Element found: ");
        printf("(%d,%d) ",foundLink->key,foundLink->data);
        printf("\n");  
    } else {
        printf("Element not found.");
    }

    delete(4);
    printf("List after deleting an item: ");
    printList();
    printf("\n");
    foundLink = find(4);

    if(foundLink != NULL) {
        printf("Element found: ");
        printf("(%d,%d) ",foundLink->key,foundLink->data);
        printf("\n");
    } else {
        printf("Element not found.");
    }

    printf("\n");
    sort();

    printf("List after sorting the data: ");
    printList();

    reverse(&head);
    printf("\nList after reversing the data: ");
    printList();



    return 0;
}
