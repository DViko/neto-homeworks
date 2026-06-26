# 📓 Homework_05_01: Docker

> ***A short reference on installing Docker, working with containers, and compiling a simple C++ application inside Ubuntu 16.04.***

🔹 Basic scheme:

```text
    Host OS (Linux Mint/Ubuntu)
            │
            ▼
        Docker Engine
            │
            ▼ 
    ┌───────────────────┐
    │ Ubuntu 16.04      │
    │ GCC 5.4           │
    │ My application    │
    └───────────────────┘
```


## 📝 Basic Concepts

Docker is a platform for developing, testing, and running applications inside isolated environments called containers. Unlike a virtual machine, a container does not run its own operating system kernel. Instead, it shares the host kernel while maintaining an isolated filesystem, processes, and networking.




🔹 An  **Image** is a read-only template used to create containers.

🔸 Example:

  - `docker pull ubuntu:16.04`

🔹 A container is a running instance of an image.

🔸 Example:

  - `docker run -it ubuntu:16.04 bash`

🔹 Docker Engine.

  - The docker engine is the service responsible for downloading images, creating containers, and managing their lifecycle

## 📝 Installing Docker (Linux Mint/Ubuntu)

🔹 Update package index:

  - `sudo apt update`

🔹 Install Docker:

  - `sudo apt install docker.io`

🔹 Enable Docker service:

  - `sudo systemctl enable docker`
  - `sudo systemctl start docker`

🔹 Check service status:

  - `systemctl status docker`

🔹 (Optional) Allow running Docker without📝 Notes `sudo` :

  - `sudo usermod -aG docker $USER`

Log out and log back in after adding yourself to the docker group.

## 📝 Verify Installation

🔹 Docker version:

  - `docker --version`

🔹 Run the test container:

  - `docker run hello-world`

If everything is working correctly, Docker downloads the hello-world image and prints a welcome message.


## 📝 Downloading and launching an Ubuntu 16.04 container

🔹 Download the image:

  - `docker pull ubuntu:16.04`

🔹 List downloaded images:

  - `docker images`
  - or `docker image ls`

🔹 Start an interactive container:

  - `docker run -it ubuntu:16.04 bash`

🔹Options:

  - `-i` → keep STDIN open
  - `-t` → allocate a pseudo-terminal
  - `bash` → start the Bash shell

🔹 Inside the container the prompt looks similar to :

  - `root@2787e3d306fa:/#`


## 📝 Install GCC

🔹 Update package list:

  - `apt update`

🔹 Install the compiler:

  - `apt install -y g++`

🔹 Verify installation:

  - `g++ --version`


## 📝 Creating a console application

🔹 Create the source file:

  - `cat > hello.cpp`
  - insert:

```cpp
    #include <iostream>

    int main()
    {
        std::cout << "Hello World!\n";
        return 0;
    }
```

Press `Ctrl + D` to save.

🔹 Compile:

  - `g++ hello.cpp -o hello`

🔹 Run:

  - `./hello`

🔹 Output:

```text
    Hello World!
```

## 📝 Useful Docker Commands

🔹 List downloaded images:

  - `docker images`

🔹 List running containers:

  - `docker ps`

🔹 List all containers:

  - `docker ps -a`

🔹 Stop a running container:

  - `docker stop <container_id>`

🔹 Start an existing container:

  - `docker start <container_id>`

🔹 Open a shell inside a running container:

  - `docker exec -it <container_id> bash`

🔹 Remove a stopped container:

  - `docker rm <container_id>`

🔹 Remove an image:

  - `docker rmi <image_name>`


### 💡 Notes :

  - Docker containers are lightweight and start within seconds.
  - Containers share the host operating system kernel.
  - Images are templates, containers are running instances of those images.
  - Working inside a Docker container feels very similar to working in a local Linux terminal or on a remote server via SSH.
  - Docker makes it easy to reproduce the exact development environment on any machine.

---