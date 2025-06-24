FROM gcc:13.3.0

RUN apt-get update; \
    apt-get install -y --no-install-recommends \
    python3-dev \
    python3-pip \
    python3-setuptools \
    libudev-dev \
    cmake

RUN pip3 install conan --break-system-packages

RUN mkdir -p /root/.conan2/profiles 
COPY profiles/default /root/.conan2/profiles/default

# RUN mkdir -p /usr/project/build
# WORKDIR /usr/project
# COPY conanfile.txt ./

# WORKDIR /usr/project/build
# RUN conan install ..  -s="build_type=Release"

# COPY . /usr/project
# RUN cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
# RUN cmake --build .

WORKDIR /usr/project
COPY entrypoint.sh ./entrypoint.sh
RUN chmod +x entrypoint.sh

WORKDIR /usr/project
EXPOSE 8080 8181 5000 3000
# ENTRYPOINT ["./entrypoint.sh"]
CMD ["bash"]