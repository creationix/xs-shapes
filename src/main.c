#include <stdio.h>

#include "xsAll.h"
#include "mc.xs.h"

extern txPreparation *xsPreparation();

///////////////////////////////////////////////////////////////////////////////
// Main app testing design.
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    static txMachine root;
    int error = 0;
    txMachine *machine = &root;
    txPreparation *preparation = xsPreparation();

    c_memset(machine, 0, sizeof(txMachine));
    machine->preparation = preparation;
    machine->keyArray = preparation->keys;
    machine->keyCount = (txID)preparation->keyCount + (txID)preparation->creation.keyCount;
    machine->keyIndex = (txID)preparation->keyCount;
    machine->nameModulo = preparation->nameModulo;
    machine->nameTable = preparation->names;
    machine->symbolModulo = preparation->symbolModulo;
    machine->symbolTable = preparation->symbols;

    machine->stack = &preparation->stack[0];
    machine->stackBottom = &preparation->stack[0];
    machine->stackTop = &preparation->stack[preparation->stackCount];

    machine->firstHeap = &preparation->heap[0];
    machine->freeHeap = &preparation->heap[preparation->heapCount - 1];
    machine->aliasCount = (txID)preparation->aliasCount;

    machine = fxCloneMachine(&preparation->creation, machine, "myxs", NULL);

    xsBeginHost(machine);
    {
        xsVars(2);
        {
            xsTry
            {
                xsCall1(xsGlobal, xsID_require, xsString("main"));
            }
            xsCatch
            {
                xsStringValue message = xsToString(xsException);
                fprintf(stderr, "### %s\n", message);
                error = 1;
            }
        }
    }
    xsEndHost(the);
    xsDeleteMachine(machine);

    return error;
}
