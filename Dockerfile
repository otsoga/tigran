FROM debian:bookworm
RUN apt-get update && apt-get install -y gcc make valgrind
WORKDIR /app/tigran
COPY . .
RUN make
CMD ["./tigran"]
