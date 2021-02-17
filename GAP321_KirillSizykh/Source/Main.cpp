#include <Application/GameApp.h>
#include <Logic/GameLogic.h>

#ifdef _DEBUG
#include <VLD/vld.h>
#endif

int main(int argc, const char** argv)
{
    GameApp app;

    if (!app.Init())
    {
        return 1;
    }

    app.Run();

    app.Cleanup();

    return 0;
}