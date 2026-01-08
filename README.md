# Underwater_explore — Prototype Report & Outline

## Overview
This repository contains my prototype for a scene using OpenGL. My scene is a simple underwater exploration demo. To run the exectuable you need to extract the executable zip and double click on the application.exe. 

## Youtube link

Link - https://youtu.be/TXZereqWp_4

## How to run the executable/ build solution

First you need to extract the zip folder titled debug from the respository. Then to run the execuatable open the extracted folder and double click or run the beat dungeon.exe file.

To build the project from the repository you need to clone all folders and then build it in visual studio community 2022 Debug x64. All dependencies should be linked correctly as I used the paths from the lab sessions.

## README Outline

1. Project concept & short summary
2. Dependencies used (build/run)
3. Gameplay description
4. Use of AI / procedural techniques
5. Game programming patterns used
6. Game mechanics and implementation notes
7. Design (UML / class relationships)
8. Sample screens & asset references
9. Exception handling & test cases
10. Further implementation details (how prototype works)
11. Evaluation: achievements and lessons learned
12. Next steps and improvement suggestions

## Dependencies used
The dependencies used were:
- OpenGL for rendering of the project.
- GLFW for the context window and GLAD for wrangling the shaders.
- FastNoiseLite.h for noise generation used in poceduralGeneration.h.
- stb_image.h/ stbImageLoader.cpp are used for loading textures.
- For the UI I used ImGui which I recieved prior permission to use. This is used for add the signature and for displaying a bottle collection count.
- IrrKlang is used for audio of both background music and bottle collection sound effects
- Assimp is used for model loading
- GlSL is used for the vertex and fragment shaders

External runtime / build libraries (declared in project):
- GLFW, GLAD, OpenGL
- GLM (math)
- Assimp (model import)
- irrKlang (audio)
- Dear ImGui (UI)
- FastNoiseLite (procedural noise)

All models and textures I made myself however the sound effects I got from:
Music from - https://jdsherbert.itch.io/ambiences-music-pack?download
Sound effect from - https://www.epidemicsound.com/?utm_source=microsoft&utm_medium=paidsearchbrand&utm_campaign=SEM%7CGBR%7Cen%7Cen%7CBrand&utm_term=epidemic%20sound&msclkid=aa175cdb84921de103b035bbb5a2acd6&utm_content=brand_name

## Gameplay description
There is minimal gameplay due to the focus being on creating a scene rather than a game. The user can move around the scene using WASD for forward, left, back and right respectively. Due to being 3D the direction rotates with where the camera is pointing. To move the camera to pan around the scene you move the mouse in the direction you wish to pan towards. The objective is to move around the scene and collect 5 bottles that are littering the ocean. The ocean bed and location of the bottles is procedurally generated each time the scene is ran. There is plants that spawn in the world which vary in height generated in the terrain generation. These plants can only spawn in the 'murky' biome. There are 3 biomes plains, murky and lava. Plains and murky are generated through a biome noise while lava is generated at a certain depth. Both plants and bottles are models which are imported using assimp. The bottle moves up and down and rotates based off time being my timed-animations.

There is a dynamic light source that moves with the player and uses blingPhong reflecting off surrounding objects. Sound is implemented using IrrKlang. There is a background track which loops continuously. There is also a ding sound effect that plays when you collect a bottle.

## Use of AI / Procedural techniques
Throughout my code I comment on where AI was used. I used it to help with the logic behind calculating the normal of vertices in procedural terrain (proceduralGeneration.cpp generateNormals()). I was having issues linking dependencies correctly for plant.h/.cpp so AI assisted in resolving this issue. Finally ai was used to help create an outline of the README for me to add to and edit. 

Ai was beeing used to help me implementing light sources across the lava sources. I created the initial logic and code but when it repeatedly wasn't working I used AI to try and help fix but even then I failed to resolve this. I mention further on this in my video.

