#include "VSModEngine.h"
#include "Core/EditorApp.h"


int main(int argc, char* argv[]){
    Logger::Init();
    EditorApp app;
    CORE_INFO("Hello, world!");
    app.Init();
    app.Run();
    app.Shutdown();
    return 0;
}