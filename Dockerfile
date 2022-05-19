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

# generate all relevant configs
ARG RIDEABLES="8 9 10 11 12 16 17 18 19 23"
ARG MODES="8"
RUN mkdir -p /configs
COPY template.cfg /root/Montage/template.cfg
RUN for tool in bfi dofta; do \
    for persist in DirWB Buffered; do \
    for rideable in $RIDEABLES; do \
    for mode in $MODES; do \
        sed "s/MUMAKTOOL/$tool/;s/RIDEABLE/$rideable/;s/MODE/$mode/;s/PERSIST/$persist/" \
            template.cfg > /configs/$rideable-$mode-$persist-$tool.cfg; \
    done; \
    done; \
    done; \
    done

