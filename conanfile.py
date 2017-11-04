from conans import ConanFile, CMake


class BitseryConan(ConanFile):
    name = "bitsery"
    version = "4.1.0"
    license = "MIT"
    description = "Header only C++ binary serialization library. It is designed around the networking requirements for real-time data delivery, especially for games."
    url = "https://github.com/fraillt/bitsery"
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    default_options = ""
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/fraillt/bitsery.git --branch v{version} --depth 1".format(version=self.version))

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/bitsery" % self.source_folder)
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="bitsery/include")

    def package_info(self):
        pass
