# auto_makefile

**auto_makefile** is a C++ program that automates the generation of Makefiles Rules for your projects. It analyzes your project directory structure and completes your Makefile rules to compile all relevant source files.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Features

- Automatically detects C++ source files in your project directory.
- Generates Makefile rules to compile all source files into executable binaries.
- Supports custom compiler options and build configurations.

## Installation

### Prerequisites

- C++ compiler (e.g., g++)

### Building from Source

1. Clone this repository to your local machine:
```bash
git clone https://github.com/your-username/auto_makefile.git
```

2. Navigate to the project directory:
```bash
cd auto_makefile
```
3. Build the program using make:
```bash
make
```

4. Move the program to /usr/local/bin to execute it from anywhere:
```bash
sudo mv auto_makefile /usr/local/bin/
```

5. (optional) You can delete the repository:
```bash
cd .. ;
rm -R auto_makefile/
```
## Usage
```bash
auto_makefile [Makefile] ...
```
**auto_makefile** take as argument Makefile where you want the rule to be auto-completed.

In the Makefile you will have to add line 

## Contributing
Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name`.
3. Make your changes and commit them: `git commit -m 'Add your feature'`.
4. Push to the branch: `git push origin feature/your-feature-name`.
5. Create a pull request on GitHub.

`⭐ Don't forget to put a star if you like the project!`
