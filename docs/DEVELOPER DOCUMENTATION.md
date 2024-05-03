
# Developer Documentation

## Comprehensive Guide to Asteroid Game Development with ECS and SDL2

This section presents an in-depth developer documentation for the Asteroid Game. This game, developed using SDL2, is specifically crafted to demonstrate the use of the Entity Component System (ECS) architecture in game development.

___

### Developer Documentation for Asteroid Game

___

#### Table of Contents

1. **[Introduction](#1-introduction)**

2. **[Technical Specifications and Design](#2-technical-specifications-and-design)**

3. **[Architectural Overview](#3-architectural-overview)**

- 3.1. [Architectural Diagrams](#31-architectural-diagrams)

- 3.2. [Components Overview](#32-components-overview)

- 3.3. [Systems Overview](#33-systems-overview)

4. **[Development Guidelines and Standards](#4-development-guidelines-and-standards)**

5. **[Testing Framework and Coverage](#5-testing-framework-and-coverage)**

- 5.1. [Testing Strategy Outline](#51-testing-strategy-outline)

6. **[Versioning Information](#6-versioning-information)**

7. **[Performance Metrics and Optimization](#7-performance-metrics-and-optimization)**

8. **[Accessibility in Game Design](#8-accessibility-in-game-design)**

9. **[Troubleshooting and FAQs](#9-troubleshooting-and-faqs)**

10. **[Best Practice Recommendations](#10-best-practice-recommendations)**

11. **[References and Further Reading](#11-references-and-further-reading)**

12. **[Feedback and Updates](#12-feedback-and-updates)**

---

#### 1. Introduction

This documentation provides an in-depth guide to the development of the Asteroid Game using SDL2 and the ECS architecture. It is designed as a comprehensive resource for understanding and contributing to the project.

---

#### 2. Technical Specifications and Design

- ECS Framework:

- Entities: Comprises of Player, Bullet, and Asteroid, each being an instance of `entity`.

- Components: Includes structures like `sprite_component`, `movement_component`, `controller_component`, etc., serving as state holders.

- Systems: Encompasses `mobility_system` for updating positions, `sprite_system` for graphical rendering, `collision_system` for collision detection and response, and more.

- Rendering and Event Management: Utilizes SDL2 for graphical rendering and handling user interactions.

---

#### 3. Architectural Overview

- #### 3.1. Architectural Diagrams

- ECS Architecture Class Diagram

[![](https://mermaid.ink/img/pako:eNptVFFL9DAQ_CslzwomOe_OQwLX1jeFj-98a0ViGzXYJiVNhUP878ZuClnqS-nMdLOZdLJfpLGtIgfy5uTwnj2Wtcmy7FjdGa-9VuNTdnkpsrwqbD9Yo4wfn-Yv8pkvqtN59KqPZDGTZfVfmVY5bd6AhiWp-NfJs3K3QB6ZyKeuU37BXBzDUs7q9jYpy6kYB6e9em6WHUQ5Z6K3n6oPzFrjorHGOxsauLW6EZ-qs43257V2LZz10mtr1tpWeCebj2Bsre1Ep1_VOMg_6vZhN12nxz8XvREy-l5pcKg0-HzR3e9ux_m0o1qw5WgwjbxjKTGOhcQ1FhLLWEj8YiE1i5XEKRboldBmmDym50dJq1N5n0GilEOBgmhShBhCHKENQluEdgjtkzYMtWGoDUPFbF3MUTFHxRwV87R4QTfpRYAbx2L4AdEYd0A8xhvQJgYa0HWMMKBtDC2gXYwpoH3MJaBkCwU0LWkazquZO9L4iwFxckF65Xqp2zBavn61mvj3cFlrcgivrXQfNanNd_hOTt6ezqYhB-8mdUGmoZVelVqGidQvpGq1t-4BRtU8sb5_ABU4Zh4?type=png)](https://mermaid.live/edit#pako:eNptVFFL9DAQ_CslzwomOe_OQwLX1jeFj-98a0ViGzXYJiVNhUP878ZuClnqS-nMdLOZdLJfpLGtIgfy5uTwnj2Wtcmy7FjdGa-9VuNTdnkpsrwqbD9Yo4wfn-Yv8pkvqtN59KqPZDGTZfVfmVY5bd6AhiWp-NfJs3K3QB6ZyKeuU37BXBzDUs7q9jYpy6kYB6e9em6WHUQ5Z6K3n6oPzFrjorHGOxsauLW6EZ-qs43257V2LZz10mtr1tpWeCebj2Bsre1Ep1_VOMg_6vZhN12nxz8XvREy-l5pcKg0-HzR3e9ux_m0o1qw5WgwjbxjKTGOhcQ1FhLLWEj8YiE1i5XEKRboldBmmDym50dJq1N5n0GilEOBgmhShBhCHKENQluEdgjtkzYMtWGoDUPFbF3MUTFHxRwV87R4QTfpRYAbx2L4AdEYd0A8xhvQJgYa0HWMMKBtDC2gXYwpoH3MJaBkCwU0LWkazquZO9L4iwFxckF65Xqp2zBavn61mvj3cFlrcgivrXQfNanNd_hOTt6ezqYhB-8mdUGmoZVelVqGidQvpGq1t-4BRtU8sb5_ABU4Zh4)

- Gameloop Diagram

[![](https://mermaid.ink/img/pako:eNpl081OwzAMAOBXiXJmL7ADErT7Yy376YBDu0NovC0iTarUA41p707mNkChpyr-7DhycuallcCHfO9EfWCbuDDMf3d5hsLhlg0Gt-w-nxmFSmj1CSyLEyaMZJEDgcBelJH2Y9tm3ROP8i62BiPBgeuiEUXjXrFTg1A1HYgJjEL6UosTODYyqPDUkRGRcSB3Pt1ZJVukIFQaE5vkE1EBS6ytu_UJrU_zqT-BBjZ6B4MhZ0qxWf5Uy2vpyBp0VmvfQdtlx2bEHgKbmfqIffFAYh7Ed489NCeUBPQM2pb-mH2UEEoDSu2r0v9QSujxp2-tVaOs6atHUougErWDphZ_0ILQMqCNE-WbMvs-WhJaBbS2KPDfditC67y9AiyrncLv6awpmIUKWekATBfL2sn9Htcmj7RtgF2HueU3vAJXCSX9nT1fWcHxABUUfOh_pXBvBS_MxTtxRJudTMmH6I5ww4-0XayEv-oVH-6EbvwqSIXWpe0joLdw-QKH4vhS?type=png)](https://mermaid.live/edit#pako:eNpl081OwzAMAOBXiXJmL7ADErT7Yy376YBDu0NovC0iTarUA41p707mNkChpyr-7DhycuallcCHfO9EfWCbuDDMf3d5hsLhlg0Gt-w-nxmFSmj1CSyLEyaMZJEDgcBelJH2Y9tm3ROP8i62BiPBgeuiEUXjXrFTg1A1HYgJjEL6UosTODYyqPDUkRGRcSB3Pt1ZJVukIFQaE5vkE1EBS6ytu_UJrU_zqT-BBjZ6B4MhZ0qxWf5Uy2vpyBp0VmvfQdtlx2bEHgKbmfqIffFAYh7Ed489NCeUBPQM2pb-mH2UEEoDSu2r0v9QSujxp2-tVaOs6atHUougErWDphZ_0ILQMqCNE-WbMvs-WhJaBbS2KPDfditC67y9AiyrncLv6awpmIUKWekATBfL2sn9Htcmj7RtgF2HueU3vAJXCSX9nT1fWcHxABUUfOh_pXBvBS_MxTtxRJudTMmH6I5ww4-0XayEv-oVH-6EbvwqSIXWpe0joLdw-QKH4vhS)

-- ECS Architechture

```yaml

Class: sprite_component

Attributes:

- src: SDL_FRect

- texture: SDL_Texture*

- angle: float

Class: movement_component

Attributes:

- vel_x: float

- vel_y: float

- speed: float

Class: controller_component

Attributes:

- controller_x: float

- controller_y: float

Class: velocity_component

Attributes:

- vel_x: float

- vel_y: float

- drag: float

- speed: float

Class: rotation_component

Attributes:

- deviation: float

Class: tracking_component

Attributes:

- target: entity

- follow_mouse: bool

Class: lifespan_component

Attributes:

- lifespan: double

Class: collision_component

Attributes:

- tag: char

Class: asteroid_component

Attributes:

- spawn_timer: double

- spawn_delay: double

- vel_x: float

- vel_y: float

- width: float

- height: float

Class: mobility_system

Methods:

- update(registry&, double): void

Class: sprite_system

Methods:

- update(registry&, SDL_Renderer*): void

Class: controller_system

Methods:

- update(registry&, SDL_Event&): void

Class: velocity_system

Methods:

- update(registry&, double): void

Class: rotation_system

Methods:

- update(registry&, double): void

Class: tracking_system

Methods:

- update(registry&): void

Class: lifespan_system

Methods:

- update(registry&, double): void
	
Class: collision_system

Methods:

- update(registry&): void

Class: asteroid_system

Methods:

- update(registry&, double, SDL&): void

Class: input_system

Methods:

- update(registry&, entity, SDL_Event&, SDL&): void

```

- #### 3.2. Components Overview

- `sprite_component`: Manages the graphical representation of entities.

- `movement_component`: Handles the movement of entities.

- `controller_component`: Processes user input for entity control.

- `velocity_component`: Governs the velocity and drag of entities.

- `rotation_component`: Controls the rotation of entities.

- `tracking_component`: Enables entities to track and follow targets with rotation.

- `lifespan_component`: Determines the lifespan of entities.

- `collision_component`: Manages collision detection and response.

- `asteroid_component`: Controls the spawning and behavior of asteroids.

  

- #### 3.3. Systems Overview

- `mobility_system`: Updates the position of entities based on their movement and controller components.

- `sprite_system`: Renders the graphical representation of entities.

- `controller_system`: Processes user input and updates the controller component.

- `velocity_system`: Updates the position of entities based on their velocity and controller components.

- `rotation_system`: Rotates entities based on their rotation component.

- `tracking_system`: Enables entities to track and follow targets.

- `lifespan_system`: Manages the lifespan of entities and removes them when their lifespan expires.

- `collision_system`: Detects and handles collisions between entities.

- `asteroid_system`: Controls the spawning and behavior of asteroids.

- `input_system`: Processes user input for game-specific actions.

  

---

#### 4. Development Guidelines and Standards

- ECS Adherence: Strictly follow the ECS architecture for integrating new features or making modifications.

- Modularity: Ensure modularity in development for streamlined updates and addition of new features.

- Code Standard: Adhere to C++ coding standards to enhance code readability and maintainability.

---

#### 5. Testing Framework and Coverage

- #### 5.1. Testing Strategy Outline

- **Unit Testing**: Focus on testing individual components and systems.

- **Two Examples of Integration/Functional Testing**

1. Test the mobility_system:
```cpp
void test_mobility_system(registry& reg, double deltaTime) {
    // Create a test entity with sprite and movement components
    entity test_entity = 1;
    reg.sprites[test_entity] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.movements[test_entity] = { 1, 1, 200 };

    // Call the mobility_system update function
    mobility_system mobility_sys;
    mobility_sys.update(reg, deltaTime);

    // Check if the sprite's position is updated correctly
    assert(reg.sprites[test_entity].src.x == 100 + deltaTime * 200);
    assert(reg.sprites[test_entity].src.y == 100 + deltaTime * 200);
}
```

2. Test the collision_system:
```cpp
void test_collision_system(registry& reg) {
    // Create test entities with sprite and collision components
    entity test_entity1 = 1;
    entity test_entity2 = 2;
    reg.sprites[test_entity1] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.sprites[test_entity2] = { {120, 120, 50, 50}, nullptr, 0 };
    reg.collisions[test_entity1] = { 'a' };
    reg.collisions[test_entity2] = { 'b' };

    // Call the collision_system update function
    collision_system collision_sys;
    collision_sys.update(reg);

    // Check if the entities are destroyed correctly based on collision rules
    assert(reg.lifespans.find(test_entity1) != reg.lifespans.end());
    assert(reg.lifespans.find(test_entity2) != reg.lifespans.end());
}
```

- **Integration Testing**: Assess the interplay between systems like `sprite_system` and `mobility_system`.

- **End-User Functional Testing**:

- User Input: Test responsiveness to various key inputs and mouse interactions.

- Game Logic: Validate the adherence to game rules and mechanics.

- Rendering Verification: Ensure accurate display of all game components.

---

#### 6. Versioning Information

- **Game Version**: 1.0.0

- **SDL2 Version**: 2.0.12

- **C++ Version**: C++11 or higher

---

#### 7. Performance Metrics and Optimization

**Key Metrics**:

- FPS (Frames Per Second)

- Memory Usage

**Optimization Tips**:

- Optimize loop iterations.

- Minimize object creation during gameplay.

---

#### 8. Accessibility in Game Design

- Customizable control keys.

- Adjustable difficulty levels.

---

#### 9. Troubleshooting and FAQs

- **Q: What if the game doesn't start?**

- A: Check dependencies and ensure proper SDL2 setup.

- **Q: How do I resolve rendering issues?**

- A: Verify asset installation and graphics drivers.

---

#### 10. Best Practice Recommendations

- Continuous Testing: Regular testing alongside code evolution is recommended.

- Performance Profiling: Utilize profiling tools to identify performance bottlenecks.

- Code Review: Conduct regular code reviews to maintain code quality and identify potential issues.

---

#### 11. References and Further Reading

1. ECS: [An Entity-Component-System From Scratch](https://www.codingwiththomas.com/blog/an-entity-component-system-from-scratch)

2. SDL2 Documentation: [SDL2 Wiki](https://wiki.libsdl.org/)

---

#### 12. Feedback and Updates

Your feedback is crucial for the continual improvement of this project. Please submit suggestions or issues via the designated communication channels. Watch this section for future updates and enhancements.

---
