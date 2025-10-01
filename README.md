# Stamtræer

Den fjerde afleveringsopgave handler om stamtræer.

Stamtræer er binære træer hvor hver forgrening er en biologisk forælder, og hver node indeholder en person (navn, fødeår).

Virkeligheden er selvfølgelig den, at selvom vi stadig har brug for en sædcelle og et æg før der kommer en baby, er det
at være forælder et bredere begreb end at have doneret sæd eller have født et barn. Stamtræer beskriver kun genetisk
ophav, og ikke familierelationer. Og det er lidt unøjagtigt at kalde ens biologiske forældre "mor" og "far", da man jo
kan påtage sig enhver kønsrolle uagtet hvilken funktion ens kønsorganer har spillet i tilbringelsen af personen i noden.
Stamtræer er lidt komplicerede, og familietræer er endnu mere komplicerede, og er faktisk ikke altid træer i datalogisk
forstand. Og hvis man tæller Tilbage til Fremtiden (1985) med, kan stamtræer også være cykliske grafer.

Men hvis I vil bære over med mig i bare denne uge, så leger vi at alle har en mog og en far, hvad end det betyder.
Så kan vi tage de polymorfe n-ære træer bagefter.

## Eksempler på stamtræer

Her er to tegninger af stamtræer:

```
                            o   o   o <- oldeforældre
                           /     \ /
                          o   o   o <- bedsteforældre
                           \ /   /
  o   o <- forældre         o   o <- forældre
   \ /                       \ /
    o <- rod                  o <- rod
```

De er lavet med to structs, som du kan læse i ancestry.h:

```c
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
```

Man kan godt lave stamtræer uden hjælpefunktioner og uden `malloc()`. Det tager bare lidt meget arbejde, fordi man skal
gentage sig selv. Og man mister alle sine structs når funktionen returnerer, så de skal allokeres i yderste lag. Det er
meget begrænsende. Det har jeg gjort i funktionen `small_stack_allocated_tree()`.

Det er nu alligevel nemmere at arbejde med datastrukturer hvis man laver små hjælpefunktioner. Det har jeg gjort i
funktionen `big_heap_allocated_tree()`. Meget af det som gentager sig er allokeringen (kald til `malloc()`), og det
kræver så at funktionerne har nogle tilsvarende `free()`-kald.

## Ugeopgavens indhold

I stedet for at lave træer manuelt, skal du lave et lille bibliotek af funktioner, der kan gøre det nemmere, hurtigere
og mere læseligt at oprette større træer. Jeg har lavet et eksempel-træ med de hjælpefunktioner i funktionen
`large_heap_allocated_tree()`, men funktionen virker kun hvis hjælpefunktionerne er lavet.

## Hints

Se linklist-koden og personer-koden fra undervisningen:
- https://github.com/ek-llc-25/linklist
- https://github.com/ek-llc-25/personer

Stamtræerne minder om linkede lister, men har to forgreninger i stedet for én.

Personerne er næsten ens, men der er et ekstra felt, `year_born` i denne aflevering.