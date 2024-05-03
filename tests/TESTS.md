```cpp
TEST_CASE("mobility_system_update") {
    // Create a test registry
    registry reg;

    // Create a test entity with sprite and movement components
    entity test_entity = 1;
    reg.sprites[test_entity] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.movements[test_entity] = { 1, 1, 200 };

    // Call the mobility_system update function
    mobility_system mobility_sys;
    mobility_sys.update(reg, 1.0); // Delta time = 1 second

    // Check if the sprite's position is updated correctly
    REQUIRE(reg.sprites[test_entity].src.x == 300);
    REQUIRE(reg.sprites[test_entity].src.y == 300);
}

TEST_CASE("velocity_system_update") {
    // Create a test registry
    registry reg;

    // Create a test entity with sprite, velocity, and controller components
    entity test_entity = 1;
    reg.sprites[test_entity] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.velocities[test_entity] = { 0, 0, 0.9f, 200 };
    reg.controllers[test_entity] = { 1, 0 }; // Moving right

    // Call the velocity_system update function
    velocity_system velocity_sys;
    velocity_sys.update(reg, 1.0); // Delta time = 1 second

    // Check if the sprite's position is updated correctly
    REQUIRE(reg.sprites[test_entity].src.x > 200);
    REQUIRE(reg.sprites[test_entity].src.y == 100);
}

TEST_CASE("rotation_system_update") {
    // Create a test registry
    registry reg;

    // Create a test entity with sprite and rotation components
    entity test_entity = 1;
    reg.sprites[test_entity] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.rotations[test_entity] = { 90 }; // 90 degrees per second

    // Call the rotation_system update function
    rotation_system rotation_sys;
    rotation_sys.update(reg, 1.0); // Delta time = 1 second

    // Check if the sprite's angle is updated correctly
    REQUIRE(reg.sprites[test_entity].angle == 90);
}

TEST_CASE("lifespan_system_update") {
    // Create a test registry
    registry reg;

    // Create a test entity with sprite and lifespan components
    entity test_entity = 1;
    reg.sprites[test_entity] = { {100, 100, 50, 50}, nullptr, 0 };
    reg.lifespans[test_entity] = { 2.0 }; // 2 seconds lifespan

    // Call the lifespan_system update function
    lifespan_system lifespan_sys;
    lifespan_sys.update(reg, 1.0); // Delta time = 1 second

    // Check if the lifespan is decremented correctly
    REQUIRE(reg.lifespans[test_entity].lifespan == 1.0);

    // Call the update function again to expire the lifespan
    lifespan_sys.update(reg, 1.0); // Delta time = 1 second

    // Check if the entity is removed
    REQUIRE(reg.sprites.find(test_entity) == reg.sprites.end());
    REQUIRE(reg.lifespans.find(test_entity) == reg.lifespans.end());
}
```