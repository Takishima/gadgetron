#! /bin/bash

base_dir=$(pwd)

cd ${base_dir}/base/ubuntu_1804_cuda92_cudnn7
sudo docker build --network=host -t base/ubuntu_1804_cuda92_cudnn7_base .

cd ${base_dir}/incremental/ubuntu_1804_cuda92_cudnn7
sudo docker build --network=host -t gadgetron_base/ubuntu_1804_cuda92_cudnn7 -f DockerfileBase .
sudo docker build --no-cache --network=host -t incremental/ubuntu_1804_cuda92_cudnn7 -f Dockerfile .

cd ${base_dir}
sudo ${base_dir}/create_chroot_from_image incremental/ubuntu_1804_cuda92_cudnn7 7168
