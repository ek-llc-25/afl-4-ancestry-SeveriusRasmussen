#ifndef AFL_3_ANCESTRY_ANCESTRY_H
#define AFL_3_ANCESTRY_ANCESTRY_H

struct person_t {
    char *first_name;
    char *last_name;
    int year_born;
};

struct ancestry_node_t {
    struct ancestry_node_t *mom;
    struct ancestry_node_t *dad;
    struct person_t *person;
};

struct person_t *make_person(char *first_name, char *last_name, int year_born);
void free_person(struct person_t *);

struct ancestry_node_t *make_tree(struct person_t *);
void print_tree(struct ancestry_node_t *);
bool add_mom(struct ancestry_node_t *, struct person_t *);
bool add_dad(struct ancestry_node_t *, struct person_t *);
void free_tree(struct ancestry_node_t *);

#endif //AFL_3_ANCESTRY_ANCESTRY_H