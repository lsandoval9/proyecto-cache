FROM ubuntu:14.04

WORKDIR /app

# Install build tools
RUN apt-get update && \
    apt-get install -y g++ nano

# Copy source code and compile
COPY . .

RUN g++ -std=c++11 main.cpp -o RUN.out

# Set the command to run
CMD ["python3", "cache_time.py"]