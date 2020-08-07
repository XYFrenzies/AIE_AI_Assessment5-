


#include "Application.h"

int main(int argc, char* argv[])
{
    {
        Application app; // constructor
        app.Startup();
        app.Run();
    }

    return 0;
}