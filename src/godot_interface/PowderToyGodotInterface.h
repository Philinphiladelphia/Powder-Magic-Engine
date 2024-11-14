#ifndef POWDER_TOY_INTERFACE_H
#define POWDER_TOY_INTERFACE_H

#include <deque>
#include <chrono>
#include <mutex>
#include <vector>

// Powder Toy Imports
#include "simulation/Simulation.h"
#include "gui/game/GameModel.h"

// Singleton imports
#include "prefs/GlobalPrefs.h"
#include "client/Client.h"
#include "client/http/requestmanager/RequestManager.h"
#include "common/platform/Platform.h"
#include "graphics/Graphics.h"
#include "simulation/SaveRenderer.h"
#include "simulation/SimulationData.h"
#include "common/tpt-rand.h"
#include "gui/game/Favorite.h"
#include "gui/game/GameController.h"
#include "gui/game/GameView.h"
#include "gui/interface/Engine.h"
#include "SimulationConfig.h"

struct ExplicitSingletons
{
	// These need to be listed in the order they are populated in main.
	std::unique_ptr<GlobalPrefs> globalPrefs;
	http::RequestManagerPtr requestManager;
	std::unique_ptr<Client> client;
	std::unique_ptr<SaveRenderer> saveRenderer;
	std::unique_ptr<Favorite> favorite;
	std::unique_ptr<ui::Engine> engine;
	std::unique_ptr<SimulationData> simulationData;
	std::unique_ptr<GameController> gameController;
    std::unique_ptr<Simulation> simulation;
};

struct PowderCircle
{
    int x;
    int y;
    int r;
    int element;
};

class PowderToyInterface {
public:
    PowderToyInterface();

    void MakeCircle(PowderCircle &circle);
    bool RequestsBuffered();
    void SetSimFramerate(int framerate);
    void SetSimDrawingFrequency(int frequency);
    void RunSimFrame();

    void GetParticles(int* particles);

    void InitializeSingletons();

private:

    std::unique_ptr<ExplicitSingletons> explicit_singletons_;
};

#endif // POWDER_TOY_INTERFACE_H