add_executable(example_usage
    example_usage.cpp
)
add_executable(tiny_kitchen_system
    tiny_kitchen_system.cpp
)

target_link_libraries(example_usage PRIVATE KitchenRoutingLibrary)
target_link_libraries(tiny_kitchen_system PRIVATE KitchenRoutingLibrary)