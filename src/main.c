#include <stdio.h>
#include <stdlib.h>

#include "machine.h"


int main() {
    FILE* obj = fopen("objectfile-example.txt", "r");
    struct Machine* machine = instantiateMachine(obj);

    printf("Computation ended with state [%d]\n---\n", runMachine(machine));
    seeResultingMachine(machine);

    return 0;
}
