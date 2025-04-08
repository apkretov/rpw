#pragma once

#include <iostream>
#include <string>
#include "Amplifier.h"
#include "Tuner.h"
#include "DvdPlayer.h"
#include "CdPlayer.h"
#include "Projector.h"
#include "TheaterLights.h"
#include "Screen.h"
#include "PopcornPopper.h"
using std::cout;
using std::string;

/* Java
public class HomeTheaterFacade {
	Amplifier amp; // Here's the composition; these are all the components of the subsystem we are going to use.
	Tuner tuner;
	DvdPlayer dvd;
	CdPlayer cd;
	Projector projector;
	TheaterLights lights;
	Screen screen;
	PopcornPopper popper;

	public HomeTheaterFacade(Amplifier amp, // The facade is passed a reference to each component of the subsystem in its constructor.The facade then assigns each to the corresponding instance variable.
		Tuner tuner,
		DvdPlayer dvd,
		CdPlayer cd,
		Projector projector,
		Screen screen,
		TheaterLights lights,
		PopcornPopper popper)
	{
		this.amp = amp;
		this.tuner = tuner;
		this.dvd = dvd;
		this.cd = cd;
		this.projector = projector;
		this.screen = screen;
		this.lights = lights;
		this.popper = popper;
	}
	// other methods here

	public void watchMovie(String movie) { // watchMovie() follows the same sequence we had to do by hand before, but wraps it up in a handy method that does all the work.Notice that for each task we are delegating the responsibility to the corresponding component in the subsystem.
		System.out.println(�Get ready to watch a movie...�);
		popper.on();
		popper.pop();
		lights.dim(10);
		screen.down();
		projector.on();
		projector.wideScreenMode();
		amp.on();
		amp.setDvd(dvd);
		amp.setSurroundSound();
		amp.setVolume(5);
		dvd.on();
		dvd.play(movie);
	}

	public void endMovie() { // And endMovie() takes care of shutting everything down for us.Again, each task is delegated to the appropriate component in the subsystem.
		System.out.println(�Shutting movie theater down...�);
		popper.off();
		lights.on();
		screen.up();
		projector.off();
		amp.off();
		dvd.stop();
		dvd.eject();
		dvd.off();
	}
}
*/
class HomeTheaterFacade {
#pragma region Constructing your home theater facade
	Amplifier &amp; // Here's the composition; these are all the components of the subsystem we are going to use.
	Tuner &tuner;
	DvdPlayer &dvd;
	CdPlayer &cd;
	Projector &projector;
	TheaterLights &lights;
	Screen &screen;
	PopcornPopper &popper;
public:
	HomeTheaterFacade(Amplifier &amp, // The facade is passed a reference to each component of the subsystem in its constructor.The facade then assigns each to the corresponding instance variable.
		Tuner &tuner,
		DvdPlayer &dvd,
		CdPlayer &cd,
		Projector &projector,
		Screen &screen,
		TheaterLights &lights,
		PopcornPopper &popper)
		: amp(amp)
		, tuner(tuner)
		, dvd(dvd)
		, cd(cd)
		, projector(projector)
		, screen(screen)
		, lights(lights)
		, popper(popper) {
	}
	// other methods here
#pragma endregion //Constructing your home theater facade

#pragma region Implementing the simplified interface
	void watchMovie(const string &movie) { // watchMovie() follows the same sequence we had to do by hand before, but wraps it up in a handy method that does all the work.Notice that for each task we are delegating the responsibility to the corresponding component in the subsystem.
		cout << "Get ready to watch a movie...\n";
		popper.on();
		popper.pop();
		lights.dim(10);
		screen.down();
		projector.on();
		projector.wideScreenMode();
		amp.on();
		amp.setDvd(dvd);
		amp.setSurroundSound();
		amp.setVolume(5);
		dvd.on();
		dvd.play(movie);
	}

	void endMovie() { // And endMovie() takes care of shutting everything down for us.Again, each task is delegated to the appropriate component in the subsystem.
		cout << "Shutting movie theater down...\n";
		popper.off();
		lights.on();
		screen.up();
		projector.off();
		amp.off();
		dvd.stop();
		dvd.eject();
		dvd.off();
	}
#pragma endregion //Implementing the simplified interface
};