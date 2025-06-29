from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class PackageRecipe(ConanFile):
    name = "blacky"
    version = "1.0"
    package_type = "application"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    # exports_sources = "CMakeLists.txt", "src/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.requires("fmt/11.2.0")
        boost_ops = {
            "without_iostreams": False,
            "without_random": False,
            "without_regex": False,
            "without_system": False,
            #
            "without_atomic": True,
            "without_charconv": True,
            "without_chrono": True,
            "without_cobalt": True,
            "without_container": True,
            "without_context": True,
            "without_contract": True,
            "without_coroutine": True,
            "without_date_time": True,
            "without_exception": True,
            "without_fiber": True,
            "without_filesystem": True,
            "without_graph_parallel": True,
            "without_graph": True,
            "without_json": True,
            "without_locale": True,
            "without_log": True,
            "without_math": True,
            "without_mpi": True,
            "without_nowide": True,
            "without_process": True,
            "without_program_options": True,
            "without_python": True,
            "without_serialization": True,
            "without_stacktrace": True,
            "without_test": True,
            "without_thread": True,
            "without_timer": True,
            "without_type_erasure": True,
            "without_url": True,
            "without_wave": True,
        }
        self.requires("boost/1.88.0", options=boost_ops)
        self.requires("ms-gsl/4.2.0")
