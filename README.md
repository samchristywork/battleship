![Banner](https://s-christy.com/sbs/status-banner.svg?icon=device/water&hue=200&title=Battleship&description=A%20terminal%20based%20battleship%20game%20written%20in%20C)

## Overview

<p align="center">
  <img src="./assets/screenshot.png" width=500 />
</p>

This is a simple console-based Battleship game written in C, where you can play
against different levels of AI or a human opponent.

## Features

- Play against different AI opponents with varying difficulty.
- The human player can manually place their ships on the board.
- Collision checks to make sure there are no invalid board placements.
- Visualization of player and opponents boards with a score readout.
- Fully interactive gameplay.
- Gracefully handles SIGINT.
- ANSI color support.

## Setup

`make build` to build the program, and `make run` to run it.

## Dependencies

```
gcc
make
```

## AI Levels

- Easy: AI makes random guesses.
- Medium: AI makes semi-intelligent guesses based on prior hits.
- Hard: AI has a small chance to cheat by hitting directly on ships.

## License

This work is licensed under the GNU General Public License version 3 (GPLv3).

[<img src="https://s-christy.com/status-banner-service/GPLv3_Logo.svg" width="150" />](https://www.gnu.org/licenses/gpl-3.0.en.html)
