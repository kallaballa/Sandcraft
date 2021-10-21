# Sandcraft
A two player (and soon more) falling sand game for the web. 

## The Game
The players are joined in a sandbox where they play and express whatever they want with diverse materials that act and interact.

## Heritage
The Particle logic is based on https://github.com/zear/SDLSand, which itself is based on a series of reimplementations and ports. At the moment Sandcraft still looks almost identical to SDLSand but much has changed codewise.i

## Tech
The game is written in C++ though its primary target is the web, Emscripten is used to compile the code to WebAssembly which runs in the browser. To achieve direct communication between the game instances a complex setup of various channels is performed (websocket, webrtc, stun). The signaling server (websocket) is called SandcraftServer and you can find it here; https://github.com/kallaballa/SandcraftServer. The particle behaviour is based on a cellular automaton. At the moment it doesn't compile for native platforms but that is only temporary (till i get around to it). 


Demo: https://phokis.at/sandcraft.html
