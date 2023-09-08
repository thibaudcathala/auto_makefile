# auto_makefile

<p align="justify">**auto_makefile** is a C++ program that automates the generation of Makefiles Rules for your projects. It analyzes your project directory structure and completes your Makefile rules to compile all relevant source files.</p>

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

`⭐ Don't forget to put a star if you like the project!`

## Features

<details close>
  <summary>Automatic Rule Generation</summary>
  <p align="justify">Auto-generates Makefile rules for compiling source files, saving you time and effort in manual Makefile creation.</p>
</details>
<details close>
  <summary>Customizable Rules</summary>
  <p align="justify">Allows you to define root rules, file extensions, paths, and subfolder rules, making it easy to adapt the Makefile generation to your project's structure and requirements.</p>
</details>
<details close>
  <summary>Support for Multiple Root Rules</summary>
  <p align="justify">Create separate compilation rules for different parts or components of your project by specifying multiple root rules.</p>
</details>
<details close>
  <summary>Effortless Subfolder Rules</summary>
  <p align="justify">Simplifies the generation of rules for subdirectories within root directories, enhancing project organization.</p>
</details>
<details close>
  <summary>Custom Tab Indentation</summary>
  <p align="justify">Lets you customize the number of tabs used for indentation in the generated Makefile, ensuring consistent formatting.</p>
</details>
<details close>
  <summary>Tag-Based Rule Completion</summary>
  <p align="justify">Uses tags (#//) as markers to indicate where auto-completion should take place in the Makefile, giving you control over rule placement.</p>
</details>
<details close>
  <summary>Command-Line Interface</summary>
  <p align="justify">Provides a command-line interface for easy execution and integration into your project's build process.</p>
</details>

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

In the Makefile, you must define specific variables and utilize tags that will serve as markers for the auto_makefile program to generate the rule content:
```bash
# root: [ROOT_RULE_NAME], ...;
# path: [PATH_TO_FOLDER], ...;
# file_ext: [FILE_EXT, ...], ...;
# subfolder_rule_name: [SUBFOLDER_RULE_NAME], ...;
# nb_tab: [NB_TAB], ...;

#//
ROOT_RULE_NAME  =
#//
```
### Tag:

- To delineate the section where auto_makefile needs to auto-complete the rules, use tags formatted as: `#//`. These tags serve as markers to indicate the boundaries of the area that require automatic rule generation.

### Here's an explanation of each of these variables:

1. **`root: [ROOT_RULE_NAME], ...;`**

- This variable specifies the root rule names to complete. You can list multiple root rule names, separated by commas.

2. **`path: [PATH_TO_FOLDER], ...;`**

- Here, you provide the paths to the folders where your project's source files are located. Each path corresponds to one of the root rules defined earlier. You can specify multiple paths separated by commas.

3. **`file_ext: [FILE_EXT, ...], ...;`**

- This variable specifies the file extensions of the source files you want to include in each root rule. Each entry in this list corresponds to a root rule defined earlier. You can specify multiple file extensions separated by commas for each root rule.

4. **`subfolder_rule_name: [SUBFOLDER_RULE_NAME], ...;`**

- For each root rule, you can specify a subfolder rule name. This name will be used to generate rules for subdirectories within each root rule's directory. Like the other variables, you can specify multiple subfolder rule names separated by commas, corresponding to the root rules.

- **{FOLD}** and **{SUBFOLD}** are variable that you can use in `[SUBFOLDER_RULE_NAME]` to generate different subrule name.

5. **`nb_tab: [NB_TAB], ...;`**

- This variable specifies the number of tabs to use for each rule's indentation. Each entry corresponds to a root rule.

## Contributing
Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name`.
3. Make your changes and commit them: `git commit -m 'Add your feature'`.
4. Push to the branch: `git push origin feature/your-feature-name`.
5. Create a pull request on GitHub.
