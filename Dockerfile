ARG BASE="mumak:1.12.1-ubuntu20"
FROM ${BASE}

RUN apt install -y libhwloc-dev libjemalloc-dev uuid-dev libgomp1 libelf-dev \
    libconfig-dev libitm1 scons

WORKDIR /root
RUN git clone https://github.com/pmem/libpmemobj-cpp
RUN git clone https://github.com/pmem/valgrind.git

WORKDIR /root/valgrind
RUN ./autogen.sh && ./configure && make && make install

WORKDIR /root/libpmemobj-cpp
RUN mkdir build
WORKDIR /root/libpmemobj-cpp/build
RUN cmake .. && make -j$(nproc) && make install

RUN mkdir -p /root/Montage
WORKDIR /root/Montage
COPY ext /root/Montage/ext
COPY src /root/Montage/src
COPY Makefile /root/Montage/Makefile
RUN make
