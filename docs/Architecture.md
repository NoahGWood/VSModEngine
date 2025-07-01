# Architecture Overview (Early Stage)

This document provides an overview of how VSModEngine currently works at a high level. It's aimed at developers or contributors who want to understand the structure and extend the system.

---

## Core Design Goals

* Cross-platform (Linux, Windows, Mac eventually)
* Modular and extensible (via a plugin system)
* GUI-based using Dear ImGui + SDL2
* Fast to iterate on (CMake-based, no heavy dependencies)

---

## Main Components

### 1. **Core Application (`EditorApp`)**

* Owns the main SDL window and OpenGL context
* Initializes Dear ImGui and rendering backends
* Maintains the main app loop (`Init()`, `Run()`, `Shutdown()`)
* Delegates UI drawing to panels and menus
* Provides access to the event dispatcher, menu manager, etc.

### 2. **Logger (`Logger`)**

* Uses `spdlog`
* Two separate loggers: Core (engine logs) and Client (plugin logs)
* Macros like `CORE_INFO()`, `ERROR()` make usage simple

### 3. **Panels (`IPanel`)**

* Represent dockable UI sections in the editor
* Each implements `OnImGuiRender()` and `GetName()`
* Example: Project Browser Panel

### 4. **Menus (`IMenu`)**

* Represent top-level or nested menu items
* Support recursive submenus
* Example: File > Open Project

### 5. **Menu Manager**

* Registers and renders all top-level and nested menus
* Handles `OnImGuiRender()` for the menu bar

### 6. **Plugin System**

* Supports static plugin loading (dynamic WIP)
* Plugins implement lifecycle hooks: `OnLoad()`, `OnUnload()`
* Can register panels, menus, events, etc.
* CorePlugin is statically linked and provides base features

### 7. **Event System**

* Basic event categories and types (FileDrop, PluginLoaded, etc.)
* `Event` base class with runtime type info
* `EventDispatcher` dispatches events by type

---

## Lifecycle

```text
App start
├─ Init SDL + OpenGL + ImGui
├─ Load plugins (e.g. CorePlugin)
│  ├─ Register menus, panels
├─ Run main loop
│  ├─ Poll events
│  ├─ Dispatch to plugins and panels
│  ├─ Render ImGui
├─ Shutdown cleanly
```

---

## Directory Structure (WIP)

```
VSModEngine/
├── CMakeLists.txt
├── include/
│   └── Core/, UI/, Events/, Plugin/
├── src/
│   └── Core/, UI/, Events/, Plugin/
├── plugins/
│   └── CorePlugin/
│       ├── include/
│       └── src/
└── vendor/
    └── SDL2/, imgui/, spdlog/, etc.
```

---

## Planned Next Features

* Project 
* BlockType editor (visual editing of `blocktypes/*.json`)
* Shape/texture viewer
* JSON validation against VS schemas
* Dynamic plugin loading
* Mod packaging/export system

---

For now, this engine is fully functional with dockable panels, menus, logging, and plugin support. More mod-specific tools are being added soon.
