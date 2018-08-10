#include <stdio.h>

#include "xs.h"
#include "mc.xs.h"

///////////////////////////////////////////////////////////////////////////////
// Main app testing design.
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    int error = 0;
	xsMachine* machine = fxPrepareMachine(NULL, xsPreparation(), "xs-shapes", NULL, NULL);

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
