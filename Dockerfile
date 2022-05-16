ARG BASE="mumak:3.8"
FROM ${BASE}

RUN apt install -y libhwloc-dev libjemalloc-dev uuid-dev libgomp1 libelf-dev \
    libconfig-dev libitm1 scons libpmemobj-cpp-dev

RUN mkdir -p /root/Montage
WORKDIR /root/Montage
COPY . /root/Montage/
RUN make

