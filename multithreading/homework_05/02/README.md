# 📓 Homework_05_02: Dockerfile

> ***A short reference on creating Docker images using a Dockerfile.***

## 📝 Basic Concepts

A **Dockerfile** is a text file that contains a sequence of instructions used to build a Docker image automatically.

Instead of manually executing commands inside a container, Docker reads the Dockerfile and performs each step during the image build process.

🔹 Build Process :

```text
    Dockerfile
        │
        ▼
    docker build
        │
        ▼
    Docker Image
        │
        ▼
    docker run
        │
        ▼
    Container
```

A Dockerfile describes **how to build an image**, while a container is a running instance of that image.

🔹 Example Dockerfile :

```docker
    FROM ubuntu:24.04

    RUN apt update && apt install -y g++ nano

    WORKDIR /my_app

    COPY my_app.cpp .

    CMD ["bash"]
```

## 📝 Dockerfile Instructions

🔹 `FROM` :

  - Defines the base image

🔸 Example :

  - `FROM ubuntu:16.04`

Every Dockerfile starts with a `FROM` instruction.

🔹 `RUN` :

  - Executes commands while building the image

🔸 Example :

  - `RUN apt update`
  - or `RUN apt install -y g++`

🔹 Typical uses:

  - install packages
  - update package lists
  - create directories
  - configure the environment


🔹 `WORKDIR`

  - Sets the working directory inside the image

🔸 Example :

  - `WORKDIR /my_app`

Equivalent to changing the current directory before executing subsequent instructions.

🔹 `COPY` :

 - Copies files from the host machine into the image.

🔸 Example :

  - `COPY my_app.cpp .`

The destination `.` refers to the current working directory defined by `WORKDIR`.

🔹 `CMD` :

  - Specifies the default command executed when the container starts.

🔸 Example :

  - `CMD ["bash"]`

When the container is launched, Docker automatically starts the Bash shell.


## 📝 Build an Image and run the Container

🔹 Build the image from the directory containing the Dockerfile:

  - `docker build -t my-gcc-project .`

🔹 Options :

  - `-t` → assign a name (tag) to the image.
  - `.` → use the current directory as the build context.


🔹 Start an interactive container :

  - `docker run -it my-gcc-project`

🔹 The container starts in :

  - /my_app

Because the working directory was defined using `WORKDIR`.

## 📝 Working Inside the Container

🔹 List project files :

  - `ls`

🔹 Edit the source code :

  - `nano my_app.cpp`

🔹 Compile the program :

  - `g++ my_app.cpp -o exec`

🔹 Run the executable:

  - `./exec`


## 📝 Project Structure

🔹 Local project (directory of my_app) :

```text
    my_app/
    ├── Dockerfile
    └── my_app.cpp
```

🔹 During the build process :

```text
    Host Machine
    │
    ├── Dockerfile
    └── my_app.cpp
            │
            ▼
    docker build
            │
            ▼
    Docker Image
    │
    └── /my_app
        └── my_app.cpp
```


## 📝 Manual vs Dockerfile

🔹 Manual Setup :

```text
    docker run
        │
        ▼
    apt update
        │
        ▼
    apt install g++
        │
        ▼
    apt install nano
        │
        ▼
    mkdir my_app
        │
        ▼
    copy my_app.cpp
```

🔹 Dockerfile :

```docker
    FROM ubuntu:16.04

    RUN apt update && apt install -y g++ nano

    WORKDIR /my_app

    COPY my_app.cpp .

    CMD ["bash"]
```
The Dockerfile automates the entire environment setup.


## 📝 Advantages of Dockerfile

  - Reproducible development environments.
  - Automatic dependency installation.
  - Easy project sharing.
  - No manual environment configuration.
  - Suitable for CI/CD pipelines.

### 💡 Notes :

  - A Dockerfile is a recipe for building an image.
  - An image is a template used to create containers.
  - A container is a running instance of an image.
  - Docker executes Dockerfile instructions from top to bottom.
  - Once the image is built, it can be reused any number of times.
  - During development, source files are often shared with the container using Volumes instead of COPY.

> Think of a **Dockerfile** as the equivalent of **CMakeLists.txt** for your development environment:
>   - **CMakeLists.txt** describes how to build your application.
>   - **Dockerfile** describes how to build the environment in which your application is developed and executed.

---