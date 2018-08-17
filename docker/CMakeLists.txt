set(_image_config "ubuntu_1804_cuda92_cudnn7")

add_custom_target(chroot
  COMMAND sudo docker build --network=host -t base/${_image_config}_base ${GADGETRON_SOURCE_DIR}/docker/base/${_image_config}
  COMMAND sudo docker build --network=host -t gadgetron_base/${_image_config} -f ${GADGETRON_SOURCE_DIR}/docker/incremental/${_image_config}/DockerfileBase ${GADGETRON_SOURCE_DIR}/docker/incremental/${_image_config}
  COMMAND sudo docker build --network=host -t incremental/${_image_config} -f ${GADGETRON_SOURCE_DIR}/docker/incremental/${_image_config}/Dockerfile ${GADGETRON_SOURCE_DIR}/docker/incremental/${_image_config}
  COMMAND sudo create_chroot_from_image incremental/${_image_config} 7168
  WORKING_DIRECTORY ${GADGETRON_SOURCE_DIR}/docker
  )

