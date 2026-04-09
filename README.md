**Title**

Teeny Farm

**Description**

Teeny Farm is a cozy farm sim inspired by Harvest Moon, Stardew Valley and the like. Restore an abandoned farm by growing, harvesting and selling crops. Use your profits to improve and expand the farm any way you like! Teeny Farm is an ideal game for unwinding especially after a long day at school or work.

**Narrative**

After inheriting a small farm from your ancestors, your mission is to bring it back to life to the way it was, or better than when your great-grandparents once ran it. Starting with only basic tools and a handful of seeds, you must cultivate crops and rebuild your family's pride and joy one harvest at a time.

**Art Assets**
- Asset pack used -  https://cupnooble.itch.io/sprout-lands-asset-pack
- AI-generated main menu image.

**Systems**

- **Movement System**
  - Controls the player’s Facing component. 
  - Considers the facing direction of the player and does not reset their direction upon key up.
- **Keyboard Input System**
  - Processes keyboard input from the player.
  - Sends the player intent to the Movement System/Player Action System to handle.
- **Animation System**
    - Utilizes the player’s Facing component instead of the Velocity component to reference which Animation clip to play.
- **Player Control System**
    - Updates the player’s velocity corresponding to their intent.
- **Player Action System** *(Branched off of Event Response System)*
    - Grabs the player’s intent from “E” keyboard press and calls upon the appropriate useAction corresponding to the tool/item type selected.
- **Collision Interaction Response System**
    - Branched off of Event Response System as its own system.
    - No longer depends on World.
    - Collision events handler.
- **Mouse Interaction Response System**
    - Branched off of Event Response System as its own system.
    - No longer depends on World.
    - Mouse input events handler.
- **Render System**
    - Handles all Tilemap and Sprite rendering by calling upon Sprite System and Map Renderer.
- **Sprite System**
    - Now handles sprite rendering.
    - Calculates the world dest rect dynamically -> dest no longer stored in Sprite component.
- **Selection Highlight System**
    - Draws a box highlight around the target tile for farming visibility.
    - Calculates the target tile by grabbing the nearest tile to the player’s position depending on the direction they are facing and offsets by the camera.
- **Tool Service**
    - Looks at the selected tool type and processes the player action event.
    - Handles soil tilling and calls on Crop Service to handle the rest.
- **Crop Service** *(Not fully implemented)*
    - Handles crop planting, watering, and harvesting.
    - Handles crop states stored in the Crop component.
- **Crop Visual Database** *(Not fully implemented)*
    - Stores Crop component texture data based on Crop Type for rendering.
- **Crop Growth System**
    - Advances crop maturity using delta time.
- **Event Bindings** *(Replaced Event Response System)*
    - Removed Player Action subscription -> Tool Service handles that now.
- **Scene Management System**
    - Now owns World, Camera, Map Loader, and SelectionHighlightSystem.
    - Handles scene transitions (eg. menu and gameplay).
- **Entity Factory**
    - Creates game objects in the world - player, crops, cows, etc.
- **UI Entity Factory**
    - Creates the UI components on the screen.
- **Item Database** *(Not fully implemented)*
    - Stores ItemData component data
- **Inventory UI System** *(Temporary placeholder)*
    - Grabs the items from the player’s initialized Inventory component.
    - Creates a visual of Inventory slots of the items.
- **Tilemap Parsing and Rendering System**
    - Parses and renders all tilemap and object layers.
- **Audio System**
    - Plays and loops BGM
    - Sound effect after the player uses an action.
- **HUD System** *(Not fully implemented)*
    - Added font and wanted to make a hotbar showing the season, day and time, and weather.
- **Texture Manager**
  - Uses *SDL_SCALEMODE_NEAREST* to fix ugly texture bleeding (lines) on the tilemap.
- **Game Loop**
    - Uses VSync to ask SDL to wait for the monitor's refresh rate to reduce visible tearing in pixel texture rendering.
    - Controls the main execution of the game.
