               __      ___              _____ _                   
        /\     \ \    / (_)            / ____| |                  
       /  \     \ \  / / _ _ __ ___   | (___ | |_ ___  _ __ _   _ 
      / /\ \     \ \/ / | | '_ ` _ \   \___ \| __/ _ \| '__| | | |
     / ____ \     \  /  | | | | | | |  ____) | || (_) | |  | |_| |
    /_/    \_\     \/   |_|_| |_| |_| |_____/ \__\___/|_|   \__, |
                                                             __/ |
                                                            |___/

#### A _ncurses_ based game for learning Vim

## Overview
There are a lot of problems faced by beginners to [Vim](http://www.vim.org/)
(like getting used to not using arrow keys for example). Although there are a
lot of resources for learning Vim, they can get tedious and time consuming.  

The project aims to make a game played by using the shortcuts and key mappings
in Vim to ease into the famous learning curve of Vim. The idea is to make a
retro console game (like bomber-man and the likes) which is controlled solely
by Vim key mappings and shortcuts.  

Inspired by [Vim Adventures](https://vim-adventures.com/) and open sourced.

## Compiling
Assuming you have _libncurses_, _CMake_ and _Make_ installed,
```bash
mkdir build && cd build
cmake ..
make
```

## Documentation
For documentation, a configuration file for _Doxygen_ is provided. Assuming you
 have _doxygen_ installed, issue these commands:
```bash
doxygen doxygen.conf
```

## Author
[Utkarsh Maheshwari](https://github.com/UtkarshMe)

## License
[GPL version 3](https://github.com/UtkarshMe/a-vim-story/blob/master/LICENSE)
