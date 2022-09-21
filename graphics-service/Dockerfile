ARG FROM_DIRECTORY
FROM $FROM_DIRECTORY

RUN apt-get update
RUN apt-get install -y build-essential git
RUN apt-get install -y libgtest-dev libboost-test-dev vim
RUN apt-get install -y libasound2-dev mesa-common-dev libx11-dev
RUN apt-get install -y libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
RUN apt-get install -y cmake unzip
RUN apt-get install -y libcanberra-gtk-module libcanberra-gtk3-module
RUN apt-get install -y mesa-utils libjsoncpp-dev libcurl4-gnutls-dev
ARG CLIENT_OS
RUN if [ "$CLIENT_OS" = "Mac" ]; then \
	apt-get install -y gcc-9 && \
	apt-get upgrade libstdc++6 && \
	apt-get install -y libssl-dev; fi

WORKDIR /usr/src

RUN apt-get install wget
RUN wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz
RUN tar -zxvf cmake-3.20.0.tar.gz
RUN rm cmake-3.20.0.tar.gz
RUN cd cmake-3.20.0
WORKDIR /usr/src/cmake-3.20.0
RUN ./bootstrap
RUN make 
RUN make install -j

WORKDIR /usr/src

RUN wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
RUN unzip glfw-3.2.1.zip
RUN rm glfw-3.2.1.zip
RUN cd glfw-3.2.1
WORKDIR /usr/src/glfw-3.2.1
RUN cmake -DBUILD_SHARED_LIBS=ON
RUN make install -j

WORKDIR /usr/smart-mirror

CMD bash
