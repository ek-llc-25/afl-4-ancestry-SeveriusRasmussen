#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ancestry.h"

struct person_t *make_person(char *first_name, char *last_name, int year_born) {
    // Allokér plads i heap'en til en `struct person_t`.
    struct person_t *new = malloc(sizeof(struct person_t));
    if (new == NULL) return NULL;
    //DONE (new->...) Allokér også plads i heap'en til kopier af `first_name` og `last_name`.
    //DONE (strcpy();) Kopiér indholdet fra `first_name` og `last_name` over i kopierne.
    //DONE (strlen(last_name) + 1) Husk at gøre plads til både alle tegnene i navnene + 1 NUL-byte.

    // First name
    new->first_name = malloc(strlen(first_name) + 1);
    if (new->first_name == NULL)
    {
        free(new);
        return NULL;
    }
    strcpy(new->first_name, first_name);

    // Last name
    new->last_name = malloc(strlen(last_name) + 1);
    if (new->last_name == NULL)
    {
        free(new->first_name); //free first_name hvis last_name fejler.
        free(new);
        return NULL;
    }
    strcpy(new->last_name, last_name);

    // Year
    new->year_born = year_born;
    return new;
}

void free_person(struct person_t *person) {
    //Done Der skal være et free()-kald for hver malloc() i make_person().
    //Done Du må gerne sætte `first_name` og `last_name` til NULL *EFTER* de er free()'et.
    //First Name
    free(person->first_name);
    person->first_name = NULL;

    //Last Name
    free(person->last_name);
    person->last_name = NULL;

    free(person);
    person = NULL;

}

struct ancestry_node_t *make_tree(struct person_t *person) {
    //DONE Allokér plads til en `struct ancestry_node_t`.
    struct ancestry_node_t *node = malloc(sizeof(struct ancestry_node_t));
    if (node == NULL) return NULL;

    //DONE Sæt `person` til input-personen.
    node->person = person;

    //DONE Sæt `mom` og `dad` til NULL.
    node->mom = NULL;
    node->dad = NULL;

    return node;
}

bool add_mom(struct ancestry_node_t *child_node, struct person_t *mom_person) {
    //Done Hvis der allerede er en mor-stamtavle, skal funktionen fejle.
    if (!child_node || !mom_person) return false; // Hvis ingen child eller mom, fejler det.
    if (child_node->mom) return false; // Hvis child har allerede en mom, fejler det.

    //Done Hvis ikke, skal `mom_person` indsættes i en `mom_node` som først skal allokeres.
    struct ancestry_node_t *mom_node = make_tree(mom_person);
    if (!mom_node) return false;

    child_node->mom = mom_node;
    return false;
}

bool add_dad(struct ancestry_node_t *child_node, struct person_t *dad_person) {
    //Done Hvis der allerede er en far-stamtavle, skal funktionen fejle.
    if (!child_node || !dad_person) return false;
    if (child_node->dad) return false;

    //Done Hvis ikke, skal `dad_person` indsættes i en `dad_node` som først skal allokeres.
    struct ancestry_node_t *dad_node = make_tree(dad_person);
    if (!dad_node) return false;

    child_node->dad = dad_node;
    return false;
}

void free_tree(struct ancestry_node_t *node) {
    if (!node) return;
    //Done Kald `free_person()` på personen i noden.
    free_tree(node->person);
    //Done Kald `free_tree()` på begge forældre-stamtræer.
    free_tree(node->mom);
    free_tree(node->dad);
    //Done Sæt pointerne til NULL efter de er free()'et.
    node->person = NULL;
    node->mom = NULL;
    node->dad = NULL;

    free(node);
}

void print_tree_recursive(struct ancestry_node_t *node, char *prefix, bool is_last) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_last ? "|- " : "|- ");
    printf("%s %s\n", node->person->first_name, node->person->last_name);

    char new_prefix[1000];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "   ");

    if (node->mom != NULL && node->dad != NULL) {
        print_tree_recursive(node->mom, new_prefix, false);
        print_tree_recursive(node->dad, new_prefix, true);
    } else if (node->mom != NULL) {
        print_tree_recursive(node->mom, new_prefix, true);
    } else if (node->dad != NULL) {
        print_tree_recursive(node->dad, new_prefix, true);
    }
}

void print_tree(struct ancestry_node_t *node) {
    print_tree_recursive(node, "", true);
}
