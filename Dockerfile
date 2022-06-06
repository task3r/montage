ARG BASE="mumak:1.8"
FROM ${BASE}

RUN apt install -y libhwloc-dev libjemalloc-dev uuid-dev libgomp1 libelf-dev \
    libconfig-dev libitm1 scons libpmemobj-cpp-dev

RUN mkdir -p /root/Montage
WORKDIR /root/Montage
COPY ext /root/Montage/ext
COPY src /root/Montage/src
COPY Makefile /root/Montage/Makefile
RUN make
