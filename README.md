# Underwater_explore — Prototype Report & Outline

## Overview
This repository contains my prototype for a scene using OpenGL. My scene is a simple underwater exploration demo. To run the exectuable you need to extract the executable zip and double click on the application.exe. 

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

---

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
- GLFW, GLAD, GLEW / OpenGL
- GLM (math)
- Assimp (model import)
- irrKlang (audio)
- Dear ImGui (UI)
- FastNoiseLite (procedural noise)

## Gameplay description
There is minimal gameplay due to the focus being on creating a scene rather than a game. The user can move around the scene using WASD for forward, left, back and right respectively. Due to being 3D the direction rotates with where the camera is pointing. To move the camera to pan around the scene you move the mouse in the direction you wish to pan towards. The objective is to move around the scene and collect 5 bottles that are littering the ocean. The ocean bed and location of the bottles is procedurally generated each time the scene is ran. There is plants that spawn in the world which vary in height generated in the terrain generation. These plants can only spawn in the 'murky' biome. There are 3 biomes plains, murky and lava. Plains and murky are generated through a biome noise while lava is generated at a certain depth. Both plants and bottles are models which are imported using assimp. The bottle moves up and down and rotates based off time being my timed-animations.

There is a dynamic light source that moves with the player and uses blingPhong reflecting off surrounding objects. Sound is implemented using IrrKlang. There is a background track which loops continuously. There is also a ding sound effect that plays when you collect a bottle.

## Use of AI / Procedural techniques
Throughout my code I comment on where AI was used. I used it to help with the logic behind calculating the normal of vertices in procedural terrain (proceduralGeneration.cpp generateNormals()). I was having issues linking dependencies correctly for plant.h/.cpp so AI assisted in resolving this issue. Finally ai was used to help create an outline of the README for me to add to and edit. 

Ai was beeing used to help me implementing light sources across the lava sources. I created the initial logic and code but when it repeatedly wasn't working I used AI to try and help fix but even then I failed to resolve this. I mention further on this in my video.

## Game programming patterns used
I did not use any advanced Game programming patterns such as Object pooling. This is due to the scale of the project being very small as well as no clear places to add it. I considered object pooling for either the plants or bottles but couldn't see the benefit considering they are spawned once and only bottles are interactable. There is only 5 max bottles so felt would be overkill. This does not mean I did not follow proper programming techniques such as OOP which is used.

## Game mechanics and how they are coded (examples)
- Movement & camera: handled in `Player` class (see [Player.cpp](Player.cpp) / [Player.h](Player.h)); mouse callbacks registered in [Underwater_explore.cpp](Underwater_explore.cpp).
- Item collection: `Collectable` objects are placed by `ProcGen`; player proximity checks (likely in game loop) trigger pickup logic—see [collectable.h](collectable.h) and [collectable.cpp](collectable.cpp).
- Plant rendering: `Plant` constructs a `Model("art/models/plant/plant.obj")` in [plant.cpp](plant.cpp) and draws multiple instances by translating the model matrix.
- Shaders: lighting and model shading controlled via shader pairs: [lightShader.vert](lightShader.vert), [lightShader.frag](lightShader.frag), and [modelFragmentShader.frag](modelFragmentShader.frag).

---



## Sample screens / assets
No exported screenshots tracked in repo. Assets and models available under:
- art models: `art/models/plant/plant.obj` (referenced via [plant.cpp](plant.cpp)) and raw Blender sources: `art/models/plant/plant.blend1` and `art/models/bottle/bottle.blend1`
- sprite/texture sources: `art/*.aseprite` files (binary)
- Shaders: [vertexShader.vert](vertexShader.vert), [modelFragmentShader.frag](modelFragmentShader.frag)

To capture sample screens: run the executable (build via [Underwater_explore.sln](Underwater_explore.sln)) and take screenshots of the rendered window.

---

## Exception handling and test cases
Current state (observed):
- Limited explicit exception handling in main loop. Typical C++ patterns used (return codes, console messages). Example: GLAD init failure prints message in [Underwater_explore.cpp](Underwater_explore.cpp).
- Dear ImGui contains internal debug/assert checks (see [imgui/imgui.cpp](imgui/imgui.cpp)), useful during development.
- No dedicated unit tests detected in repository.

Recommendations:
- Add guards and return-value checks for asset loading (Assimp model loads, texture loads via `stbi_load`) in [plant.cpp](plant.cpp) and model/loader code.
- Wrap critical initialization with try/catch and log to console; e.g., for GLFW/GLAD/Assimp initialization in [Underwater_explore.cpp](Underwater_explore.cpp).
- Introduce small automated tests for deterministic parts (e.g., noise output range tests using [FastNoiseLite.h](FastNoiseLite.h)).
- Add runtime checks for file existence for assets referenced in code (models, shaders).

---

## Further details: how the prototype works
- Startup sequence in [Underwater_explore.cpp](Underwater_explore.cpp):
  - Seed RNG, init GLFW, create window, load GLAD, compile shaders (`Shader`), init ImGui, instantiate `ProcGen` and call `procTerrainGen()`.
  - Get returned lists: plants (`map->getPlants()`), lava, collectables (`map->generateCollectables()`), bind collectables, create `Player`.
  - Enter render loop where shaders are used and objects drawn.
- Asset loading: Models use Assimp (includes in [Underwater_explore.cpp](Underwater_explore.cpp)); textures through `stb_image.h` and [stbImageLoader.cpp](stbImageLoader.cpp).
- UI/Debug: ImGui demo windows are included (see [imgui/imgui_demo.cpp](imgui/imgui_demo.cpp)) for control and diagnostics.

---

## Evaluation — achievements & hindsight
What was achieved:
- Working prototype with procedural terrain, plant/collectable spawning, model rendering, basic player control and ImGui-based tooling.
- Integration of several libraries (Assimp, stb_image, FastNoiseLite, irrKlang, Dear ImGui) into a single Visual Studio project.

What I'd do differently:
- Replace absolute include/library paths in [Underwater_explore.vcxproj](Underwater_explore.vcxproj) with a portable build (CMake + vcpkg) to improve reproducibility.
- Stream procedural generation across threads to avoid frame hitches (producer-consumer with a generation worker thread).
- Export Blender sources to runtime-friendly formats (glTF/OBJ) and use Git LFS or external asset hosting for large binary assets (e.g., `art/models/*.blend1` are Blender binary data).
- Add unit tests for deterministic components (noise, placement algorithms), and add automated scene sanity checks.
- Improve resource management (unique_ptr/shared_ptr) and explicit error handling around asset loads.

---

## Next steps I can help perform
- Create a README.md file in repo (this is the content).
- Add a `.gitignore` for Visual Studio and exclude large binary Blender/aseprite files.
- Fix `variables.h` macro precedence (example: wrap `MAP_SIZE` with parentheses).
- Add basic runtime checks for asset loads, or generate a small UML PNG showing class relations.

---

If you want, I will:
- Commit this README to `README.md`, and/or
- Generate the `.gitignore` and a small UML diagram image and add to repo.
