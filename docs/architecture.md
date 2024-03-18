# Architecture

## Overview

This is a basic bare-metal application using the Arduino platform on an ESP32.
Arduino provides a top-level with hooks for setup and loop functions.

### Platform Layer

The platform layer for this application primarily provides soft timer support and queued event callback mechanism.
I'd like to expand to have more capable event arguments, but as it stands, enables basic events to be added to a central queue and evaluated in the proper order.
I've used and seen similar methods in the past and one cool use is with respect to button handling events such as press, release and button hold events having a clean interface.

### Board Support Package (BSP) Layer

This is intended to abstract the hardware to the application and put items into context of the particular board (e.g. down button instead of digital input 42, etc.)
It is intended that the BSP knows about the hardware details and about the platform layer interface, but nothing else specific to the application.

### Application Layer

This is intended to focus on the real application and functionality. It should be possible to adapt the BSP to a different physical hardware and not need to totally re-write the application layer. (assuming moderate hardware changes only). This layer depends on the platform layer and BSP interfaces.
