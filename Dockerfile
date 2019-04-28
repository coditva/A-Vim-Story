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
    && apt-get install --no-install-recommends -y \
    gcc cmake make libncurses5-dev \
    && rm /var/lib/apt/lists/*

# Build it
WORKDIR /a-vim-story/build
RUN cmake ..
RUN make
RUN make install

# Set the binary as the start point
ENTRYPOINT ["/usr/local/bin/a-vim-story"]
