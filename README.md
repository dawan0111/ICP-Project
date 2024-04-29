# C++ ICP Algorithm Project
[![icp2-ezgif-com-crop.gif](https://i.postimg.cc/8CdVKhGx/icp2-ezgif-com-crop.gif)](https://postimg.cc/McG4XfvY)

This project aims to visualize Iterative Closest Point (ICP) algorithms implemented in C++. Eigen3 and matplotlib-cpp libraries are used, and three ICP variants are planned to be implemented, showcased with checkbox-like indicators:

- [x] SVD-based ICP
- [ ] Non-linear least squares-based ICP
- [ ] Point-to-plane least squares-based ICP

## Installation and Usage

1. Clone this project repository.
    ```bash
    git clone --recurse-submodules https://github.com/dawan0111/ICP-Project.git
    ```
    - The `--recurse-submodules` flag clones the submodules along with the repository.

2. Build the project.
    ```bash
    sudo bash ./thirdparty_build.sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the executable to visualize the algorithm.
    ```bash
    ./SVD_EXAMPLE
    ```

## Notes
- This project is built using CMake.

## Contribution

To contribute to this project, follow these steps:

1. Fork this repository.
2. Create a new branch for your feature or bug fix.
3. Commit and push your changes.
4. Open a Pull Request to contribute your changes.

## Copyright and License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.