Finally AI was used in an attempt to generate unit tests. However the unit tests were unsuccessful (could not be ran) but I kept them in to show them.

## Game programming patterns used
I did not use any advanced Game programming patterns such as Object pooling. This is due to the scale of the project being very small as well as no clear places to add it. I considered object pooling for either the plants or bottles but couldn't see the benefit considering they are spawned once and only bottles are interactable. There is only 5 max bottles so felt would be overkill. This does not mean I did not follow proper programming techniques such as OOP which is used.

## Game mechanics and how they are coded (examples)
- Movement & camera: handled in `Player` class (see [Player.cpp](Player.cpp) / [Player.h](Player.h)); mouse callbacks registered in [Underwater_explore.cpp](Underwater_explore.cpp).
Player movement is done by updating the camera position based off of user input. Update frag is then called to adjust the shaders appropriately. Update frag updates both camera and light position for the shaders as this updates the flare light source to move it with the player.

handleInput
<img width="671" height="485" alt="Screenshot 2026-01-08 234118" src="https://github.com/user-attachments/assets/879648e0-8333-42b0-ab13-d924e0cbeb99" />

updateFrag
<img width="1134" height="242" alt="Screenshot 2026-01-08 234125" src="https://github.com/user-attachments/assets/2c40b254-a38c-42a8-98cd-7f81cbc6616a" />

Collectable and plant are both classes that essentially just render the model. Plant also handles how many plant models are stacked on top of each other. I could of used inheritance for these but that would of actually increased code complexity due to how small these classes are.

Collectable
<img width="546" height="678" alt="Screenshot 2026-01-08 234152" src="https://github.com/user-attachments/assets/82bd1f6a-b454-4e8e-8c9e-95cc0eede3ec" />
<img width="501" height="475" alt="Screenshot 2026-01-08 234156" src="https://github.com/user-attachments/assets/bd92e843-ef05-46e2-8b46-92c8b6928102" />

Plant
<img width="652" height="628" alt="Screenshot 2026-01-08 234202" src="https://github.com/user-attachments/assets/bf8ec7d5-7dc4-4c4e-8946-c89feff019d7" />
<img width="553" height="392" alt="Screenshot 2026-01-08 234206" src="https://github.com/user-attachments/assets/fededdad-b0e6-4eef-8871-2921ea14db57" />

The modelFragmentShader and fragmentShader are different due to being used for different models. ModelFragmentShader is for imported models while FragmentShader is for the procedural terrain handling texture blending.

modelFragmentShader
<img width="491" height="604" alt="Screenshot 2026-01-08 234425" src="https://github.com/user-attachments/assets/21f7ac54-73ad-4671-b610-e25066e8cb4e" />
<img width="656" height="534" alt="Screenshot 2026-01-08 234431" src="https://github.com/user-attachments/assets/3b66cae7-0f65-4fff-a564-348f81d7ddea" />

fragmentShader
<img width="434" height="653" alt="Screenshot 2026-01-08 234438" src="https://github.com/user-attachments/assets/31e0869d-1374-4139-b76c-a790f43ab179" />


## Sample screens / assets
No exported screenshots tracked in repo. Assets and models available under:

Terrain
<img width="1270" height="706" alt="Screenshot 2026-01-08 234657" src="https://github.com/user-attachments/assets/c21a6ce1-23c2-4c76-9769-95c0fd40dd46" />

Terrain plains texture
<img width="64" height="64" alt="plains" src="https://github.com/user-attachments/assets/980f8f7b-3e55-4474-b677-c16251ead6d1" />

Terrain murky texture
<img width="64" height="64" alt="murky" src="https://github.com/user-attachments/assets/bfe68d01-0047-4a23-9c57-52cebebfd74b" />

Terrain lava texture
<img width="64" height="64" alt="lava" src="https://github.com/user-attachments/assets/6fb73740-8e19-4691-a5c2-22650b7adee6" />

