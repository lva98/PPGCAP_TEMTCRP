FROM debian:bookworm-slim

RUN apt -y update
RUN apt -y install \
  git \
  wget \
  clang \
  llvm \
  cmake \
  curl \
  zip \
  unzip \
  tar \
  libopencv-dev

RUN git clone https://github.com/Microsoft/vcpkg.git
WORKDIR /vcpkg
RUN ./bootstrap-vcpkg.sh
ENV VCPKG_ROOT /vcpkg

CMD [ "bash" ]
