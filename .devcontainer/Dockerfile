FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

#install dev utils ,gstreamer and dependencies
RUN apt-get update && apt-get install -y -q libgnutls28-dev git


RUN apt-get install  libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev \
gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly -y


RUN apt-get install gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl \
gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio  pkg-config cmake python3 build-essential wget unzip -y


EXPOSE 35000-35100/udp

ENV DEBIAN_FRONTEND=""


CMD ["/bin/bash"]