Plant 
<img width="543" height="504" alt="Screenshot 2026-01-08 234713" src="https://github.com/user-attachments/assets/3547068e-ecba-4bcd-94e9-cf8780a07023" />

Plant textures
Stem
<img width="64" height="64" alt="stem" src="https://github.com/user-attachments/assets/240d98f1-cdf8-4118-a023-21a68bbf0edb" />

Leaves
<img width="64" height="64" alt="leaf" src="https://github.com/user-attachments/assets/39959870-e828-4303-94ba-2a463aedec5d" />

Bottle 
<img width="338" height="359" alt="Screenshot 2026-01-08 234731" src="https://github.com/user-attachments/assets/6e58b80b-42cb-4925-b976-c3169e3d274d" />

Bottle texture
<img width="64" height="64" alt="bottle" src="https://github.com/user-attachments/assets/61e0ef14-569d-40e0-bdc8-dcee8e805d08" />


## Exception handling and test cases

I attempted to add unit tests similarlly to how they were handled in my 30% coursework. This was via testing AI generated unit tests. However unlike last time I could not get them to work for my project. With more time I would ensure these were working but have left the failed unit tests in so they can still be seen. Most potential fixes I could find resolved around dependencies outside the allowed scope so decided not to pursue. I did still however complete user testing (with user consent) gaining the below feedback

Positives
- Ran smoothly
- Enjoyed the lighting from the 'flare' and how it affected the environment
- appreciated the effort of background (skybox) changing based off y axis
- Notice the subtle sound when collecting a bottle
- Procedural generation was good especially the smooth transitions from flat to mountains

Negatives
- Confused about what the objective was
- UI not dynamic to screen size
- Would of liked a more satisfying sound upon collecting a bottle
- Wanted a lightsource coming from the lava

To improve user testing in the future I will give them the wider context of the project and module specs. This is because most feedback was to do with it not being a complete game which is outside the project scope. I do however wish I had made it clearer what the user was meant to do (collect bottles) as even a scene needs clarity.

## Further details: how the prototype works - AI generated only as I feel it it covers the outline of what I describe earlier and in my video
- Startup sequence in [Underwater_explore.cpp](Underwater_explore.cpp):
  - Seed RNG, init GLFW, create window, load GLAD, compile shaders (`Shader`), init ImGui, instantiate `ProcGen` and call `procTerrainGen()`.
  - Get returned lists: plants (`map->getPlants()`), lava, collectables (`map->generateCollectables()`), bind collectables, create `Player`.
  - Enter render loop where shaders are used and objects drawn.
- Asset loading: Models use Assimp (includes in [Underwater_explore.cpp](Underwater_explore.cpp)); textures through `stb_image.h` and [stbImageLoader.cpp](stbImageLoader.cpp).
- UI/Debug: ImGui demo windows are included (see [imgui/imgui_demo.cpp](imgui/imgui_demo.cpp)) for control and diagnostics.

## Evaluation — achievements & hindsight
Although I did try to follow my project proposal after alot of trying and tutorial following on model animation I couldn't add the player's arms like I intended. I changed this advanced feature to include BlingPhong lighting.

What was achieved:
- working scene in OpenGL only using approved depencies which includes
  - procedural terrain generation
  - model rendering with multiple textures
  - basic player control to move around the scene
  - goal of collecting 5 bottles adding small amount of gamification
  - Music and sound effects
  - UI showing bottles collected and signature
  - Vertex and multiple fragment shaders implemented
  - 3D polygons with timed animations and textures
  - BlingPhong lighting implemented

What I'd do differently:
- Optimise game rendering by splitting terrain rendering down further only using in view chunks
- Add more game mechanics to make it feels like more of a game rather than just a scene
- Add an entity chasing you in the water most likely
- Improve resource management and explicit error handling around asset loads.

What I want to add if work on project continued
- light source from lava
- lava bubbles
- clear game objective
- working unit tests
- player model animation
