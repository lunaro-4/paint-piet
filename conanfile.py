from conan import ConanFile
from conan.tools.cmake import CMakeDeps, cmake_layout, CMakeToolchain, CMake

class PaintPietReceipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    # generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("libpng/1.6.40")
        self.requires("libcheck/0.15.2")

    def build_requirements(self):
        self.tool_requires("cmake/3.29.5")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.user_presets_path = 'ConanPresets.json'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
