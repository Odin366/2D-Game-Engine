#include "CIntroState.h"
#include "Globals.h"

IntroState *IntroState::inst = 0;

void IntroState::Init()
{
	printf("Intro Init");

	// Initialize variables

		// Set initial cycle color to green
		cycleColor = { 0, 255, 0 };

		// Set color change speed
		colorIncrement = 1;

	// Load Resources

		// Load a single, white particle for particle system
		particle.LoadImage("Particle/particle.png");

		// Load the text overlay and make it mostly transparent
		vText.LoadText("Color Starfield effect", game->GetDefaultColor(), game->GetDefaultFont());
		vText.SetAlpha(50);

	// Get the particle system manager
	myPSysMan = PSysMan::GetInstance();

	// Load particle system
	myPSysMan->PushSys(STARFIELD, &particle, game->GetScreenWidth(), game->GetScreenHeight());
}

void IntroState::Finalize()
{	
	// Free textures
	particle.Free();
	vText.Free();

	// Delete pointers
	myPSysMan->DestroyInstance();
	myPSysMan = NULL;

	printf("Intro Finalize");
}

void IntroState::Draw()
{
	// Clear the screen to black
	game->ClearScreen(0, 0, 0);

	// Draw all particles
	myPSysMan->Draw();

	// Draw the text overlay
	vText.Draw((game->GetScreenWidth() - vText.GetWidth()) / 2, (game->GetScreenHeight() - vText.GetHeight()) / 2);
}

void IntroState::Update()
{
	// color cycle
	game->CycleColors(cycleColor, colorIncrement);

	// Change text color
	vText.SetColor(cycleColor.r, cycleColor.g, cycleColor.b);

	// change system color
	myPSysMan->systems.back()->SetSysColor(cycleColor);

	// Update particle system(s)
	myPSysMan->Update();

}

void IntroState::HandleEvents()
{
}

void IntroState::Pause()
{
	printf("Intro Paused");
}
void IntroState::Resume()
{
	printf("Intro Resumed");
}

