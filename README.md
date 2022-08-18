# AttOS
A tiny real time scheduler for AVR micro controllers.

# Setup
1. Install [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
2. Open the top level directory in PlatformIO

# Usage

## Concepts
Task

AttOS reserves the following resources for its own use:
* TIMER 0: Used by the AttOS' scheduler to schedule tasks
