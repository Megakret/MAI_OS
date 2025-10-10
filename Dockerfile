# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:14

# These commands copy your files into the specified directory in the image
# and set that as the working location
RUN apt-get update 
RUN apt-get install -y --no-upgrade cmake clang-tidy sudo strace python3 pip python3-matplotlib
RUN useradd -m -s /bin/bash developer && \
    echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
COPY . ./workspace
WORKDIR /workspace
RUN chown -R developer:developer /workspace 
USER developer
CMD ["/bin/bash"]
# This command runs your application, comment out this line to compile only
LABEL Name=mai_os Version=0.0.1
