#include <Application/GAP321App.h>
#include <Logic/GAP321Game.h>

#ifdef _DEBUG
#include <VLD/vld.h>
#endif

int main(int argc, const char** argv)
{
    GAP321App app;

    if (!app.Init())
    {
        return 1;
    }

    app.Run();

    app.Cleanup();

    return 0;
}