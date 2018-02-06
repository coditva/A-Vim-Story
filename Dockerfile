# Get image
FROM ubuntu:xenial

# Copy only the required files
COPY ./src /a-vim-story/src
COPY ./include /a-vim-story/include
COPY ./maps /a-vim-story/maps
COPY ./CMakeLists.txt /a-vim-story/CMakeLists.txt
COPY ./config.h.in /a-vim-story/config.h.in

# Update and install the dependencies
RUN apt-get update \
    && apt-get install -y gcc cmake make libncurses5-dev

# Build it
RUN mkdir /a-vim-story/build \
    && cd /a-vim-story/build \
    && cmake .. \
    && make \
    && make install

# Set the binary as the start point
ENTRYPOINT ["/usr/local/bin/a-vim-story"]
