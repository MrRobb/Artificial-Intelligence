//
//  Tetris.hpp
//  Tetris AI
//
//  Created by Roberto Ariosa Hernández on 06/01/2018.
//

#ifndef Tetris_hpp
#define Tetris_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "ofApp.h"

#define CLOCKWISE true
#define COUNTERCLOCKWISE false

using namespace std;

// Data Structures
enum Blocks {I=0,J=4,L=8,O=12,S=16,T=20,Z=24};
struct Shape {
	int x;
	int y;
	Blocks shape;
};

#endif /* Tetris_hpp */
