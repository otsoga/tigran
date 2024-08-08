FROM debian:bookworm
RUN apt-get update && apt-get install -y gcc make

# Set the working directory in the container
WORKDIR /app/tigran

# Copy the current directory contents into the container
COPY . .

# Run make to build the application
RUN make

# Specify the command to run on container start
CMD ["./tigran"]
