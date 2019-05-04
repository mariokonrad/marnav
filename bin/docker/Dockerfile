ARG gcc_version=9.1.0
FROM gcc:${gcc_version}
MAINTAINER Mario Konrad <mario.konrad@gmx.net>

ARG cmake_version=3.13.4
ARG boost_version=1.69.0

USER root
RUN apt-get update \
 && apt-get install -y apt-utils curl git-core libqt5*-dev \
 && rm -fr /var/lib/apt/lists/*
RUN mkdir -p /opt

# install cmake
COPY install-cmake.sh /tmp/
RUN /tmp/install-cmake.sh "${cmake_version}"
ENV PATH /opt/local/cmake/bin:$PATH

# install boost
COPY install-boost.sh /tmp/
RUN /tmp/install-boost.sh "${boost_version}"
ENV BOOST_ROOT=/opt/local

# add user
RUN useradd --groups users -M --uid 1000 user
USER user
