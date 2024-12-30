CONTAINER=$(docker ps --format '{{.Names}}' | head -n 1)

if [ -z "$CONTAINER" ]; then
    docker run -it -v .:/usr/src/naxos/ jpbonch/os
    exit 1
fi

echo "Attaching to container: $CONTAINER"
docker exec -it "$CONTAINER" bash