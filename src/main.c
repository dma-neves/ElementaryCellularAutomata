#include "CellularAutomata.h"

#include <stdio.h>

int main()
{
    printf("Rule number: ");
    int ruleNumber;
    scanf("%d", &ruleNumber);

    init(800, 800, "Cellular Automata", ruleNumber);
    run();
}