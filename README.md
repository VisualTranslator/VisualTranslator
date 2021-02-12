<p align="center">
  <img alt="Logo" width="350px" src="https://raw.githubusercontent.com/VisualTranslator/visualtranslator.github.io/master/img/logo.png"/>
</p>

> Tool for recognition and translation text.

## Table of Contents

- [Installation](#installation)
- [Features](#features)
- [Usage](#usage)
- [Build](#build)
- [FAQ](#faq)
- [Team](#team)
- [Donations](#donations)
- [License](#license)

## Installation
  The installation process is absolutely similar for Windows, macOS, and Linux.
  
  **Download installer and follow the instructions inside.**
 
  > If you want to download the specific build, visit [Github Releases page](https://github.com/VisualTranslator/VisualTranslator/releases)

  [TODO] add screenshots of tray icons in different OS
  
## Features
* Select & Translate in any software.
* Screen Recognition AI.
* More than 125 languages.
* Fast and Cross-platform.
* Written in C++ and avaliable for Windows, macOS and Linux.
* Free.

## Usage
* Press <kbd>CTRL</kbd> + <kbd>ALT</kbd> + <kbd>Q</kbd> on Windows or <kbd>CMD</kbd> + <kbd>ALT</kbd> + <kbd>Q</kbd> on macOS (or activate VisualTranslator from tray icon).
* Select screen area and release mouse button.
* Voila! Translation will appear near the tray icon.

> To change standard application key combination, press on the tray icon and choose Settings.

## Build
Project is compiled successfully with `MSVC2017 x64` on Windows and `Apple Clang x86_64` on macOS.

1. Install [qpm](qpm.io) package manager.
2. Run `qpm install` in src folder to install all dependencies.
3. Open `VisualTranslator.pro` in QtCreator.
3. Run `Build`.

## FAQ
### How it recognizes selected text?
Under the hood VisualTranslator uses [tesseract](https://github.com/tesseract-ocr/tesseract) to recognize text on the selected area.

### How it uses Neural Networks?
The latest version of Tesseract OCR engine is based on LSTM neural networks. [More info here.](https://github.com/tesseract-ocr/tesseract/wiki/4.0-with-LSTM)

### What languages are supported?
List of all supported languages can be found [here](https://github.com/VisualTranslator/VisualTranslator/blob/master/supported_languages.md).

## Team
* Andriy Semenets (https://github.com/semanser)
* Oleksandr Kushnir (https://github.com/kushnir95)

## Donations
## License
This software use [GPL v3](https://github.com/VisualTranslator/VisualTranslator/blob/master/LICENSE) license.

