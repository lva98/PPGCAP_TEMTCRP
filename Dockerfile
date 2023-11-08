FROM mcr.microsoft.com/devcontainers/cpp


# Install OpenCV dependencies
RUN apt-get update && \
    apt-get install -y bison && \
    apt-get install -y python3-distutils && \
    apt-get install -y libdbus-1-dev && \
    apt-get install -y libx11-dev libxft-dev libxext-dev && \
    apt-get install -y libxrandr-dev && \
    apt-get install -y libxi-dev && \
    apt-get install -y autoconf && \
    apt-get install -y autoconf-archive && \
    apt-get install -y libxtst-dev
# Instalar outras dependências necessárias, se houver

# Instalar OpenCV usando vcpkg
RUN vcpkg install openvino
RUN vcpkg install opencv

# Configurar variáveis de ambiente, compilação, etc.

CMD [ "bash" ]
