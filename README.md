**Team Members and Roles**
---------------------------------------------------------------------
**Iris Chow** - Developer/Writer
- Repo: https://github.com/irisicle/8051Project.git


**Engine Design**
---------------------------------------------------------------------
- 2D game engine using the lecture material that you provided in class as the base.
- Pure ECS approach by referencing your lecture notes as well as doing my own extensive research.
- SDL3 library


**Systems**
---------------------------------------------------------------------
- Game Loop
	- Controls the main execution of the game.
- Scene Management System
	- Handles scene transitions (eg. menu and gameplay).
- Entity System
	- Creates game objects in the world - player, crops, tools, items, etc.
- Crop System
	- Tracks crop states - planted, growing, and ready to harvest.
- Tilemap Rendering System
	- Renders .tsx and .tmx files.
- Keyboard Input System
	- Processes keyboard input from the player.
- Time System for crop growth
	- Manages timers that control crop growth progression.
- SFX System
	- Plays background music and sound effects for player actions.


**Game Design**
---------------------------------------------------------------------
**Title**

Teeny Farm

**Description**

Teeny Farm is a cozy farm sim inspired by Harvest Moon, Stardew Valley and the like. Restore an abandoned farm by growing, harvesting and selling crops. Use your profits to improve and expand the farm any way you like! Teeny Farm is an ideal game for unwinding especially after a long day at school or work.

**Narrative**

After inheriting a small farm from your ancestors, your mission is to bring it back to life to the way it was, or better than when your great-grandparents once ran it. Starting with only basic tools and a handful of seeds, you must cultivate crops and rebuild your family's pride and joy one harvest at a time.

**High-Level Features**
- Core Gameplay Loop
	- Move -> Till Soil -> Plant -> Water -> Grow -> Harvest -> Earn Coins -> Unlock -> Repeat
- Player movement
	- Player can roam freely around the map using WASD.
- Farming interaction system
	- Player can intuitively interact with the map to:
		- Till soil
		- Plant seeds
		- Water crops
		- Harvest crops when ready
		- Sell crops for cash
		- Use cash to unlock/expand farm
- Crop growth system
	- Plants go through multiple states/stages.
- Rewarding economy system
	- Convert crops into coins to build and expand farm.
- Audio system
	- BGM and SFX

**Art Assets**
- Ideally I would like to draw my own assets but for the sake of time I'll be using a free 2D pixel art asset pack that I found on itch.io:
	- Asset pack used -  https://cupnooble.itch.io/sprout-lands-asset-pack

**Platforms supported**
- macOS, Windows


**Tools and Risks**
---------------------------------------------------------------------
**Tools**
- Engine framework
	- SDL3
- IDE
	- CLion
- Version Control
	- Git/Github
- Assets
	- Itch.io free asset packs
- Map Editor
	- Tiled


**Risks**
- Possible scope creep - wanting to add more features and expand beyond the best of my ability.
- Perfectionism - spending too much time or focusing on making it look perfect. Will try to utilize timeboxing.
- Time management struggles - as we're nearing the end of the semester, everything is starting to pile up with final exams and deadlines for other courses approaching.
- Trying to stay motivated when there's so much on my plate already.
- Lack of support since I'm going solo on this project.
