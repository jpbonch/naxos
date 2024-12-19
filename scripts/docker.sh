CONTAINER=$(docker ps --format '{{.Names}}' | head -n 1)

if [ -z "$CONTAINER" ]; then
    echo "No running containers found."
    exit 1
fi

echo "Attaching to container: $CONTAINER"
docker exec -it "$CONTAINER" bash