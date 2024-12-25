docker pull ubuntu
docker build -t "container" .
docker run -it -v $PWD:/tmp -w /tmp container

# windows
# docker run -it -v ${PWD}:/tmp -w /tmp container