# Trasnochando Con Mirna Lemort

A two-player cooperative first-person stealth/puzzle game built in **Unreal Engine 5.5** for Windows.

This was my college final project. I wrote all of the programming myself — the goal was to take on the challenge of building a real multiplayer game from scratch: server-authoritative replication, RPCs, AI perception, and Steam session hosting, on top of a co-op gameplay loop where two players actually need each other to make progress.

## The game

Two influencers are invited to film an episode of *Trasnochando con Mirna Lemort*, a late-night TV show hosted by the eccentric Mirna Lemort. When they arrive at the Lemort mansion, things go wrong: Mirna turns out to be a vampiric diva who feeds on her guests' youth, and the players have to cooperate to solve four puzzles and escape before she catches them.

- **Stealth + puzzles** — Mirna patrols the mansion. She has a 50° vision cone and hears noise on a distance-based curve, so crouching, running, and where you make sound all matter.
- **Real cooperation** — every puzzle requires both players. The final puzzle consumes the rewards from the previous three, so the game can't be soloed.
- **Listen-server multiplayer over Steam** — one player hosts, the other joins via the Steam session.

## Tech

- **Engine**: Unreal Engine 5.5
- **Language**: C++ for gameplay systems, Blueprints for content/configuration on top
- **Networking**: server-authoritative listen server with `Server`/`NetMulticast` RPCs and replicated state on the GameState
- **Online**: `OnlineSubsystemSteam` (+ vendored AdvancedSessions / AdvancedSteamSessions plugins) for session hosting and join flow
- **AI**: Behavior Tree + Blackboard with custom C++ tasks/services for patrol, sight checks, and noise-driven investigation

## Documentation

The full game design document (in Spanish, Obsidian-style) lives in [`Documentation/GameDesignDocument/`](Documentation/GameDesignDocument/) and covers the puzzles, Mirna's AI, the noise system, controls, UI, and win/lose conditions in detail.

## Credits

Programming: me (sole programmer). Art, design, and additional contributions by the rest of the college team.
