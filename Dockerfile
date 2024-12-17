# Start with an official base image that has minimal dependencies
FROM ubuntu:20.04

# Set non-interactive mode for apt-get (so it won't prompt)
ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update && apt-get install -y \
    build-essential \
    qemu-system-x86 \
    qemu-user-static \
    gdb \
    nasm \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

# Create a working directory for xv6
WORKDIR /usr/src
