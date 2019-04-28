# A Vim Story
_A ncurses based game for learning Vim_

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/053e7aa12d05484fbe77a521bb2d4f34)](https://www.codacy.com/app/UtkarshMe/A-Vim-Story?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=UtkarshMe/A-Vim-Story&amp;utm_campaign=Badge_Grade)



### Overview

There are a lot of problems faced by beginners to [Vim](http://www.vim.org/)
(like getting used to not using arrow keys for example). Although there are a
lot of resources for learning Vim, they can get tedious and time consuming.  

The project aims to make a game played by using the shortcuts and key mappings
in Vim to ease into the famous learning curve of Vim. The idea is to make a
retro console game (like bomber-man and the likes) which is controlled solely
by Vim key mappings and shortcuts.  

Inspired by [Vim Adventures](https://vim-adventures.com/) and open sourced.



### Compiling
Assuming you have _libncurses_, _CMake_ and _Make_ installed.

    mkdir build && cd build

    cmake ..

    make
    make install        # to install (might want to use 'sudo')

    a-vim-story         # to run


If you want to install in another directory

    cmake -DCMAKE_INSTALL_PREFIX=/usr ..  # to install in /usr

Or if you want to test it in `build/` itself

    cmake -DCMAKE_INSTALL_PREFIX=. ..
    make && make install
    ./bin/a-vim-story

**You can even use the Dockerfile now.**


### Documentation
For documentation, a configuration file for _Doxygen_ is provided. Assuming you
have _doxygen_ installed, issue these commands:

    doxygen doxygen.conf



### Author
[Utkarsh Maheshwari](https://github.com/UtkarshMe)



### License
[GPL version 3](https://github.com/UtkarshMe/a-vim-story/blob/master/LICENSE)
