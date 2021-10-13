# vlcRemote
## Overview
This project aims to solve one of the most pressing issues facing humanity - having to get up from the couch while watching TV. The device plugs into your laptop and allows for remote control of apps such as Netflix,YouTube and VLC. To do that I used an IR receiver, old TV remotes and keyboard functionality of the Arduino Pro Micro. So far I implemented suport for remotes that use NEC, Samsung and Sony protocols. 
## Necessary parts
* Arduino Pro Micro (will not work with Uno, Mega or Nano :( )
* IR receiver (I used vs1838b but any others should work)
* An IR remote running any of the supported protocols
* (Optional) A universal board to solder everything onto
## Installation
The installation is done via Platformio if you don't have it installed as an Atom or VS Code plugin install the [CLI version](https://platformio.org/install/cli) and run `platformio run --target upload`.
