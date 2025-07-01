# VSModEngine
A cross-platform, open-source modding toolkit for [Vintage Story](https://www.vintagestory.at/), inspired by Bethesda’s Creation Kit and Minecraft’s MCreator.

## 🧱 What It Is

VSModEngine is a standalone mod editor for Vintage Story designed to make modding simpler, faster, and more accessible; even for non-programmers.

Whether you're tweaking blocks, editing shapes, or building full content packs, this tool aims to give you a visual workflow and powerful plugin support.

> “I wanted to make a mod for Vintage Story and was a bit surprised at how complex it is to get started, even with prior game dev experience. I really like the game, so I’m building a proper ‘Creation Kit’-style modding engine for it.”

## 🚀 Features (WIP)

- 🔌 Plugin system - mod the mod editor itself
- 🪟 Dockable UI panels (ImGui-based)
- 📁 Project-based mod structure
- 🧱 BlockType editor (coming soon)
- 🔍 Shape viewer
- 🧰 Mod config + export tools
- ✅ Built-in validation and error checking

## 📦 Roadmap

- [x] Core app framework (windowing, logging, plugin system)
- [x] Menu + panel management
- [x] Static plugin loading
- [ ] Block editor UI
- [ ] Shape/texture viewer
- [ ] Worldgen patch editor
- [ ] Export to full mod folder
- [ ] Optional VS API backend for validation

## ⚙️ Tech Stack

- C++17
- SDL2
- OpenGL + Dear ImGui
- ImGuizmo, ImNodes, nlohmann/json, spdlog

## 🔧 Build Instructions

- Clone the repo
- Use CMake (`cmake . && make` or your preferred generator)
- Requires SDL2, OpenGL, and standard development libraries

## 📜 License

This project is licensed under the **GNU GPLv3**. Contributions welcome, but all derivatives must remain open.

## 🙌 Contributing

Suggestions and PRs welcome - especially from the Vintage Story community. Join the fun and help shape the future of modding!

---