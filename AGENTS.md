# AGENTS.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

BattleBlaster (Toon Tank Mania) is an Unreal Engine 5.6 tank battle game. The player controls a tank to destroy enemy towers across multiple levels.

## Build & Development Commands

```powershell
# Generate project files (run from project root)
"C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="E:\Batle Blaster\Toon-Tank-Mania\BattleBlaster.uproject" -game -engine

# Build the project (Development Editor)
"C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" BattleBlasterEditor Win64 Development "E:\Batle Blaster\Toon-Tank-Mania\BattleBlaster.uproject" -waitmutex

# Open in Unreal Editor
"C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\Win64\UnrealEditor.exe" "E:\Batle Blaster\Toon-Tank-Mania\BattleBlaster.uproject"
```

Visual Studio solution: `BattleBlaster.sln`

## Code Architecture

### Pawn Hierarchy
- **`ABasePawn`** - Base class for all game pawns. Contains turret rotation, firing logic, destruction effects (Niagara particles, camera shake, sound)
  - **`ATank`** - Player-controlled tank. Uses Enhanced Input system for movement/rotation/firing. Has spring arm camera setup and health bar widget
  - **`AEnemyTower`** - Stationary enemy. Auto-targets and fires at player within `FireRange` at `FireRate` intervals

### Core Components
- **`UHealthComponent`** - ActorComponent attached to pawns. Handles damage via `OnTakeAnyDamage` delegate. Broadcasts `OnHealthChanged` delegate for UI updates. Notifies `GameManager` when actor dies

### Game Flow
- **`AGameManager`** (GameModeBase) - Tracks enemy count, handles win/lose conditions, manages game start countdown via `PromptUIController`
- **`UToonTankGameInstance`** - Persists across levels. Manages level progression (`LoadNextLevel`, `RestartCurrentLevel`, `RestartGame`) and background music

### UI Widgets (UMG)
- **`UPromptUIController`** - Displays game messages (countdown, win/lose). Binds to `Message_TB` TextBlock
- **`UHealthBarBehavior`** - Progress bar bound to `UHealthComponent::OnHealthChanged` delegate

### Combat
- **`AProjectile`** - Spawned by `BasePawn::FireBehavior()`. Uses `UProjectileMovementComponent`. Applies damage via `UGameplayStatics::ApplyDamage` on hit

## Module Dependencies

Defined in `BattleBlaster.Build.cs`:
- Core, CoreUObject, Engine, InputCore
- EnhancedInput (for input handling)
- UMG (for UI widgets)
- Niagara (for particle effects)

## Key Patterns

- UI widgets use `meta = (BindWidget)` to bind C++ properties to UMG widget names
- Health system uses multicast delegates (`FOnHealthChanged`) for loose coupling between components and UI
- Levels are loaded by index via `UToonTankGameInstance::ChangeLevel()`
