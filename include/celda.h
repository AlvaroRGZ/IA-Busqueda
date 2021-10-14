#pragma once

struct Cell {

    bool value; // Libre    --> false
                // No libre --> true
                
    char state = ' '; // X   --> significa que el taxi ha pasado previamente por ese sitio
                      // " " --> significa que está libre
                      // O   --> significa que hay un obstáculo
};