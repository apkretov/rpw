#include "HomeTheaterFacade.h"

/* Java 
public class HomeTheaterTestDrive { // Here we're creating the components right in the test drive. Normally the client is given a facade, it doesn't have to construct one itself.
    public static void main(String[] args) {
        // instantiate components here
        HomeTheaterFacade homeTheater = new HomeTheaterFacade(amp, tuner, dvd, cd, projector, screen, lights, popper); // First you instantiate the Facade with all the components in the subsystem.
        homeTheater.watchMovie("Raiders of the Lost Ark"); // Use the simplified interface to first start the movie up, and then shut it down.
        homeTheater.endMovie();
    }
}
*/
int main() { // Here we're creating the components right in the test drive. Normally the client is given a facade, it doesn't have to construct one itself.
    Amplifier amp; // instantiate components here
    Tuner tuner;
    DvdPlayer dvd;
    CdPlayer cd;
    Projector projector;
    Screen screen;
    TheaterLights lights;
    PopcornPopper popper;
    
    HomeTheaterFacade homeTheater(amp, tuner, dvd, cd, projector, screen, lights, popper); // First you instantiate the Facade with all the components in the subsystem.
    
    homeTheater.watchMovie("Raiders of the Lost Ark"); // Use the simplified interface to first start the movie up, and then shut it down.
    homeTheater.endMovie();
    
    return 0;
}