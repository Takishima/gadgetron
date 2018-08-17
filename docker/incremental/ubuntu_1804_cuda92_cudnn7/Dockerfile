FROM gadgetron_base/ubuntu_1804_cuda92_cudnn7

ARG GADGETRON_URL=https://github.com/Takishima/gadgetron
ARG GADGETRON_BRANCH=basel

#Fix compiler error with CUDA for now
RUN sed -i "s;#error -- unsupported GNU version! gcc versions later than 4.9 are not supported!;//#error -- unsupported GNU version! gcc versions later than 4.9 are not supported!;g" /usr/local/cuda/include/host_config.h

#GADGETRON
RUN cd /opt/code && \
    git clone ${GADGETRON_URL} --branch ${GADGETRON_BRANCH} --single-branch && \
    cd gadgetron && \
    mkdir build && \
    cd build && \
    CC=gcc-6 CXX=g++-6 cmake -DCUDA_NVCC_FLAGS="-ccbin gcc-6" -DBUILD_WITH_PYTHON3=ON -DBART_USE_LUA=ON ../ && \
    make -j $(nproc) && \
    make install && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.gadgetron.sha1 --value `git rev-parse HEAD` && \
    cp ${GADGETRON_HOME}/share/gadgetron/config/gadgetron.xml.example ${GADGETRON_HOME}/share/gadgetron/config/gadgetron.xml && \
    cp /opt/code/gadgetron/docker/start_supervisor /opt/ && \
    cp /opt/code/gadgetron/docker/supervisord.conf /opt/

# For mounting on the HOST
RUN mkdir ${GADGETRON_HOME}/lib_extra
RUN mkdir /python
RUN mkdir /gadgetron_log

#HASH for ISMRMRD
RUN cd /opt/code/ismrmrd && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.ismrmrd.sha1 --value `git rev-parse HEAD` 

# HASH for ISMRMRD PYTHON API
RUN cd /opt/code/ismrmrd-python && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.ismrmrdpython.sha1 --value `git rev-parse HEAD` 

#HASH for ISMRMRD PYTHON TOOLS
RUN cd /opt/code/ismrmrd-python-tools && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.ismrmrdpythontools.sha1 --value `git rev-parse HEAD` 

# HASH for SIEMENS_TO_ISMRMRD
RUN cd /opt/code/siemens_to_ismrmrd && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.siemens_to_ismrmrd.sha1 --value `git rev-parse HEAD` 

# HASH for PHILIPS_TO_ISMRMRD
RUN cd /opt/code/philips_to_ismrmrd && \
    /opt/code/gadgetron/docker/manifest --key .io.gadgetron.philips_to_ismrmrd.sha1 --value `git rev-parse HEAD` 

# Clean up packages.
RUN  apt-get clean && \
   rm -rf /var/lib/apt/lists/*

CMD ["/opt/start_supervisor"]
