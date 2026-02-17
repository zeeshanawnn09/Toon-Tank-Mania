# Toon Tank Mania

A classic arcade-style tank battle game built with Unreal Engine 5.6. Take control of a tank and battle against enemy towers in this action-packed game!

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.6-blue?logo=unrealengine)
![License](https://img.shields.io/badge/License-MIT-green)

## 🎮 Gameplay

Control your tank across the battlefield, aim your turret at enemy towers, and destroy them all to achieve victory. But be careful — the towers will fire back!

### Controls

- **W/S** - Move forward/backward
- **A/D** - Rotate tank
- **Mouse** - Aim turret
- **Left Click** - Fire projectile

## ✨ Features

- Player-controlled tank with smooth movement and rotation
- Turret aiming system with mouse control
- Enemy towers with AI targeting and firing mechanics
- Health system with visual health bars
- Projectile system with collision detection
- Particle effects using Niagara
- Camera shake effects on explosions
- Win/Lose game conditions
- Game countdown and UI prompts

## 🛠️ Technical Details

### Built With

- **Engine**: Unreal Engine 5.6
- **Language**: C++
- **Input System**: Enhanced Input
- **VFX**: Niagara Particle System
- **UI**: UMG (Unreal Motion Graphics)

### Project Structure

```
Source/BattleBlaster/
├── BasePawn.cpp/h          # Base class for Tank and Enemy Tower
├── Tank.cpp/h              # Player-controlled tank
├── EnemyTower.cpp/h        # AI-controlled enemy turrets
├── Projectile.cpp/h        # Projectile logic
├── GameManager.cpp/h       # Game mode and win/lose logic
├── HealthComponent.cpp/h   # Health management
├── HealthBarBehavior.cpp/h # Health bar UI component
└── PromptUIController.cpp/h# In-game UI prompts
```

## 🚀 Getting Started

### Prerequisites

- [Unreal Engine 5.6](https://www.unrealengine.com/)
- Visual Studio 2022 (Windows) or Xcode (macOS)

### Installation

1. Clone the repository
   ```bash
   git clone https://github.com/yourusername/Toon-Tank-Mania.git
   ```

2. Right-click on `BattleBlaster.uproject` and select **Generate Visual Studio project files**

3. Open `BattleBlaster.sln` in Visual Studio or open the `.uproject` file directly in Unreal Engine

4. Build and run the project

## 📸 Screenshots

*Coming soon*

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built as a learning project for Unreal Engine C++ development
- Asset packs: LP FPS Lite, Military Free
